#!/usr/bin/env python3

# A very crude C preprocessor handling only '#include "local-header.hpp"'
# to work around https://github.com/andreasfertig/cppinsights/issues/428

import os.path
import sys


def main(args):
    seen = set()
    def cat(file_path):
        assert file_path not in seen, (file_path, seen)
        seen.add(file_path)
        print(f'# 1 "{file_path}"')
        with open(file_path) as f:
            for line_index, line in enumerate(f):
                if (
                    line.startswith('#include "')
                    and line.endswith('"\n')
                ):
                    included_path = os.path.normpath(os.path.join(os.path.dirname(file_path), line[10:-2]))
                    if included_path not in seen:
                        cat(included_path)
                    print(f'# {line_index + 2} "{file_path}"')
                else:
                    print(line, end='')
    cat(args[0])


if __name__ == '__main__':
    main(sys.argv[1:])
