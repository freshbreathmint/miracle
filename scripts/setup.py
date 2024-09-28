#!/usr/bin/env python3

import configparser
import os
import shutil
import sys

def copy_contents(source_dir, target_dir):
    if not os.path.exists(source_dir):
        print("Source directory does not exist:", source_dir)
        sys.exit(1)
    for item in os.listdir(source_dir):
        s = os.path.join(source_dir, item)
        d = os.path.join(target_dir, item)
        if os.path.isdir(s):
            if os.path.exists(d):
                shutil.rmtree(d)
            shutil.copytree(s, d)
        else:
            shutil.copy2(s, d)

def handle_application(name, script_dir):
    source_dir = os.path.join(script_dir, 'templates', 'application')
    # The target directory is the workspace directory (parent of miracle)
    miracle_dir = os.path.abspath(os.path.join(script_dir, '..'))
    workspace_dir = os.path.abspath(os.path.join(miracle_dir, '..'))
    target_dir = workspace_dir
    copy_contents(source_dir, target_dir)
    config_path = os.path.join(target_dir, 'config.ini')
    if not os.path.exists(config_path):
        print("config.ini not found in target directory.")
        sys.exit(1)
    config = configparser.ConfigParser()
    config.read(config_path)
    if 'application' not in config:
        config['application'] = {}
    config['application']['name'] = name
    with open(config_path, 'w') as configfile:
        config.write(configfile)
    print("Application setup completed.")

def handle_library(name, lib_type, script_dir):
    if lib_type == 'static':
        source_dir = os.path.join(script_dir, 'templates', 'library-static')
    else:
        source_dir = os.path.join(script_dir, 'templates', 'library-dynamic')
    # The target directory is the workspace directory
    miracle_dir = os.path.abspath(os.path.join(script_dir, '..'))
    workspace_dir = os.path.abspath(os.path.join(miracle_dir, '..'))
    target_dir = os.path.abspath(os.path.join(workspace_dir, name))
    if os.path.exists(target_dir):
        shutil.rmtree(target_dir)
    shutil.copytree(source_dir, target_dir)
    src_dir = os.path.join(target_dir, 'src')
    include_dir = os.path.join(target_dir, 'include')
    # Rename library_example.c to <name>.c
    old_c_file = os.path.join(src_dir, 'library_example.c')
    new_c_file = os.path.join(src_dir, f'{name}.c')
    if os.path.exists(old_c_file):
        os.rename(old_c_file, new_c_file)
        # Edit the new .c file
        with open(new_c_file, 'r') as f:
            content = f.read()
        content = content.replace('#include "library_example.h"', f'#include "{name}.h"')
        with open(new_c_file, 'w') as f:
            f.write(content)
    else:
        print(f"{old_c_file} does not exist.")
        sys.exit(1)
    # Rename library_example.h to <name>.h
    old_h_file = os.path.join(include_dir, 'library_example.h')
    new_h_file = os.path.join(include_dir, f'{name}.h')
    if os.path.exists(old_h_file):
        os.rename(old_h_file, new_h_file)
    else:
        print(f"{old_h_file} does not exist.")
        sys.exit(1)
    print("Library setup completed.")

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))

    if len(sys.argv) < 3:
        print("Usage: setup.py <target> <name> [static/dynamic]")
        sys.exit(1)
    target = sys.argv[1]
    name = sys.argv[2]
    if target == 'application':
        handle_application(name, script_dir)
    elif target == 'library':
        if len(sys.argv) < 4:
            print("Usage: setup.py library <name> <static/dynamic>")
            sys.exit(1)
        lib_type = sys.argv[3]
        if lib_type not in ['static', 'dynamic']:
            print("Third argument must be 'static' or 'dynamic'")
            sys.exit(1)
        handle_library(name, lib_type, script_dir)
    else:
        print("Unknown target:", target)
        sys.exit(1)

if __name__ == '__main__':
    main()
