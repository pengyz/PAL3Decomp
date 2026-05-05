#@category PAL3A
import json


def format_address(address):
    return '0x{:08X}'.format(int(address.getOffset()))


program = currentProgram
listing = program.getListing()
symbol_table = program.getSymbolTable()
function_manager = program.getFunctionManager()

output = {
    'image_base': format_address(program.getImageBase()),
    'functions': [],
    'globals': [],
    'types': [],
}

for function in function_manager.getFunctions(True):
    output['functions'].append({
        'address': format_address(function.getEntryPoint()),
        'name': function.getName(),
        'source_file': str(function.getSymbol().getSource()),
        'return_type': str(function.getReturnType()),
        'parameters': [str(p.getDataType()) + ' ' + p.getName() for p in function.getParameters()],
    })

for symbol in symbol_table.getAllSymbols(True):
    if symbol.isGlobal() and symbol.getAddress().isMemoryAddress():
        output['globals'].append({
            'address': format_address(symbol.getAddress()),
            'name': symbol.getName(),
            'datatype': '',
        })

with open(askFile('Save PAL3A symbol export', 'Save').getAbsolutePath(), 'w') as fp:
    json.dump(output, fp, indent=2)
