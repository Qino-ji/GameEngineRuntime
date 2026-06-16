#!/usr/bin/env python3
from __future__ import annotations

import argparse
import shutil
import subprocess
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description="Compile WGSL to SPIR-V when a compiler is available.")
    parser.add_argument("input", type=Path)
    parser.add_argument("-o", "--output", type=Path)
    parser.add_argument("--compiler", default="dxc")
    args = parser.parse_args()

    compiler = shutil.which(args.compiler)
    if compiler is None:
        print(f"compiler not found: {args.compiler}")
        return 2

    cmd = [compiler, "-T", "cs_6_6", "-spirv", str(args.input), "-Fo", str(args.output)]
    return subprocess.run(cmd, check=False).returncode


if __name__ == "__main__":
    raise SystemExit(main())
