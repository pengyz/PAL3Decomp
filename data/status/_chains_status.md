# 后台链状态（每 30 秒由监督作业刷新 ✓）

> 本文件 = **你能自己看到的证据** ✓（不依赖我的转述 ✓）。
> 自检命令：`bash data/status/chains_status.sh`
=== 现在 22:01:02 ===
--- 进程（PID / 已运行秒 / 命令）:
  353066  435s  /bin/bash /tmp/land5.sh
  360528  1s  /usr/bin/python3 pipeline/cli.py check
--- 日志末尾:
  [/tmp/recover4.log] 最后写 2026-09-20 22:00:54
      EXIT=0
      ===== RECOVER_DONE =====
  [/tmp/land5.log] 最后写 2026-09-20 22:01:00
      
      [Invariants] advisory 模式（只报告计数，不影响退出码）...
--- 指标:
  census ok=76 errors=2150 | L1=34 | matched=266/315
--- 注解改动数: 60
