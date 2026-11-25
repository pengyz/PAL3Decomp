#!/usr/bin/env python3
"""census_cscreenmode44_20261125.py — CScreenMode 44 留守方法归属普查 (单遍扫描)。
语料全文件一次读入, 按方法名建索引后逐文件扫调用形。
输出: 接收者类型分类 → 迁移/留/另案 三色清单。
"""
import json, re, os, collections

# 1. 44 留守方法
cm = json.load(open('data/annotations/structs/CScreenMode.json', encoding='utf-8'))
all_methods = {str(m.get('name')): a for a, m in (cm.get('methods') or {}).items()}
# 已迁 27 个的单例族名单 (不重复普查)
migrated = {'GetInstance','AudioSetPosition','GetAudioManager','AudioStopAll','AudioFadeOut',
  'PlaySoundStream','AudioUpdate','StopAll','StopAllAudio','PlayCombatMusic','PlaySceneMusic',
  'PlaySoundIfEnabled','PlayAmbientSound','SetMode','Restore','ApplyColorFilter','PlayVideo',
  'CreateDevice','SetViewport','GetWidth','GetHeight','IsAudioReady','GetSoundList',
  'InitSceneAudio','SetAudioParam','InitCPK','PlayCPKStream'}
stray = {nm: a for nm, a in all_methods.items() if nm not in migrated}
print('CScreenMode 总方法 %d, 已迁 %d, 留守 %d' % (len(all_methods), len(migrated), len(stray)))

# 2. 单遍语料扫描: 找 (cast)->Cls::Method( 形
recv = {nm: collections.Counter() for nm in stray}
recv_samples = {nm: [] for nm in stray}
# 预编译一个大 alternation
names_pat = '|'.join(re.escape(n) for n in sorted(stray, key=len, reverse=True))
call_re = re.compile(
    r'\(\s*\(\s*\(\?\s*(\w[\w<> ]*)\s*\*\s*\)\s*\(?([^)&;]{1,60}?)\)?\s*\)\s*\)\s*->\s*\w+::(' + names_pat + r')\s*\('
)
file_count = 0
for root, dirs, files in os.walk('pal3/src'):
    for fn in files:
        if not fn.endswith('.cpp'):
            continue
        p = os.path.join(root, fn)
        try:
            txt = open(p, encoding='utf-8', errors='replace').read()
        except Exception:
            continue
        file_count += 1
        for m in call_re.finditer(txt):
            cast_t, recv_e, meth = m.group(1), m.group(2).strip(), m.group(3)
            if meth not in recv:
                continue
            if 'g_ScreenMode' in recv_e:
                recv[meth]['singleton'] += 1
            elif recv_e.startswith('this'):
                recv[meth]['this(不确定宿主)'] += 1
            else:
                recv[meth]['other:' + recv_e[:20]] += 1
            if len(recv_samples[meth]) < 1:
                recv_samples[meth].append('%s:%s' % (fn, m.group(0)[:80]))

print('扫描 %d 文件' % file_count)
# 3. 三色分类
green, yellow, red = [], [], []
for nm, a in sorted(stray.items()):
    r = recv[nm]
    total = sum(r.values())
    if total == 0:
        red.append((nm, a, '零语料调用'))
    elif r['singleton'] > 0 and r['singleton'] >= total * 0.5:
        green.append((nm, a, dict(r.most_common(2)), '单例族→gbBinkVideo'))
    elif r['this(不确定宿主)'] > 0 or r['other:']:
        yellow.append((nm, a, dict(r.most_common(2)), '混合/他宿主'))
    else:
        red.append((nm, a, dict(r.most_common(2)), '无匹配'))

print('\n=== 绿灯(单例族→gbBinkVideo) %d ===' % len(green))
for nm, a, r, note in green:
    print('  %-24s %s' % (nm, r))
print('\n=== 黄灯(混合/他宿主) %d ===' % len(yellow))
for nm, a, r, note in yellow:
    print('  %-24s %s' % (nm, r))
print('\n=== 红灯(零调用/无匹配) %d ===' % len(red))
for nm, a, r in red:
    print('  %-24s %s' % (nm, r))

out = {'green': [{'name': n, 'addr': a, 'recv': r} for n, a, r, _ in green],
       'yellow': [{'name': n, 'addr': a, 'recv': r} for n, a, r, _ in yellow],
       'red': [{'name': n, 'addr': a, 'recv': r} for n, a, r in red]}
json.dump(out, open('data/status/cscreenmode44_census_20261125.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)
print('\n→ data/status/cscreenmode44_census_20261125.json')
