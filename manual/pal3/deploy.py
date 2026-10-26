# manual/pal3 部署脚本（deploy——游戏目录替换）
# 阶段 2：可运行（编译产物→游戏目录→运行验证）
# 用法：python manual/pal3/deploy.py [game_dir]
import os
import shutil
import sys

def deploy(game_dir=None):
    if game_dir is None:
        game_dir = r'E:\Program Files (x86)\Steam\steamapps\common\PAL3'  # TODO: pipeline.toml [game] install_dir
    exe_name = 'PAL3.exe'
    backup_suffix = '.orig'

    src = os.path.join(os.path.dirname(__file__), 'PAL3_manual.exe')
    dst = os.path.join(game_dir, exe_name)
    backup = dst + backup_suffix

    # 1. 备份原 exe
    if os.path.exists(dst) and not os.path.exists(backup):
        shutil.copy2(dst, backup)
        print('Backup: %s -> %s' % (dst, backup))

    # 2. 复制编译产物
    shutil.copy2(src, dst)
    print('Deploy: %s -> %s' % (src, dst))

    # 3. 验证（存在性）
    if os.path.exists(dst):
        print('OK: %s deployed (%d bytes)' % (dst, os.path.getsize(dst)))
        return 0
    else:
        print('FAIL: %s not found' % dst)
        return 1

if __name__ == '__main__':
    game_dir = sys.argv[1] if len(sys.argv) > 1 else None
    sys.exit(deploy(game_dir))
