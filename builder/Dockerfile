# Copyright 2023 Vincent Jacques

FROM ubuntu:23.04

# https://docs.docker.com/engine/reference/builder/#run---mounttypecache
RUN set -x \
 && rm -f /etc/apt/apt.conf.d/docker-clean \
 && echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' >/etc/apt/apt.conf.d/keep-cache

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    set -x \
 && apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install --yes --no-install-recommends \
      ca-certificates \
      cairomm-1.16-dev \
      g++ \
      gdb \
      libavcodec-dev \
      libboost-dev \
      make \
      pkg-config \
      python3-pip \
      wget \
 && true

RUN set -x \
 && mkdir minisat \
 && cd minisat \
 && wget https://github.com/niklasso/minisat/archive/37dc6c67.tar.gz -O - | tar -xz --strip-components=1 \
 && sed -i minisat/core/SolverTypes.h -e '55s#bool sign = false#bool sign#' -e '63s#bool sign#bool sign=false#' \
 && make config prefix=/usr/local \
 && make install \
 && cd .. \
 && rm -r minisat \
 && ldconfig

RUN wget https://github.com/CLIUtils/CLI11/releases/download/v2.3.2/CLI11.hpp --output-document=/usr/local/include/CLI11.hpp

RUN wget https://github.com/renatoGarcia/icecream-cpp/raw/fc3a8edcf174d27d8c8628bb68fbe8bca86e8275/icecream.hpp --output-document=/usr/local/include/icecream.hpp

RUN wget https://github.com/doctest/doctest/releases/download/v2.4.11/doctest.h --output-document=/usr/local/include/doctest.h

RUN pip3 install --break-system-packages \
      cpplint \
      PyYAML \
 && true
