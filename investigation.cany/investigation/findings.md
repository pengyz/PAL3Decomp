# Findings

- **fnd_1** S2 131/215 回归的根因是全局命名冲突：0x583A9C（串池首串 "fivemagic"）的标注名 dir 与 0x58B44C（"role"）的 IDB 名 dir 撞名，IDA 实落 dir_0 而 globals.h 发 dir，导致 33 个单元报 C2065 'dir_0'（并级联 C2109/C2102）。改为唯一名 aFivemagic 后全链验证：S2 141/215、总错 800、dir_0 C2065 归零。 (Seen it; evidence: ev_3ff7b3b6faab6dae691004109f5aa7553d3a0d2884a5ed9fb324b508aa72f93d, ev_6ee7f47254c30b2356e4337ae023ab1ed3ecf05231f682ccb919fe5bdb4aabb2)
