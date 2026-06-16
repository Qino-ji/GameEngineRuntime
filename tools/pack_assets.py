#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description="Create a simple atlas manifest.")
    parser.add_argument("images", nargs="+", type=Path)
    parser.add_argument("-o", "--output", type=Path, required=True)
    args = parser.parse_args()

    missing = [str(path) for path in args.images if not path.exists()]
    if missing:
        print("missing images:")
        for path in missing:
            print(f"  {path}")
        return 1

    manifest = {
        "version": 1,
        "images": [str(path) for path in args.images],
        "atlas": {
            "width": 0,
            "height": 0,
            "cells": [],
        },
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
