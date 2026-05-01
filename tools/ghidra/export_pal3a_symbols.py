#@category PAL3A
import json

program = currentProgram
listing = program.getListing()
symbol_table = program.getSymbolTable()
function_manager = program.getFunctionManager()

output = {
    'image_base': str(program.getImageBase()),
    'functions': [],
    'globals': [],
    'types': [],
}

for function in function_manager.getFunctions(True):
    output['functions'].append({
        'address': str(function.getEntryPoint()),
        'name': function.getName(),
        'source_file': str(function.getSymbol().getSource()),
        'return_type': str(function.getReturnType()),
        'parameters': [str(p.getDataType()) + ' ' + p.getName() for p in function.getParameters()],
    })

for symbol in symbol_table.getAllSymbols(True):
    if symbol.isGlobal() and symbol.getAddress().isMemoryAddress():
        output['globals'].append({
            'address': str(symbol.getAddress()),
            'name': symbol.getName(),
            'datatype': '',
        })

with open(askFile('Save PAL3A symbol export', 'Save').getAbsolutePath(), 'w') as fp:
    json.dump(output, fp, indent=2)
