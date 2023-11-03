# Copyright 2023 Vincent Jacques

ifndef SUDOKU_MAKE_CALLED_BY_SCRIPT
  $(error Don't call 'make' directly. Use the './make.sh' script.)
endif


# Top-level targets

default: link test lint


# Inputs

source_files := $(shell find src -name '*.cpp')
header_files := $(shell find src -name '*.hpp')
integ_test_files := $(shell find tests/integ -name '*.yml')


# Lint and static analysis

.PHONY: lint
lint: lint-cpplint

cpplint_sentinels := $(patsubst src/%,build/lint/%.cpplint.ok,${source_files} ${header_files})

.PHONY: lint-cpplint
lint-cpplint: ${cpplint_sentinels}

build/lint/%.cpplint.ok: src/%
	@mkdir -p ${@D}
	cpplint --linelength=120 --root=src --filter=-build/include_subdir $<
	@touch $@


# Compilation

object_files := $(patsubst src/%.cpp,build/obj/%.o,${source_files})

.PHONY: compile
compile: ${object_files}

build/obj/%.o: src/%.cpp
	@mkdir -p ${@D}
	g++ -g --coverage -c -std=c++20 $$(pkg-config cairomm-1.16 libavutil libavcodec --cflags) -include icecream.hpp -MMD -MP $< -o $@

# Special object file containing doctest's main function
build/obj/test-main.o:
	@mkdir -p ${@D}
	g++ -g -c -x c++ -std=c++20 -include doctest.h -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN /dev/null -o $@

include $(shell find build -name '*.d' 2>/dev/null)


# Link

.PHONY: link
link: build/bin/sudoku

build/bin/sudoku: ${object_files}
	@mkdir -p ${@D}
	g++ -g --coverage $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o $@


# Unit tests

.PHONY: test-unit
test-unit: build/tests/unit.ok

unit_test_sentinels := $(patsubst src/%.cpp,build/tests/unit/%.ok,$(filter-out src/main.cpp,${source_files}))

build/tests/unit.ok: ${unit_test_sentinels}
	@rm -rf build/tests/unit.coverage
	@mkdir build/tests/unit.coverage
	@lcov $(patsubst src/%.cpp,--add-tracefile build/tests/unit/%.coverage/lcov.info,$(filter-out src/main.cpp src/sudoku.cpp src/explanation/video/video-serializer.cpp src/explanation/video/video-video-serializer.cpp src/explanation/video/frames-video-serializer.cpp src/explanation/follower.cpp src/explanation/text-explainer.cpp src/sudoku-constants.cpp,${source_files})) --output-file build/tests/unit.coverage/lcov.info >/dev/null 2>&1 || true
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests/unit.coverage/lcov.info --output-directory build/tests/unit.coverage >/dev/null 2>&1 || true
	@touch $@

gcov_prefix_strip := $(shell pwd | sed 's|/| |g' | wc -w | xargs expr 2 +)

build/tests/unit/%.ok: build/obj/%.o build/obj/test-main.o
	@mkdir -p ${@D}
	g++ -g --coverage $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o build/tests/unit/$*
	@rm -rf build/tests/unit/$*.coverage
	GCOV_PREFIX=build/tests/unit/$*.coverage GCOV_PREFIX_STRIP=${gcov_prefix_strip} build/tests/unit/$* --source-file=src/$*.cpp
	@find build/tests/unit/$*.coverage -name '*.gcda' | sed 's|\(build/tests/unit/$*.coverage/\(.*\)\).gcda|ln build/obj/\2.gcno \1.gcno|' | sh
	@lcov --quiet --capture --directory build/tests/unit/$*.coverage --output-file build/tests/unit/$*.coverage/lcov.info >/dev/null 2>&1 || true
	@lcov --quiet --extract build/tests/unit/$*.coverage/lcov.info "$$PWD/src/$*.*" --output-file build/tests/unit/$*.coverage/lcov.info >/dev/null 2>&1 || true
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests/unit/$*.coverage/lcov.info --output-directory build/tests/unit/$*.coverage >/dev/null 2>&1 || true
	@touch $@

build/tests/unit/explanation/html-explainer.ok: build/obj/explanation/art.o
build/tests/unit/explanation/video/video-explainer.ok: build/obj/explanation/art.o


# Integ tests

.PHONY: test-integ
test-integ: build/tests/integ.ok

integ_test_sentinels := $(patsubst %.yml,build/%.ok,${integ_test_files})

build/tests/integ.ok: ${integ_test_sentinels}
	@rm -rf build/tests/integ.coverage
	@mkdir build/tests/integ.coverage
	@lcov $(patsubst %.yml,--add-tracefile build/%.coverage/lcov.info,${integ_test_files}) --output-file build/tests/integ.coverage/lcov.info >/dev/null 2>&1 || true
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests/integ.coverage/lcov.info --output-directory build/tests/integ.coverage >/dev/null 2>&1 || true
	@touch $@

build/%.ok: %.yml build/bin/sudoku builder/run-integ-test.py
	@mkdir -p ${@D}
	@rm -rf build/$*.coverage
	GCOV_PREFIX=build/$*.coverage GCOV_PREFIX_STRIP=${gcov_prefix_strip} builder/run-integ-test.py $<
	@find build/$*.coverage -name '*.gcda' | sed 's|\(build/$*.coverage/\(.*\)\).gcda|ln build/obj/\2.gcno \1.gcno|' | sh
	@lcov --quiet --capture --directory build/$*.coverage --output-file build/$*.coverage/lcov.info >/dev/null 2>&1 || true
	@lcov --quiet --extract build/$*.coverage/lcov.info "$$PWD/src/*" --output-file build/$*.coverage/lcov.info >/dev/null 2>&1 || true
	@genhtml --quiet --legend --demangle-cpp --show-details build/$*.coverage/lcov.info --output-directory build/$*.coverage >/dev/null 2>&1 || true
	@touch $@


# Coverage report for all tests

.PHONY: test
test: build/tests.ok

build/tests.ok: test-unit test-integ
	@rm -rf build/tests.coverage
	@mkdir build/tests.coverage
	@lcov $(patsubst %,--add-tracefile build/tests/%.coverage/lcov.info,unit integ) --output-file build/tests.coverage/lcov.info >/dev/null 2>&1 || true
	@genhtml --quiet --legend --demangle-cpp --show-details build/tests.coverage/lcov.info --output-directory build/tests.coverage >/dev/null 2>&1 || true
	@touch $@
