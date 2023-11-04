# Copyright 2023 Vincent Jacques

FROM ubuntu:23.04 AS base

# Cache Ubuntu packages: https://docs.docker.com/engine/reference/builder/#run---mounttypecache
RUN set -x \
 && rm -f /etc/apt/apt.conf.d/docker-clean \
 && echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' >/etc/apt/apt.conf.d/keep-cache


# Cache downloads: use one stage for each
FROM base AS download

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    set -x \
 && apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install --yes --no-install-recommends \
      ca-certificates \
      wget \
 && true

WORKDIR /download


FROM download AS download-cli11

RUN wget https://github.com/CLIUtils/CLI11/releases/download/v2.3.2/CLI11.hpp


FROM download AS download-doctest

RUN wget https://github.com/doctest/doctest/releases/download/v2.4.11/doctest.h


FROM download AS download-icecream

RUN wget https://github.com/renatoGarcia/icecream-cpp/raw/fc3a8edcf174d27d8c8628bb68fbe8bca86e8275/icecream.hpp


# Work around https://bugs.launchpad.net/ubuntu/+source/lcov/+bug/2002238
FROM download AS download-lcov

RUN set -x \
 && mkdir lcov \
 && cd lcov \
 && wget https://github.com/linux-test-project/lcov/releases/download/v1.16/lcov-1.16.tar.gz -O - | tar -xz --strip-components=1


FROM download AS download-minisat

RUN set -x \
 && mkdir minisat \
 && cd minisat \
 && wget https://github.com/niklasso/minisat/archive/37dc6c67.tar.gz -O - | tar -xz --strip-components=1


FROM base AS final

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    set -x \
 && apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install --yes --no-install-recommends \
      cairomm-1.16-dev \
      ccache \
      g++ \
      gdb \
      libavcodec-dev \
      libboost-dev \
      make \
      perl \
      pkg-config \
      python3-pip \
 && true

RUN cd /usr/local/bin \
 && ln -s /usr/bin/ccache g++ \
 && ln -s /usr/bin/ccache gcc \
 && mkdir /ccache \
 && chmod 777 /ccache

ENV CCACHE_DIR=/ccache

# Cache Python packages
RUN --mount=type=cache,target=/root/.cache/pip,sharing=locked \
    pip3 install --break-system-packages \
      cpplint \
      gcovr \
      PyYAML \
 && true

RUN --mount=type=bind,from=download-cli11,source=/download,target=/download \
    cp /download/CLI11.hpp /usr/local/include

RUN --mount=type=bind,from=download-doctest,source=/download,target=/download \
    cp /download/doctest.h /usr/local/include

RUN --mount=type=bind,from=download-icecream,source=/download,target=/download \
    cp /download/icecream.hpp /usr/local/include

RUN --mount=type=bind,from=download-lcov,source=/download,target=/download \
    set -x \
 && cd /download/lcov \
 && make install

RUN --mount=type=cache,target=/ccache \
    --mount=type=bind,from=download-minisat,source=/download,target=/download,rw \
    set -x \
 && cd /download/minisat \
 && sed -i minisat/core/SolverTypes.h -e '55s#bool sign = false#bool sign#' -e '63s#bool sign#bool sign=false#' \
 && make config prefix=/usr/local \
 && make install \
 && ldconfig
