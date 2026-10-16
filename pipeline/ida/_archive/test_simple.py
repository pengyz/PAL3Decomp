import json, os
LOG_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs")
with open(os.path.join(LOG_DIR, "test_simple.json"), 'w') as f:
    json.dump({"test": "hello"}, f)
import idc
idc.qexit(0)
