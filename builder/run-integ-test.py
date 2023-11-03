#!/usr/bin/env python3

import subprocess
import sys
import textwrap

import yaml


def main(argv):
    success = True

    with open(argv[1]) as f:
        test = yaml.load(f, Loader=yaml.SafeLoader)

    if "setup" in test:
        setup = textwrap.dedent("""
            set -o errexit
            set -o nounset
            set -o pipefail
        """) + test["setup"]
        subprocess.run(["bash"], universal_newlines=True, input=setup, check=True)

    try:
        result = subprocess.run(
            test["command"],
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
            input=test.get("stdin", ""),
        )
    finally:
        if "teardown" in test:
            teardown = textwrap.dedent("""
                set -o errexit
                set -o nounset
                set -o pipefail
            """) + test["teardown"]
            subprocess.run(["bash"], universal_newlines=True, input=teardown, check=True)

    if test.get("returncode", result.returncode) != result.returncode:
        success = False
        print(f"Expected returncode: {test['returncode']}", file=sys.stderr)
        print(f"Actual returncode: {result.returncode}", file=sys.stderr)
    test["returncode"] = result.returncode

    expected_stderr = test.get("stderr", result.stderr)
    actual_stderr = result.stderr.strip()
    if expected_stderr is not None:
        expected_stderr = expected_stderr.strip()
        if actual_stderr != expected_stderr:
            success = False
            print(f"Expected stderr:", file=sys.stderr)
            print(test["stderr"], file=sys.stderr)
            print(f"Actual stderr:", file=sys.stderr)
            print(actual_stderr, file=sys.stderr)
        test["stderr"] = actual_stderr

    expected_stdout = test.get("stdout", result.stdout)
    actual_stdout = result.stdout.strip()
    if expected_stdout is not None:
        expected_stdout = expected_stdout.strip()
        if actual_stdout != expected_stdout:
            success = False
            print(f"Expected stdout:", file=sys.stderr)
            print(test["stdout"], file=sys.stderr)
            print(f"Actual stdout:", file=sys.stderr)
            print(actual_stdout, file=sys.stderr)
        test["stdout"] = actual_stdout


    # Auto-fix the test to match reality
    with open(argv[1], "w") as f:
        # Emit YAML by hand to get the precise formatting I want
        if "setup" in test:
            f.write(f"setup: |\n")
            for line in test["setup"].splitlines():
                f.write(f"  {line}\n")
        f.write(f"command: {test['command']}\n")
        if "stdin" in test:
            f.write(f"stdin: |\n")
            for line in test["stdin"].splitlines():
                f.write(f"  {line}\n")
        if "teardown" in test:
            f.write(f"teardown: |\n")
            for line in test["teardown"].splitlines():
                f.write(f"  {line}\n")
        f.write(f"returncode: {test['returncode']}\n")
        if test["stderr"] is None:
            f.write(f"stderr: null\n")
        else:
            f.write(f"stderr: |\n")
            for line in test["stderr"].splitlines():
                f.write(f"  {line}\n")
        if test["stdout"] is None:
            f.write(f"stdout: null\n")
        else:
            f.write(f"stdout: |\n")
            for line in test["stdout"].splitlines():
                f.write(f"  {line}\n")

    return success


if __name__ == '__main__':
    exit(0 if main(sys.argv) else 1)
