# 工具脚本

独立命令行工具，不属于自动化管线但在开发中有用。

## 字节对比

| 脚本 | 用途 | 用法 |
|------|------|------|
| `compare.py` | 对比生成的 .obj 与原始 .obj 的字节差异 | `python tools/compare.py` |
| `compare_exe.py` | 对比完整 exe 文件 | `python tools/compare_exe.py build/PAL3.exe original/PAL3.exe` |
| `compare_function.py` | 对比单个函数的字节 | `python tools/compare_function.py 0x401000` |
| `gbengine_compare.py` | 对比 gbengine.dll | `python tools/gbengine_compare.py` |

## 函数匹配

| 脚本 | 用途 |
|------|------|
| `ida_class_cluster_match.py` | 按类聚类匹配函数 |
| `ida_enhanced_order_match.py` | 增强顺序匹配 |
| `pal3_strict_match_local.py` | 严格本地匹配 |
| `topo_compare.py` | 拓扑排序对比 |

## 进度统计

| 脚本 | 用途 |
|------|------|
| `progress.py` | 总体进度（函数匹配率） |
| `progress_pal3.py` | PAL3.exe 进度 |
| `gbengine_progress.py` | gbengine.dll 进度 |

## 数据导出

| 脚本 | 用途 |
|------|------|
| `dia_export_bases.py` | DIA SDK: 导出类继承关系 |
| `dia_export_structs.py` | DIA SDK: 导出结构体定义 |
| `create_pal3_sig.py` | 生成 FLIRT 签名文件 |
| `extract_pal3a_sources.py` | 提取 PAL3A 源码参考 |
