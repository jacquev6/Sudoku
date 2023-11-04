# Copyright 2023 Vincent Jacques

ifndef SUDOKU_MAKE_CALLED_BY_SCRIPT
  $(error Don't call 'make' directly. Use the './make.sh' script.)
endif


# Top-level targets

default: coverage-gcovr lint

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
	@cpplint --quiet --linelength=120 --root=src --filter=-build/include_subdir $<
	@touch $@


# Compilation

object_files := $(patsubst src/%.cpp,build/obj/%.o,${source_files})

.PHONY: compile
compile: ${object_files}

build/obj/%.o: src/%.cpp
	@${echo} "Compile: g++ -c $<"
	@mkdir -p ${@D}
	@CCACHE_LOGFILE=$@.ccache-log g++ -g --coverage -c -std=c++20 $$(pkg-config cairomm-1.16 libavutil libavcodec --cflags) -include icecream.hpp -MMD -MP $< -o $@

# Special object file containing doctest's main function
build/obj/test-main.o:
	@${echo} "Compile: g++ -c doctest.h"
	@mkdir -p ${@D}
	@CCACHE_LOGFILE=$@.ccache-log g++ -g -c -x c++ -std=c++20 -include doctest.h -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN /dev/null -o $@

include $(shell find build -name '*.d' 2>/dev/null)


# Link

.PHONY: link
link: build/bin/sudoku

build/bin/sudoku: ${object_files}
	@${echo} "Link: g++ ... -o $@"
	@mkdir -p ${@D}
	@g++ -g --coverage $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o $@


# Unit tests

untested_source_files := src/main.cpp  # Only the 'main' function and command-line parsing
untested_source_files += src/sudoku-constants.cpp  # Tested with static asserts

# @todo Test the following files
untested_source_files += src/explanation/follower.cpp
untested_source_files += src/explanation/text-explainer.cpp
untested_source_files += src/explanation/video/frames-video-serializer.cpp
untested_source_files += src/explanation/video/video-serializer.cpp
untested_source_files += src/explanation/video/video-video-serializer.cpp
untested_source_files += src/sudoku.cpp

.PHONY: test-unit
test-unit: $(patsubst src/%.cpp,build/tests/unit/%.ok,$(filter-out ${untested_source_files},${source_files}))

gcov_prefix_strip := $(shell pwd | sed 's|/| |g' | wc -w | xargs expr 2 +)

build/tests/unit/%.ok: build/obj/%.o build/obj/test-main.o
	@${echo} "Link: g++ ... -o build/tests/unit/$*"
	@mkdir -p ${@D}
	@g++ -g --coverage $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o build/tests/unit/$*

	@${echo} "Test (unit): build/tests/unit/$*"
	@rm -rf build/tests/unit/$*.coverage/gcov
	@GCOV_PREFIX=build/tests/unit/$*.coverage/gcov GCOV_PREFIX_STRIP=${gcov_prefix_strip} build/tests/unit/$* --minimal --source-file=src/$*.cpp
	@find build/tests/unit/$*.coverage/gcov -name '*.gcda' | sed 's|\(build/tests/unit/$*.coverage/gcov/\(.*\)\).gcda|ln build/obj/\2.gcno \1.gcno|' | sh
	@touch $@

build/tests/unit/explanation/html-explainer.ok: build/obj/explanation/art.o
build/tests/unit/explanation/video/video-explainer.ok: build/obj/explanation/art.o
build/tests/unit/exploration/sudoku-solver.ok: build/obj/io/sudoku.o
build/tests/unit/sat/sudoku-solver.ok: build/obj/io/sudoku.o


# Integ tests

.PHONY: test-integ
test-integ: $(patsubst tests/integ/%.yml,build/tests/integ/%.ok,${integ_test_files})

build/tests/integ/%.ok: tests/integ/%.yml build/bin/sudoku builder/run-integ-test.py
	@${echo} "Test (integ): run-integ-test.py $<"
	@mkdir -p ${@D}
	@rm -rf build/tests/integ/$*.coverage/gcov
	@GCOV_PREFIX=build/tests/integ/$*.coverage/gcov GCOV_PREFIX_STRIP=${gcov_prefix_strip} builder/run-integ-test.py $<
	@find build/tests/integ/$*.coverage/gcov -name '*.gcda' | sed 's|\(build/tests/integ/$*.coverage/gcov/\(.*\)\).gcda|ln build/obj/\2.gcno \1.gcno|' | sh
	@touch $@


# Coverage reports: lcov

.PHONY: coverage-lcov-unit
coverage-lcov-unit: build/tests/unit.coverage/lcov/index.html

build/tests/unit.coverage/lcov/index.html: $(patsubst src/%.cpp,build/tests/unit/%.coverage/lcov/index.html,$(filter-out ${untested_source_files},${source_files}))
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet $(patsubst src/%.cpp,--add-tracefile build/tests/unit/%.coverage/lcov/info,$(filter-out ${untested_source_files},${source_files})) --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

build/tests/unit/%.coverage/lcov/index.html: build/tests/unit/%.ok
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet --capture --directory build/tests/unit/$*.coverage/gcov --output-file ${@D}/info
	@lcov --quiet --extract ${@D}/info "$$PWD/src/$*.*" --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

.PHONY: coverage-lcov-integ
coverage-lcov-integ: build/tests/integ.coverage/lcov/index.html

build/tests/integ.coverage/lcov/index.html: $(patsubst tests/integ/%.yml,build/tests/integ/%.coverage/lcov/index.html,${integ_test_files})
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet $(patsubst tests/integ/%.yml,--add-tracefile build/tests/integ/%.coverage/lcov/info,${integ_test_files}) --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

build/tests/integ/%.coverage/lcov/index.html: build/tests/integ/%.ok
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet --capture --directory build/tests/integ/$*.coverage/gcov --output-file ${@D}/info
	@lcov --quiet --extract ${@D}/info "$$PWD/src/*" --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}

.PHONY: coverage-lcov
coverage-lcov: build/tests.coverage/lcov/index.html

build/tests.coverage/lcov/index.html: build/tests/unit.coverage/lcov/index.html build/tests/integ.coverage/lcov/index.html
	@${echo} "Report coverage: genhtml ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@lcov --quiet $(patsubst %,--add-tracefile build/tests/%.coverage/lcov/info,unit integ) --output-file ${@D}/info
	@genhtml --quiet --legend --demangle-cpp --show-details ${@D}/info --output-directory ${@D}


# Coverage reports: gcovr

.PHONY: coverage-gcovr-unit
coverage-gcovr-unit: build/tests/unit.coverage/gcovr/index.html

build/tests/unit.coverage/gcovr/index.html: $(patsubst src/%.cpp,build/tests/unit/%.coverage/gcovr/index.html,$(filter-out ${untested_source_files},${source_files}))
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@gcovr $(patsubst src/%.cpp,--add-tracefile build/tests/unit/%.coverage/gcovr/info.json,$(filter-out ${untested_source_files},${source_files})) --decisions --html-details ${@D}/index.html --json ${@D}/info.json

build/tests/unit/%.coverage/gcovr/index.html: build/tests/unit/%.ok
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@(cd ${@D}/..; cp -r ${root_directory}/src .; gcovr gcov --object-directory gcov --decisions --filter 'src/$*.*' --html-details gcovr/index.html --json gcovr/info.json; rm -r src)

.PHONY: coverage-gcovr-integ
coverage-gcovr-integ: build/tests/integ.coverage/gcovr/index.html

build/tests/integ.coverage/gcovr/index.html: $(patsubst tests/integ/%.yml,build/tests/integ/%.coverage/gcovr/index.html,${integ_test_files})
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@gcovr $(patsubst tests/integ/%.yml,--add-tracefile build/tests/integ/%.coverage/gcovr/info.json,${integ_test_files}) --decisions --html-details ${@D}/index.html --json ${@D}/info.json

build/tests/integ/%.coverage/gcovr/index.html: build/tests/integ/%.ok
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@(cd ${@D}/..; cp -r ${root_directory}/src .; gcovr gcov --object-directory gcov --decisions --filter 'src/*' --html-details gcovr/index.html --json gcovr/info.json; rm -r src)

.PHONY: coverage-gcovr
coverage-gcovr: build/tests.coverage/gcovr/index.html

build/tests.coverage/gcovr/index.html: build/tests/unit.coverage/gcovr/index.html build/tests/integ.coverage/gcovr/index.html
	@${echo} "Report coverage: gcovr ... ${@D}"
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@rm -rf ${@D}
	@mkdir -p ${@D}
	@gcovr $(patsubst %,--add-tracefile build/tests/%.coverage/gcovr/info.json,unit integ) --decisions --html-details ${@D}/index.html --json ${@D}/info.json
