# PAL3 Decompilation - 快捷命令
# ================================
#
# 使用方法:
#   make check       - 检查环境是否就绪
#   make pe-info     - 分析 PAL3.exe（编译器版本、段信息）
#   make imports     - 解析导入表，识别第三方库
#   make progress    - 查看反编译进度
#   make queue       - 显示推荐处理队列
#   make batch       - 批量编译对比所有已反编译函数
#   make clean       - 清理构建产物

PYTHON ?= python3
TOOLS  := tools
BUILD  := build
ASM    := asm
SRC    := src

.PHONY: help check pe-info imports progress queue batch clean stubs init

help:
	@echo "PAL3 反编译项目 - 可用命令:"
	@echo ""
	@echo "  环境/初始化:"
	@echo "    make init        初始化项目（首次）"
	@echo "    make check       检查工具链是否就绪"
	@echo ""
	@echo "  分析（需要 PAL3.exe）:"
	@echo "    make pe-info     分析 PE 头（编译器检测）"
	@echo "    make imports     解析导入表 + 识别第三方库"
	@echo "    make stubs       生成第三方库 stub 头文件"
	@echo ""
	@echo "  反编译工作流:"
	@echo "    make queue       显示推荐处理队列（优先级排序）"
	@echo "    make progress    查看整体进度"
	@echo "    make batch       批量编译对比"
	@echo ""
	@echo "  单函数处理:"
	@echo "    make decompile F=asm/FUN_xxx.json"
	@echo "    make compare S=src/core/xxx.c A=0x00401000 Z=128"
	@echo ""
	@echo "  其他:"
	@echo "    make clean       清理构建产物"
	@echo "    make rename      生成函数命名建议"

# ============================================================
# 环境 / 初始化
# ============================================================

init:
	$(PYTHON) $(TOOLS)/configure.py init

check:
	$(PYTHON) $(TOOLS)/configure.py check

# ============================================================
# 分析
# ============================================================

pe-info:
	$(PYTHON) $(TOOLS)/configure.py pe-info

imports:
	$(PYTHON) $(TOOLS)/analyze_imports.py

stubs:
	$(PYTHON) $(TOOLS)/analyze_imports.py --generate-stubs

# ============================================================
# 反编译工作流
# ============================================================

progress:
	$(PYTHON) $(TOOLS)/progress.py

queue:
	$(PYTHON) $(TOOLS)/prioritize.py

queue-detail:
	$(PYTHON) $(TOOLS)/prioritize.py --show-reasons --top 20

# 单函数反编译: make decompile F=asm/FUN_xxx.json
decompile:
ifndef F
	@echo "用法: make decompile F=asm/FUN_xxx_xxx.json"
	@echo "      make decompile F=asm/FUN_xxx_xxx.json DRY=1"
else
ifdef DRY
	$(PYTHON) $(TOOLS)/ai_decompile.py process --function $(F) --dry-run
else
	$(PYTHON) $(TOOLS)/ai_decompile.py process --function $(F)
endif
endif

# 批量反编译: make batch-ai [N=10]
N ?= 5
batch-ai:
	$(PYTHON) $(TOOLS)/ai_decompile.py batch --max-count $(N)

batch-ai-dry:
	$(PYTHON) $(TOOLS)/ai_decompile.py batch --max-count $(N) --dry-run

# 编译对比: make compare S=源文件 A=地址 Z=大小
compare:
ifndef S
	@echo "用法: make compare S=src/core/xxx.c A=0x00401000 Z=128"
else
	$(PYTHON) $(TOOLS)/compare.py --source $(S) --func-addr $(A) --func-size $(Z)
endif

# 批量对比所有已反编译函数
batch:
	$(PYTHON) $(TOOLS)/gen_batch.py
	$(PYTHON) $(TOOLS)/compare.py --batch $(BUILD)/batch_compare.json

# 函数命名建议
rename:
	$(PYTHON) $(TOOLS)/rename_helper.py

rename-apply:
	$(PYTHON) $(TOOLS)/rename_helper.py --apply

# ============================================================
# 清理
# ============================================================

clean:
	rm -rf $(BUILD)/*.obj $(BUILD)/*.asm $(BUILD)/*.map
	rm -rf $(BUILD)/compare_results/
	@echo "已清理构建产物"

clean-all: clean
	rm -rf $(BUILD)/
	@echo "已清理所有构建目录"
