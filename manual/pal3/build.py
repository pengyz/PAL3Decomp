# build.py - source collection + NMake invocation (out-of-tree)
# Generates objs.txt from recursive source glob, then runs nmake
import os
import subprocess
import sys

def main():
    src_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(src_dir, 'build')
    os.makedirs(build_dir, exist_ok=True)

    # Recursive source collection (auto - no hardcoded subdirs)
    sources = []
    for root, dirs, files in os.walk(src_dir):
        if 'build' in root:
            continue
        for f in files:
            if f.endswith('.cpp'):
                sources.append(os.path.join(root, f))

    # Generate objs.txt (NMake include format)
    objs = [os.path.join(build_dir, os.path.splitext(os.path.basename(s))[0] + '.obj') for s in sources]
    with open(os.path.join(build_dir, 'objs.txt'), 'w') as f:
        f.write('OBJS = ' + ' '.join(objs) + '\n')

    print('Sources: %d' % len(sources))
    print('Objects: %d' % len(objs))

    # Run nmake
    nmake = os.path.join(src_dir, '..', '..', 'tools', 'compilers', 'msvc6.0', 'bin', 'nmake.exe')
    env = os.environ.copy()
    env['INCLUDE'] = r'..\..\tools\compilers\msvc6.0\include;..\..\tools\vc6\Include;..\..\include;..\..\include\gbengine'
    env['LIB'] = r'..\..\tools\compilers\msvc6.0\lib;..\..\tools\vc6\Lib;..\..\gbengine'
    result = subprocess.run([nmake, '/f', 'Makefile'], cwd=src_dir, env=env)
    return result.returncode

if __name__ == '__main__':
    sys.exit(main())
