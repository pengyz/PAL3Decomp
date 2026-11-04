#!/bin/bash
# B 转换证明门禁（spec v2 §2·R9）：mutation+fixture+matrix 三证串跑。
# 触发面：.git/hooks/pre-commit 检测转换器/证明器 9 件改动时调用。
# 环境注记：三证全离线（不需要 daemon；daemon 互斥持库+端口 8432 约束属活体证明
# verify_b_import/fixture live 面，不在本 gate）。
# GATE_TEST_PATH env 可覆写测试面（红传播测试用）。
set -e
cd "$(dirname "$0")/.."
TESTS="${GATE_TEST_PATH:-tests/test_mutation_proof.py tests/test_fixture_proof.py tests/test_proof_matrix.py}"
python3 -m pytest $TESTS -q
