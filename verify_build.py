#!/usr/bin/env python3
"""
PAL3 Decompilation - Build Verification
Verifies that all targets compile successfully.
"""

import subprocess
import sys
import os
from pathlib import Path

TARGET_OUTPUTS = {
    "pal3": "PAL3.exe",
    "topo": "topo.dll",
    "gbengine": "gbengine.dll",
    "pal3a": "PAL3A.exe",
}


def run_command(cmd, description):
    print(f"\n{'='*60}")
    print(f"[*] {description}")
    print(f"{'='*60}")

    result = subprocess.run(cmd, shell=True, capture_output=True, text=True, encoding='gbk', errors='ignore')

    if result.returncode != 0:
        print(f"[FAIL] {description}")
        print(result.stdout[-500:] if result.stdout else "")
        print(result.stderr[-500:] if result.stderr else "")
        return False

    print(f"[PASS] {description}")
    return True


def verify_target(target, output_name, generator="Visual Studio 17 2022"):
    """Verify a single build target."""
    build_dir = f"build_{target}"

    if generator == "Visual Studio 17 2022":
        cfg_cmd = f'cmake -B {build_dir} -S . -G "{generator}" -A Win32 -DBUILD_TARGET={target}'
    else:
        cfg_cmd = f'cmake -B {build_dir} -S . -G "{generator}" -DCMAKE_BUILD_TYPE=Release -DBUILD_TARGET={target}'

    if not run_command(cfg_cmd, f"Configure {target}"):
        return False

    if not run_command(f'cmake --build {build_dir} --config Release', f"Build {target}"):
        return False

    output_path = Path(build_dir) / "Release" / output_name
    if not output_path.exists():
        output_path = Path(build_dir) / output_name

    if output_path.exists():
        size = output_path.stat().st_size
        print(f"  [OK] {output_name} ({size:,} bytes)")
        return True
    else:
        print(f"  [FAIL] {output_name} not found")
        return False


def main():
    os.chdir(Path(__file__).parent)

    targets = sys.argv[1:] if len(sys.argv) > 1 else ["pal3", "topo", "pal3a"]
    invalid_targets = [target for target in targets if target not in TARGET_OUTPUTS]
    if invalid_targets:
        print("Unknown target(s): {}".format(', '.join(invalid_targets)))
        print("Valid targets: {}".format(', '.join(TARGET_OUTPUTS.keys())))
        sys.exit(1)

    print(f"\nPAL3 Build Verification - Targets: {', '.join(targets)}\n")

    results = {}
    for target in targets:
        results[target] = verify_target(target, TARGET_OUTPUTS[target])

    print(f"\n{'='*60}")
    print("RESULTS:")
    for t, ok in results.items():
        status = "PASS" if ok else "FAIL"
        print(f"  [{status}] {t}")
    print(f"{'='*60}")

    sys.exit(0 if all(results.values()) else 1)


if __name__ == "__main__":
    main()
