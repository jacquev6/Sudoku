#!/usr/bin/env python3
# Copyright 2023 Vincent Jacques

import sys


assert len(sys.argv) == 2

left, right = sys.argv[1].split(":", 2)
width = 20  # Increase at will if next assert fails
assert(len(left) < width)
left = (left + ':').ljust(width)

print(f"  {left} {right.strip()}")
