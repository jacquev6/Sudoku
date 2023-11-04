#!/bin/bash

# Copyright 2023 Vincent Jacques

set -o errexit
set -o nounset
set -o pipefail


if !(
  diff -r builder/Dockerfile build/Dockerfile &&
  diff Makefile build/Makefile
)>/dev/null 2>&1
then
  rm -rf build
  mkdir build
  docker build --tag jacquev6/sudoku-development builder
  cp builder/Dockerfile build
  cp Makefile build
fi

docker run \
  --rm --interactive --tty \
  --user $(id -u):$(id -g) \
  --volume "$PWD:/wd" --workdir /wd \
  --volume sudoku-development-ccache:/ccache \
  --env SUDOKU_MAKE_CALLED_BY_SCRIPT=true \
  jacquev6/sudoku-development \
  make "$@"
