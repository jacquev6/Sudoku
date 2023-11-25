#!/usr/bin/env python3

import fileinput
import re
import sys


lambda_regex = re.compile(r'__lambda_\d+_\d+')

def main():
    new_names = {}
    for line in fileinput.input():
        for old_name in set(lambda_regex.findall(line)):
            new_name = new_names.setdefault(old_name, f"__lambda_{len(new_names)}")
            line = line.replace(old_name, new_name)
        print(line, end='')


if __name__ == '__main__':
    main()
