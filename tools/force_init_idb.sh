#!/bin/bash
# Force Init IDB（从 0 构建，清除脏数据）
# 
# 背景（用户质疑 2026-10-22）：
#   apply 是增量叠加（无全删）=> 脏数据累积
#   CEffMgr 全是 _tail_000 · script_state/m_state 不在 IDA
#   => 可能是脏数据，非 IDA 问题
#
# 用法：bash tools/force_init_idb.sh
# 风险：IDA 全量分析 ~10 分钟 + 可能丢手工注解
set -e

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
IDB="$ROOT/original/PAL3.exe.i64"
BACKUP="$ROOT/original/PAL3.exe.i64.bak.$(date +%Y%m%d_%H%M%S)"

echo "=== Force Init IDB ==="
echo "1. 备份当前 IDB"
if [ -f "$IDB" ]; then
    cp "$IDB" "$BACKUP"
    echo "   备份: $BACKUP ($(stat -c%s "$BACKUP") bytes)"
fi

echo "2. 删除 IDB（从 0 重建）"
rm -f "$IDB"
echo "   已删除: $IDB"

echo "3. 备份当前 ida_structs.json（用于对比）"
STRUCTS="$ROOT/asm/pal3/ida_structs.json"
if [ -f "$STRUCTS" ]; then
    cp "$STRUCTS" "$STRUCTS.bak.$(date +%Y%m%d_%H%M%S)"
    echo "   备份: $STRUCTS.bak.*"
fi

echo ""
echo "=== 待手动执行 ==="
echo "4. IDA 重开（从 0 分析）:"
echo "   idb_open(input_path='original/PAL3.exe')"
echo ""
echo "5. 干净 apply:"
echo "   python pipeline/cli.py apply"
echo ""
echo "6. export:"
echo "   python pipeline/cli.py export"
echo ""
echo "7. 对比 ida_structs.json 前后差异:"
echo "   diff <(python3 -c \"import json; d=json.load(open('$STRUCTS.bak')); print(len(d))\") \\"
echo "        <(python3 -c \"import json; d=json.load(open('$STRUCTS')); print(len(d))\")"
