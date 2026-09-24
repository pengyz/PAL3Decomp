#!/usr/bin/env python3
"""vtable call 转换器：_tail_000 间接调用 → 直接虚方法调用。"""
import re, os, sys, glob

# gbGfxManager vtable
VT = {1:'MsgProc',2:'NewTexture',3:'NewMesh',4:'NewVertexPool',5:'NewIndexPool',
      6:'NewDynVertBuf',7:'SetFrustum',8:'SetOrtho',9:'SetViewport',10:'SetLight',
      11:'SetMaterial',12:'BeginScene',13:'Present',14:'DrawIndexedPrimitive',
      15:'DrawPrimitive',16:'GetFrustumPlanes',17:'GetGfxCaps',18:'ApplyTransform',
      19:'SetGammaRamp'}

def transform(src):
    """转换 _tail_000 vtable 调用。"""
    count = 0
    
    # 模式 1: (*(ret(**)(Class,params))(*(_DWORD *)obj->_tail_000 + OFFSET))(obj, args)
    # 简化为两步:
    # Step A: 找到 `obj->_tail_000 + OFFSET` 的 slot
    # Step B: 替换周围的函数指针调用结构
    
    # 窄模式 1: 标准格式（单行，可跨行但结构固定）
    # ((*)obj->_tail_000 + N))(obj → obj->Method(
    def repl(m):
        nonlocal count
        obj = m.group(1)
        off = int(m.group(2))
        slot = off // 4
        method = VT.get(slot)
        if method:
            count += 1
            return f'\n__VT_CALL__ {obj}->{method}('
        return m.group(0)
    
    # 精确匹配 _tail_000 + OFFSET 后的调用括号
    src = re.sub(
        r'([\w>]+(?:\.\w+)*(?:->\w+)*)->_tail_000\s*\+\s*(\d+)\)\s*\)\s*\(\s*\n?\s*',
        repl, src)
    
    # Step B: 移除函数指针类型转换前缀（在 __VT_CALL__ 标记之前的旧代码）
    # 这需要多行处理，简化为移除 `(*(任意类型))` 紧邻 __VT_CALL__ 的模式
    src = re.sub(
        r'\(\*[^)]*\)\s*\n?\s*__VT_CALL__\s*',
        '__VT_CALL__ ',
        src)
    
    # Step C: 将 __VT_CALL__ 替换为空（已经内联到正确的调用形式）
    src = src.replace('__VT_CALL__ ', '')
    
    # 模式 2: (**(ptr to ptr))obj->_tail_000 (简化调用 slot 0)
    src = re.sub(
        r'\(\*\*[^)]+\)(\w+(?:->\w+)*)->_tail_000\b',
        r'\1->', src)
    
    return src, count

def main():
    dry_run = '--dry-run' in sys.argv
    files = []
    args = sys.argv[1:]
    i = 0
    while i < len(args):
        if args[i] == '--file' and i+1 < len(args):
            files.append(args[i+1]); i += 2
        elif not args[i].startswith('-'): files.append(args[i]); i += 1
        else: i += 1
    if not files:
        files = [f for f in glob.glob('pal3/src/**/*.cpp', recursive=True)
                 if '_tail_000' in open(f, errors='replace').read()]
    
    total = 0
    for f in files:
        src = open(f, encoding='utf-8', errors='replace').read()
        if '_tail_000' not in src: continue
        new_src, count = transform(src)
        if count > 0:
            print(f'  {f}: {count} transforms')
            total += count
            if not dry_run:
                open(f, 'w', encoding='utf-8').write(new_src)
    print(f'Total: {total} transforms{" [DRY-RUN]" if dry_run else ""}')

if __name__ == '__main__':
    main()
