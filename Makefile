# Copyright 2023 Vincent Jacques

ifndef SUDOKU_MAKE_CALLED_BY_SCRIPT
  $(error Don't call 'make' directly. Use the './make.sh' script.)
endif


# Top-level targets

default: link test lint

.PHONY: test
test: test-unit test-integ


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
	g++ -g -c -std=c++20 $$(pkg-config cairomm-1.16 libavutil libavcodec --cflags) -include icecream.hpp -MMD -MP $< -o $@

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
	g++ -g $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o $@


# Unit tests

unit_test_sentinels := $(patsubst src/%.cpp,build/tests/unit/%.ok,$(filter-out src/main.cpp,${source_files}))

.PHONY: test-unit
test-unit: ${unit_test_sentinels}

build/tests/unit/%.ok: build/obj/%.o build/obj/test-main.o
	@mkdir -p ${@D}
	g++ -g $^ $$(pkg-config cairomm-1.16 libavutil libavcodec --libs) -lminisat -o build/obj/$*
	build/obj/$* --source-file=src/$*.cpp
	@mv build/obj/$* $@

build/tests/unit/explanation/html-explainer.ok: build/obj/explanation/art.o
build/tests/unit/explanation/video/video-explainer.ok: build/obj/explanation/art.o


# Integ tests

integ_test_sentinels := $(patsubst %.yml,build/%.ok,${integ_test_files})

.PHONY: test-integ
test-integ: ${integ_test_sentinels}

build/%.ok: %.yml build/bin/sudoku builder/run-integ-test.py
	@mkdir -p ${@D}
	builder/run-integ-test.py $<
	@touch $@
