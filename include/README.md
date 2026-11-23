# include/ — 头文件域

- `pal3/gen/` — codegen 生成的类头镜像（pal3/src 的 .h 双址写出侧；C2143 shim 指回 pal3/src）
- `pal3/ida_defs.h` / `pal3/pal3_constants.h` — hexrays 伪宏词汇表与常量（手工维护的生成依赖）
- `pal3/gen/_ns_udts.h` — 共享 ns 域 UDT（宏守卫 PAL3_NS_UDTS_H_，双址镜像防跨路径重定义）
- `gbengine/` — 引擎头（真产物解析源，type_resolver gbengine 域）
