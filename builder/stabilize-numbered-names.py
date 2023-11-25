#!/usr/bin/env python3

import fileinput
import re
import sys


name_regex = re.compile(r'\b__[a-zA-Z_]*[a-zA-Z]\d+\b')

def main():
    new_names = {}
    for line in fileinput.input():
        for old_name in set(name_regex.findall(line)):
            prefix = old_name.rstrip("0123456789")
            new_name = new_names.setdefault(prefix, {}).setdefault(old_name, f"{prefix}{len(new_names[prefix])}")
            line = line.replace(old_name, new_name)
        print(line, end='')


if __name__ == '__main__':
    main()
