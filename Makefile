# Copyright 2023 Vincent Jacques

ifndef SUDOKU_MAKE_CALLED_BY_SCRIPT
  $(error Don't call 'make' directly. Use the './make.sh' script.)
endif

# https://stackoverflow.com/a/589300/905845
SHELL := /bin/bash -o pipefail -o errexit -o nounset


# Top-level targets

.PHONY: default
default: coverage-gcovr lint insight

.PHONY: no-cover
no-cover: test lint insight

.PHONY: test
test: test-unit test-integ

.PHONY: coverage-all
coverage-all: coverage-lcov coverage-gcovr

.PHONY: coverage-all-unit
coverage-all-unit: coverage-lcov-unit coverage-gcovr-unit

.PHONY: coverage-all-integ
coverage-all-integ: coverage-lcov-integ coverage-gcovr-integ


# Inputs

root_directory := $(shell pwd)
source_files := $(shell find src -name '*.cpp')
header_files := $(shell find src -name '*.hpp')
integ_test_files := $(shell find tests/integ -name '*.yml')


# Utilities

echo := builder/echo.py


# Lint and static analysis

.PHONY: lint
lint: lint-cpplint

.PHONY: lint-cpplint
lint-cpplint: $(patsubst src/%,build/lint/%.cpplint.ok,${source_files} ${header_files})

build/lint/%.cpplint.ok: src/%
	@${echo} "Lint: cpplint $<"
	@mkdir -p ${@D}
	@cpplint --quiet --linelength=120 --root=src --filter=-build/include_subdir,-readability/check $<
	@touch $@

.PHONY: insight
insight: $(patsubst src/%,build/insight/%,${source_files})

build/insight/%: src/% builder/crudest-preprocessor.py builder/stabilize-lambda-names.py builder/stabilize-numbered-names.py
	@${echo} "Insight: insights $<"
	@mkdir -p ${@D}
	@builder/crudest-preprocessor.py $< \
	| insights --stdin --show-all-callexpr-template-parameters --show-all-implicit-casts $< -- \
	  -std=c++20 \
	  $$(pkg-config cairomm-1.16 libavutil libavcodec --cflags) -I`chrones instrument c++ header-location` -include icecream.hpp \
	| builder/stabilize-lambda-names.py \
	| builder/stabilize-numbered-names.py \
	>$@.tmp
	@mv $@.tmp $@


# Compilation

debug_object_files := $(patsubst src/%.cpp,build/debug/obj/%.o,${source_files})
release_object_files := $(patsubst src/%.cpp,build/release/obj/%.o,${source_files})

.PHONY: compile
compile: compile-debug compile-release

.PHONY: compile-debug
compile-debug: ${debug_object_files}

build/debug/obj/%.o: src/%.cpp
	@${echo} "Compile: g++ -c ... -o $@"
	@mkdir -p ${@D}
	@CCACHE_LOGFILE=$@.ccache-log g++ \
		-g --coverage -O0 \
		-std=c++20 -Wall -Wextra -pedantic -Werror -Wno-missing-field-initializers \
		$$(pkg-config cairomm-1.16 libavutil libavcodec --cflags) -I`chrones instrument c++ header-location` -include icecream.hpp \
		-MMD -MP \
		-c $< \
		-o $@
	@sed -i 's#^build/debug/obj/\(.*\)\.o:#build/debug/obj/\1.o build/insight/\1.cpp:#' build/debug/obj/$*.d

# Special object file containing doctest's main function
build/debug/obj/test-main.o:
	@${echo} "Compile: g++ -c doctest.h"
	@mkdir -p ${@D}
	@ (echo 'CHRONABLE("test")') | \
	CCACHE_LOGFILE=$@.ccache-log g++ \
		-g -O0 \
		-x c++ -std=c++20 \
		-I`chrones instrument c++ header-location` \
		-include doctest.h -include chrones.hpp \
		-DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN \
		-c - \
		-o $@

.PHONY: compile-release
compile-release: ${release_object_files}

build/release/obj/%.o: src/%.cpp
	@${echo} "Compile: g++ -c ... -o $@"
	@mkdir -p ${@D}
	@CCACHE_LOGFILE=$@.ccache-log g++ \
		-DNDEBUG -O3 \
		-std=c++20 \
		$$(pkg-config cairomm-1.16 libavutil libavcodec --cflags) -I`chrones instrument c++ header-location` -include icecream.hpp \
		-MMD -MP \
		-c $< \
		-o $@

# @todo Robustify these includes: the following sequence leads to missing rebuilding a target:
#   rm -rf build; ./make.sh insight; touch src/main.cpp; ./make.sh insight
# because the '*.d' files are never produced.
include $(shell find build -name '*.d' 2>/dev/null)


# Link

.PHONY: link
link: link-debug link-release

.PHONY: link-debug
link-debug: build/debug/bin/sudoku

build/debug/bin/sudoku: ${debug_object_files}
	@${echo} "Link: g++ ... -o $@"
	@mkdir -p ${@D}
	@g++ -g --coverage -O0 $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o $@

.PHONY: link-release
link-release: build/release/bin/sudoku

build/release/bin/sudoku: ${release_object_files}
	@${echo} "Link: g++ ... -o $@"
	@mkdir -p ${@D}
	@g++ -s -O3 $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o $@


# Unit tests

# @todo Run tests under valgrind to check for memory leaks
# @todo Run tests with libasan and co.

untested_source_files := src/main.cpp src/main-4.cpp src/main-9.cpp src/main-16.cpp src/main-25.cpp  # Only the 'main' function and command-line parsing
untested_source_files += src/sudoku-constants.cpp  # Tested with static asserts

# @todo Test the following files
untested_source_files += src/explanation/follower.cpp
untested_source_files += src/explanation/text-explainer.cpp
untested_source_files += src/explanation/video/frames-video-serializer.cpp
untested_source_files += src/explanation/video/video-serializer.cpp
untested_source_files += src/explanation/video/video-video-serializer.cpp
untested_source_files += src/sudoku.cpp

.PHONY: test-unit
test-unit: $(patsubst src/%.cpp,build/debug/tests/unit/%.ok,$(filter-out ${untested_source_files},${source_files}))

gcov_prefix_strip := $(shell pwd | sed 's|/| |g' | wc -w | xargs expr 2 +)

build/debug/tests/unit/%.ok: build/debug/obj/%.o build/debug/obj/test-main.o
	@${echo} "Link: g++ ... -o build/debug/tests/unit/$*"
	@mkdir -p ${@D}
	@g++ -g --coverage $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o build/debug/tests/unit/$*

	@find tests/unit/$* -type f -delete 2>/dev/null || true

	@${echo} "Test (unit): build/debug/tests/unit/$*"
	@rm -rf build/debug/tests/unit/$*.coverage/gcov
	@GCOV_PREFIX=build/debug/tests/unit/$*.coverage/gcov GCOV_PREFIX_STRIP=${gcov_prefix_strip} build/debug/tests/unit/$* --minimal --source-file=src/$*.cpp
	@find build/debug/tests/unit/$*.coverage/gcov -name '*.gcda' | sed 's|\(build/debug/tests/unit/$*.coverage/gcov/\(.*\)\).gcda|ln build/debug/\2.gcno \1.gcno|' | sh
	@touch $@

# Using 'filter' to get an error if a source file is removed but the object file is still in 'build'
build/debug/tests/unit/explanation/html-explainer.ok: $(filter build/debug/obj/explanation/art.o build/debug/obj/exploration/events.o,${debug_object_files})
build/debug/tests/unit/explanation/video-explainer.ok: $(filter build/debug/obj/explanation/art.o build/debug/obj/exploration/events.o,${debug_object_files})
build/debug/tests/unit/exploration/sudoku-solver.ok: $(filter build/debug/obj/exploration/events.o,${debug_object_files})
build/debug/tests/unit/explanation/reorder.ok: $(filter build/debug/obj/exploration/events.o,${debug_object_files})


# Integ tests

.PHONY: test-integ
test-integ: $(patsubst tests/integ/%.yml,build/debug/tests/integ/%.ok,${integ_test_files})

build/debug/tests/integ/%.ok: tests/integ/%.yml build/debug/bin/sudoku builder/run-integ-test.py
	@${echo} "Test (integ): run-integ-test.py $<"
	@mkdir -p ${@D}
	@rm -rf build/debug/tests/integ/$*.coverage/gcov
	@GCOV_PREFIX=build/debug/tests/integ/$*.coverage/gcov GCOV_PREFIX_STRIP=${gcov_prefix_strip} PATH=build/debug/bin:${PATH} builder/run-integ-test.py $<
	@find build/debug/tests/integ/$*.coverage/gcov -name '*.gcda' | sed 's|\(build/debug/tests/integ/$*.coverage/gcov/\(.*\)\).gcda|ln build/debug/\2.gcno \1.gcno|' | sh
	@touch $@


# Coverage reports: lcov

.PHONY: coverage-lcov-unit
coverage-lcov-unit: build/debug/tests/unit.coverage/lcov/index.html

build/debug/tests/unit.coverage/lcov/index.html: $(patsubst src/%.cpp,build/debug/tests/unit/%.coverage/lcov/index.html,$(filter-out ${untested_source_files},${source_files}))
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet $(patsubst src/%.cpp,--add-tracefile build/debug/tests/unit/%.coverage/lcov/info,$(filter-out ${untested_source_files},${source_files})) --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

build/debug/tests/unit/%.coverage/lcov/index.html: build/debug/tests/unit/%.ok
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet --capture --directory build/debug/tests/unit/$*.coverage/gcov --output-file ${@D}/info
	@lcov --quiet --extract ${@D}/info "$$PWD/src/$*.*" --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

.PHONY: coverage-lcov-integ
coverage-lcov-integ: build/debug/tests/integ.coverage/lcov/index.html

build/debug/tests/integ.coverage/lcov/index.html: $(patsubst tests/integ/%.yml,build/debug/tests/integ/%.coverage/lcov/index.html,${integ_test_files})
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet $(patsubst tests/integ/%.yml,--add-tracefile build/debug/tests/integ/%.coverage/lcov/info,${integ_test_files}) --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

build/debug/tests/integ/%.coverage/lcov/index.html: build/debug/tests/integ/%.ok
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet --capture --directory build/debug/tests/integ/$*.coverage/gcov --output-file ${@D}/info
	@lcov --quiet --extract ${@D}/info "$$PWD/src/*" --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

.PHONY: coverage-lcov
coverage-lcov: build/debug/tests.coverage/lcov/index.html

build/debug/tests.coverage/lcov/index.html: build/debug/tests/unit.coverage/lcov/index.html build/debug/tests/integ.coverage/lcov/index.html
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet $(patsubst %,--add-tracefile build/debug/tests/%.coverage/lcov/info,unit integ) --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}


# Coverage reports: gcovr

.PHONY: coverage-gcovr-unit
coverage-gcovr-unit: build/debug/tests/unit.coverage/gcovr/index.html

build/debug/tests/unit.coverage/gcovr/index.html: $(patsubst src/%.cpp,build/debug/tests/unit/%.coverage/gcovr/index.html,$(filter-out ${untested_source_files},${source_files}))
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@gcovr $(patsubst src/%.cpp,--add-tracefile build/debug/tests/unit/%.coverage/gcovr/info.json,$(filter-out ${untested_source_files},${source_files})) --decisions --html-details ${@D}/index.html --json ${@D}/info.json

build/debug/tests/unit/%.coverage/gcovr/index.html: build/debug/tests/unit/%.ok
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@(cd ${@D}/..; cp -r ${root_directory}/src .; gcovr gcov --object-directory gcov --decisions --filter 'src/$*.*' --html-details gcovr/index.html --json gcovr/info.json; rm -r src)

.PHONY: coverage-gcovr-integ
coverage-gcovr-integ: build/debug/tests/integ.coverage/gcovr/index.html

build/debug/tests/integ.coverage/gcovr/index.html: $(patsubst tests/integ/%.yml,build/debug/tests/integ/%.coverage/gcovr/index.html,${integ_test_files})
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@gcovr $(patsubst tests/integ/%.yml,--add-tracefile build/debug/tests/integ/%.coverage/gcovr/info.json,${integ_test_files}) --decisions --html-details ${@D}/index.html --json ${@D}/info.json

build/debug/tests/integ/%.coverage/gcovr/index.html: build/debug/tests/integ/%.ok
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@(cd ${@D}/..; cp -r ${root_directory}/src .; gcovr gcov --object-directory gcov --decisions --filter 'src/*' --html-details gcovr/index.html --json gcovr/info.json; rm -r src)

.PHONY: coverage-gcovr
coverage-gcovr: build/debug/tests.coverage/gcovr/index.html

build/debug/tests.coverage/gcovr/index.html: build/debug/tests/unit.coverage/gcovr/index.html build/debug/tests/integ.coverage/gcovr/index.html
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@gcovr $(patsubst %,--add-tracefile build/debug/tests/%.coverage/gcovr/info.json,unit integ) --decisions --html-details ${@D}/index.html --json ${@D}/info.json


# Benchmarks

.PHONY: benchmark
benchmark: build/release/report.png

build/release/report.png: build/release/bin/sudoku
	@${echo} "Benchmark: sudoku"
	@rm -f build/release/report.png build/release/run-result.json build/release/sudoku.*.chrones.csv
	@chrones run --logs-dir build/release -- build/release/bin/sudoku --size 16 benchmark inputs/expert-16.txt
	@chrones report --logs-dir build/release --output-name build/release/report.png
