#!/usr/bin/env python3
"""Hex-Rays/IDA 约定 token 的归一化单点律（治理：单点律扩展 2026-11-10）。

历史：__ovl_ 剥除曾单点收编（strip_ovl 于 annotation_view），而
__return_ptr / __hidden / scalar-dtor 三族仍各有 3-5 份副本——副本间已发生
行为漂移（data.py scalar-dtor 写点漏反引号归一化；data.py __return_ptr
无 count=1 而 stage1 有——sret 每签名至多一个故等价，但属隐性契约）。

本模块收编后，各副本改调单点；新增归一化规则只改这里。
"""

import re

# --- __return_ptr（Hex-Rays sret 隐式指针参数；每签名至多一个） ---

_RET_PTR_PARAM = r'\s*,?\s*[A-Za-z_][\w:]*(?:\s*\*+)?\s*__return_ptr\s+\w+\s*,?'

def strip_return_ptr(sig):
    """从函数签名剥 sret 隐式指针参数并清理逗号残渣 + 返回类型降一级指针。"""
    if '__return_ptr' not in sig:
        return sig
    sig = re.sub(_RET_PTR_PARAM, ' ', sig)
    sig = re.sub(r'\(\s*,', '(', sig)
    sig = re.sub(r',\s*\)', ')', sig)
    p0 = sig.find('(')
    if p0 > 0:
        j = sig[:p0].rstrip().rfind('*')
        if j != -1:
            sig = sig[:j] + sig[j + 1:]
    return sig

def has_return_ptr(sig_or_code):
    return '__return_ptr' in sig_or_code

# --- __hidden（IDA this 形参显示约定；永非合法 C++，全局剥安全） ---

def strip_hidden(text):
    """剥全部 __hidden token（含其后的一个空白）。"""
    return re.sub(r'\b__hidden\b\s*', '', text)

# --- dtor 名归一（`` `scalar deleting destructor' `` → _scalar_dtor 等） ---

def normalize_dtor_name(name):
    """反引号形 dtor 名 → 规范 _scalar_dtor/_vector_dtor 形。"""
    name = re.sub(r'`?\s*scalar deleting destructor\s*\'?', '_scalar_dtor', name)
    name = re.sub(r'`?\s*vector deleting destructor\s*\'?', '_vector_dtor', name)
    return name.strip()
