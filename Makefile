# Copyright 2023 Vincent Jacques

ifndef SUDOKU_MAKE_CALLED_BY_SCRIPT
  $(error Don't call 'make' directly. Use the './make.sh' script.)
endif


# Top-level targets

default: test lint


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

cpplint_sentinels := $(patsubst src/%,build/lint/%.cpplint.ok,${source_files} ${header_files})

.PHONY: lint-cpplint
lint-cpplint: ${cpplint_sentinels}

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

untested_source_files := src/main.cpp src/sudoku.cpp src/explanation/video/video-serializer.cpp src/explanation/video/video-video-serializer.cpp src/explanation/video/frames-video-serializer.cpp src/explanation/follower.cpp src/explanation/text-explainer.cpp src/sudoku-constants.cpp

.PHONY: test-unit
test-unit: build/tests/unit.ok

unit_test_sentinels := $(patsubst src/%.cpp,build/tests/unit/%.ok,$(filter-out ${untested_source_files},${source_files}))

build/tests/unit.ok: ${unit_test_sentinels}
	@mkdir -p ${@D}

	@${echo} "Report coverage: genhtml ... build/tests/unit.coverage/lcov"
	@rm -rf build/tests/unit.coverage/lcov
	@mkdir -p build/tests/unit.coverage/lcov
	@lcov --quiet $(patsubst src/%.cpp,--add-tracefile build/tests/unit/%.coverage/lcov/info,$(filter-out ${untested_source_files},${source_files})) --output-file build/tests/unit.coverage/lcov/info
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests/unit.coverage/lcov/info --output-directory build/tests/unit.coverage/lcov

	@${echo} "Report coverage: gcovr ... build/tests/unit.coverage/gcovr"
	@rm -rf build/tests/unit.coverage/gcovr
	@mkdir -p build/tests/unit.coverage/gcovr
	@gcovr $(patsubst src/%.cpp,--add-tracefile build/tests/unit/%.coverage/gcovr/info.json,$(filter-out ${untested_source_files},${source_files})) --decisions --html-details build/tests/unit.coverage/gcovr/index.html --json build/tests/unit.coverage/gcovr/info.json

	@touch $@

gcov_prefix_strip := $(shell pwd | sed 's|/| |g' | wc -w | xargs expr 2 +)

build/tests/unit/%.ok: build/obj/%.o build/obj/test-main.o
	@mkdir -p ${@D}

	@${echo} "Link: g++ ... -o build/tests/unit/$*"
	@g++ -g --coverage $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o build/tests/unit/$*

	@${echo} "Test (unit): build/tests/unit/$*"
	@rm -rf build/tests/unit/$*.coverage/gcov
	@GCOV_PREFIX=build/tests/unit/$*.coverage/gcov GCOV_PREFIX_STRIP=${gcov_prefix_strip} build/tests/unit/$* --minimal --source-file=src/$*.cpp
	@find build/tests/unit/$*.coverage/gcov -name '*.gcda' | sed 's|\(build/tests/unit/$*.coverage/gcov/\(.*\)\).gcda|ln build/obj/\2.gcno \1.gcno|' | sh

	@${echo} "Report coverage: genhtml ... build/tests/unit/$*.coverage/lcov"
	@rm -rf build/tests/unit/$*.coverage/lcov
	@mkdir -p build/tests/unit/$*.coverage/lcov
	@lcov --quiet --capture --directory build/tests/unit/$*.coverage/gcov --output-file build/tests/unit/$*.coverage/lcov/info
	@lcov --quiet --extract build/tests/unit/$*.coverage/lcov/info "$$PWD/src/$*.*" --output-file build/tests/unit/$*.coverage/lcov/info
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests/unit/$*.coverage/lcov/info --output-directory build/tests/unit/$*.coverage/lcov

	@${echo} "Report coverage: gcovr ... build/tests/unit/$*.coverage/gcovr"
	@rm -rf build/tests/unit/$*.coverage/gcovr
	@mkdir -p build/tests/unit/$*.coverage/gcovr
	@(cd build/tests/unit/$*.coverage; cp -r ${root_directory}/src .; gcovr gcov --object-directory gcov --decisions --filter 'src/$*.*' --html-details gcovr/index.html --json gcovr/info.json; rm -r src)

	@touch $@

build/tests/unit/explanation/html-explainer.ok: build/obj/explanation/art.o
build/tests/unit/explanation/video/video-explainer.ok: build/obj/explanation/art.o


# Integ tests

.PHONY: test-integ
test-integ: build/tests/integ.ok

integ_test_sentinels := $(patsubst %.yml,build/%.ok,${integ_test_files})

build/tests/integ.ok: ${integ_test_sentinels}
	@mkdir -p ${@D}

	@${echo} "Report coverage: genhtml ... build/tests/integ.coverage/lcov"
	@rm -rf build/tests/integ.coverage/lcov
	@mkdir -p build/tests/integ.coverage/lcov
	@lcov --quiet $(patsubst %.yml,--add-tracefile build/%.coverage/lcov/info,${integ_test_files}) --output-file build/tests/integ.coverage/lcov/info
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests/integ.coverage/lcov/info --output-directory build/tests/integ.coverage/lcov

	@${echo} "Report coverage: gcovr ... build/tests/integ.coverage/gcovr"
	@rm -rf build/tests/integ.coverage/gcovr
	@mkdir -p build/tests/integ.coverage/gcovr
	@gcovr $(patsubst %.yml,--add-tracefile build/%.coverage/gcovr/info.json,${integ_test_files}) --decisions --html-details build/tests/integ.coverage/gcovr/index.html --json build/tests/integ.coverage/gcovr/info.json

	@touch $@

build/%.ok: %.yml build/bin/sudoku builder/run-integ-test.py
	@mkdir -p ${@D}

	@${echo} "Test (integ): run-integ-test.py $<"
	@rm -rf build/$*.coverage/gcov
	@GCOV_PREFIX=build/$*.coverage/gcov GCOV_PREFIX_STRIP=${gcov_prefix_strip} builder/run-integ-test.py $<
	@find build/$*.coverage/gcov -name '*.gcda' | sed 's|\(build/$*.coverage/gcov/\(.*\)\).gcda|ln build/obj/\2.gcno \1.gcno|' | sh

	@${echo} "Report coverage: genhtml ... build/$*.coverage/lcov"
	@rm -rf build/$*.coverage/lcov
	@mkdir -p build/$*.coverage/lcov
	@lcov --quiet --capture --directory build/$*.coverage/gcov --output-file build/$*.coverage/lcov/info
	@lcov --quiet --extract build/$*.coverage/lcov/info "$$PWD/src/*" --output-file build/$*.coverage/lcov/info
	@genhtml --quiet --legend --demangle-cpp --show-details build/$*.coverage/lcov/info --output-directory build/$*.coverage/lcov

	@${echo} "Report coverage: gcovr ... build/$*.coverage/gcovr"
	@rm -rf build/$*.coverage/gcovr
	@mkdir -p build/$*.coverage/gcovr
	@(cd build/$*.coverage; cp -r ${root_directory}/src .; gcovr gcov --object-directory gcov --decisions --filter 'src/*' --html-details gcovr/index.html --json gcovr/info.json; rm -r src)

	@touch $@


# Coverage report for all tests

.PHONY: test
test: build/tests.ok

build/tests.ok: build/tests/unit.ok build/tests/integ.ok
	@mkdir -p ${@D}

	@${echo} "Report coverage: genhtml ... build/tests.coverage/lcov"
	@rm -rf build/tests.coverage/lcov
	@mkdir -p build/tests.coverage/lcov
	@lcov --quiet $(patsubst %,--add-tracefile build/tests/%.coverage/lcov/info,unit integ) --output-file build/tests.coverage/lcov/info
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests.coverage/lcov/info --output-directory build/tests.coverage/lcov

	@${echo} "Report coverage: gcovr ... build/tests.coverage/gcovr"
	@rm -rf build/tests.coverage/gcovr
	@mkdir -p build/tests.coverage/gcovr
	@gcovr $(patsubst %,--add-tracefile build/tests/%.coverage/gcovr/info.json,unit integ) --decisions --html-details build/tests.coverage/gcovr/index.html --json build/tests.coverage/gcovr/info.json

	@touch $@
