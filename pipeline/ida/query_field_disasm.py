"""
Deep binary analysis of unnamed struct fields.
For each _todo_ field with cross-references, extracts:
- Full disassembly context (instruction bytes + mnemonics)
- Register source tracing
- Access width and type
- Calling function context

Target classes: provided as comma-separated arg or reads from todo_field_context.json
"""
import json, os, sys
import idc
import idautils
import idaapi
import ida_bytes
import ida_nalt
import ida_xref
import ida_funcs

def get_insn_bytes(ea, size=8):
    """Get raw instruction bytes at ea."""
    data = ida_bytes.get_bytes(ea, size)
    if data:
        return ' '.join('%02X' % b for b in data)
    return ''

def analyze_field_access(ea, field_off, field_name):
    """Deep analysis of a field access at a given address."""
    result = {}
    result['va'] = ea
    result['field_offset'] = field_off
    
    # Get function info
    func = idaapi.get_func(ea)
    if func:
        result['function'] = idc.get_func_name(ea)
        # Get function start bytes
        func_bytes = ida_bytes.get_bytes(func.start_ea, min(16, func.end_ea - func.start_ea))
        result['func_prologue'] = ' '.join('%02X' % b for b in func_bytes) if func_bytes else ''
    else:
        result['function'] = ''
        result['func_prologue'] = ''
    
    # Get instruction info
    insn = idaapi.insn_t()
    if idaapi.decode_insn(insn, ea):
        result['mnemonic'] = insn.get_canon_mnemonic()
        result['bytes'] = get_insn_bytes(ea, insn.size)
        result['disasm'] = idc.generate_disasm_line(ea, 0).strip()
        
        # Detect operation type
        ops = []
        for i in range(2):
            op = insn.ops[i]
            if op.type == idaapi.o_void:
                break
            op_info = {
                'type': str(op.type),
                'dtype': str(op.dtype),
                'has_disp': hasattr(op, 'addr') and op.addr != 0,
            }
            if hasattr(op, 'addr') and op.addr:
                op_info['disp'] = op.addr
            ops.append(op_info)
        result['operands'] = ops
        
        # Determine access type
        mnem = insn.get_canon_mnemonic()
        if mnem.startswith('fld') or mnem.startswith('fst') or mnem.startswith('fadd') or mnem.startswith('fcomp') or mnem.startswith('fmul'):
            result['access_type'] = 'float'
        elif mnem.startswith('movzx') or mnem.startswith('movsx'):
            result['access_type'] = 'load_' + ('byte' if 'b' in mnem else 'word')
        elif mnem == 'mov' and insn.ops[1].dtype == idaapi.dt_byte:
            result['access_type'] = 'load_byte'
        elif mnem == 'mov' and insn.ops[0].dtype == idaapi.dt_byte:
            result['access_type'] = 'store_byte'
        elif mnem in ('add', 'sub', 'cmp', 'test', 'and', 'or', 'xor', 'imul'):
            result['access_type'] = 'integer_op'
        elif mnem == 'lea':
            result['access_type'] = 'address_of'
        else:
            result['access_type'] = mnem
        
        # Check if operand references our field offset
        result['field_in_operand'] = False
        for op in insn.ops:
            if hasattr(op, 'addr') and op.addr == field_off:
                result['field_in_operand'] = True
            # Also check if operand reg points to this+field_off
            if op.type == idaapi.o_displ:
                if hasattr(op, 'addr') and op.addr == field_off:
                    result['field_in_operand'] = True
    else:
        result['mnemonic'] = ''
        result['bytes'] = ''
        result['disasm'] = ''
        result['access_type'] = 'unknown'
    
    return result

def main():
    # Determine output path
    todo_path = os.path.join(os.path.dirname(__file__), '_logs', 'todo_field_context.json')
    
    if len(idc.ARGV) > 1:
        # Format: -S"script.py class1,class2"
        target_classes = idc.ARGV[1].split(',')
    else:
        # Use all classes from todo_field_context
        target_classes = None
    
    # Load todo fields
    all_results = {}
    try:
        with open(todo_path, 'r') as f:
            todo_data = json.load(f)
    except:
        todo_data = {}
    
    if target_classes:
        classes_to_check = [c for c in target_classes if c in todo_data]
    else:
        # Focus on top classes by field count
        sorted_classes = sorted(todo_data.items(), key=lambda x: -len(x[1]))
        classes_to_check = [c for c, _ in sorted_classes[:10]]
    
    print("DISASSEMBLY ANALYSIS for classes: %s" % ', '.join(classes_to_check))
    
    for cls_name in classes_to_check:
        fields = todo_data.get(cls_name, {})
        cls_results = {}
        print("\n=== %s (%d fields) ===" % (cls_name, len(fields)))
        
        for off_str, finfo in sorted(fields.items(), key=lambda k: int(k) if str(k).isdigit() else 9999):
            if not str(off_str).isdigit():
                continue
            off = int(off_str)
            
            refs = finfo.get('refs', [])
            if not refs:
                continue
            
            field_results = []
            for ref in refs[:8]:  # Max 8 refs per field
                if isinstance(ref, dict):
                    ea = ref.get('ea', 0)
                    if ea:
                        analysis = analyze_field_access(ea, off, finfo.get('name', ''))
                        field_results.append(analysis)
                        print("  +0x%04X func=%s VA=0x%X: %s" % (
                            off, analysis.get('function','?'), ea,
                            analysis.get('disasm','?')[:90]))
            
            if field_results:
                cls_results[off_str] = field_results
        
        if cls_results:
            all_results[cls_name] = cls_results
    
    # Write results
    out_dir = os.path.join(os.path.dirname(__file__), '_logs')
    out_path = os.path.join(out_dir, 'field_disasm_analysis.json')
    with open(out_path, 'w') as f:
        json.dump(all_results, f, indent=2, default=str)
    print("\nResults written to: %s" % out_path)

if __name__ == '__main__':
    main()
    idc.qexit(0)
