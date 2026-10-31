import json

d = json.load(open('asm/pal3/decomp/CCBAI_HandleEnemyActionint_004d71e0.json', encoding='utf-8'))
print('size:', d['size_bytes'], '| sig:', d['signature'])
print(d['decompiled_c'][:1800])
