#!/usr/bin/env python3

import argparse
import configparser
import os
import subprocess
import sys
import time
from collections import defaultdict

def parse_config():
    config = configparser.ConfigParser()
    config.read('../config.ini')

    application = {
        'name': config.get('application', 'name'),
        'icon': config.get('application', 'icon'),
        'dependencies': config.get('application', 'dependencies').split(',') if config.get('application', 'dependencies') else []
    }

    libraries = {}
    for section in config.sections():
        if section.startswith('library.'):
            lib_name = section.split('library.')[1]
            lib_info = {
                'path': config.get(section, 'path'),
                'type': config.get(section, 'type'),
                'dependencies': config.get(section, 'dependencies').split(',') if config.get(section, 'dependencies') else []
            }
            libraries[lib_name] = lib_info

    return application, libraries

def get_directory(platform, build_type):
    if build_type == 'hot':
        return os.path.join(platform, 'debug')
    else:
        return os.path.join(platform, build_type)
    
def get_static_dependencies(target, application, libraries, resolved=None):
    if resolved is None:
        resolved = set()

    if target == 'application':
        dependencies = application['dependencies']
    else:
        dependencies = libraries[target]['dependencies']

    for dep in dependencies:
        if dep in libraries and libraries[dep]['type'] == 'static' and dep not in resolved:
            resolved.add(dep)
            get_static_dependencies(dep, application, libraries, resolved)

    return resolved

def topological_sort(to_build, application, libraries):
    # Build dependency graph
    graph = defaultdict(list)
    nodes = set()

    for target in to_build:
        nodes.add(target)
        if target == 'application':
            dependencies = application['dependencies']
        else:
            dependencies = libraries[target]['dependencies']
        for dep in dependencies:
                    graph[target].append(dep)
                    nodes.add(dep)

    visited = {}
    stack = []
    has_cycle = False
    
    def dfs(node):
        nonlocal has_cycle
        if node in visited:
            if visited[node] == 'visiting':
                has_cylce = True
            return
        visited[node] = 'visiting'
        for neighbor in graph[node]:
            dfs(neighbor)
        visited[node] = 'visited'
        stack.append(node)

    for node in nodes:
        if node not in visited:
            dfs(node)

    if has_cycle:
        print("Error: Cyclic dependency detected.")
        sys.exit(1)

    # Reverse the stack
    # sorted_order = stack[::-1]

    # Filter the sorted_order to include only the to_build targets
    final_build_order = [target for target in stack if target in to_build]

    return final_build_order

def generate_cmake(application, build_type, platform, bin_dir, to_build, libraries, exe, link_type):
    print("Generating CMakeLists.txt")
    print("Build targets:", to_build)

    cmake_lines = []

    # Project Details
    cmake_min_version = "VERSION 3.30"
    cmake_lines.append(f'cmake_minimum_required({cmake_min_version})\n')
    
    if build_type == 'release':
        cmake_lines.append(f'project({application["name"]})\n')
    else:    
        cmake_lines.append(f'project(executable)\n')

    # Set build type
    if build_type == 'hot':
        cmake_build_type = 'Debug'
    else:
        cmake_build_type = build_type.capitalize()
    cmake_lines.append(f'set(CMAKE_BUILD_TYPE {cmake_build_type})\n')

    # Set output directories
    cmake_lines.append(f'set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${{CMAKE_SOURCE_DIR}}/{bin_dir}")')
    cmake_lines.append(f'set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${{CMAKE_SOURCE_DIR}}/{bin_dir}")')
    cmake_lines.append(f'set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${{CMAKE_SOURCE_DIR}}/{bin_dir}")\n')

    # Hot Compile Timestamp
    if build_type == 'hot':
        timestamp = str(int(time.time()))
    else:
        timestamp = ''

    # Collect source files for each target
    cmake_lines.append('# Source Files')
    cmake_lines.append('file(GLOB_RECURSE MIRACLE_CORE_SRC "lib/core/src/*.c")\n')

    for target in to_build:
        if target == 'application':
            cmake_lines.append('file(GLOB_RECURSE APPLICATION_SRC "../src/*.c")')
        else:
            lib_info = libraries[target]
            lib_name = target
            lib_path = lib_info['path']
            cmake_lines.append(f'file(GLOB_RECURSE {lib_name.upper()}_SRC "../{lib_path}/src/*.c")')

    cmake_lines.append('')

    if exe == True:
        cmake_lines.append('file(GLOB_RECURSE INIH_SRC "lib/third_party/inih/src/*.c")')
        cmake_lines.append('file(GLOB_RECURSE EXE_SRC "executable/src/*.c")\n')

    # Build each specified library
    cmake_lines.append('# MIRACLE CORE')
    cmake_lines.append('add_library(miracle_core STATIC ${MIRACLE_CORE_SRC})')
    cmake_lines.append('target_include_directories(miracle_core PUBLIC lib/core/include)\n')

    if link_type == 'dynamic':
        cmake_lib_type = 'SHARED'
        definition = 'DYNAMIC_LINK'
    else:
        cmake_lib_type = 'STATIC'
        definition = 'STATIC_LINK'

    exe_deps = {}

    for target in to_build:
        cmake_lines.append(f'# {target.upper()}')
        if target == 'application':
            cmake_lines.append(f'add_library(application{timestamp} {cmake_lib_type} ${{APPLICATION_SRC}})')
            cmake_lines.append(f'target_include_directories(application{timestamp} PUBLIC ../include)')
            cmake_lines.append(f'target_compile_definitions(application{timestamp} PUBLIC -D{definition})')

            # Link dependencies
            cmake_deps = ['miracle_core'] # Always include miracle_core
            if link_type == 'static':
                filtered_deps = application['dependencies']
            else:
                filtered_deps = [dep for dep in application['dependencies'] if libraries.get(dep, {}).get('type') != 'dynamic']
            filtered_deps = [f'{dep}{timestamp}' if build_type == 'hot' else dep for dep in filtered_deps]
            cmake_deps.extend(filtered_deps)
            dep_str = ' '.join(cmake_deps)
            cmake_lines.append(f'target_link_libraries(application{timestamp} {dep_str})\n')
        else:
            lib_info = libraries[target]
            lib_name = target
            lib_type = lib_info['type']
            dependencies = lib_info['dependencies']

            # Determine library type
            if lib_type == 'static':
                cmake_lib_type = 'STATIC'
            else:
                if link_type == 'dynamic':
                    cmake_lib_type = 'SHARED'
                else:
                    cmake_lib_type = 'STATIC'

            cmake_lines.append(f'add_library({lib_name}{timestamp} {cmake_lib_type} ${{{lib_name.upper()}_SRC}})')
            cmake_lines.append(f'target_include_directories({lib_name}{timestamp} PUBLIC ../{lib_info['path']}/include)')
            cmake_lines.append(f'target_compile_definitions({lib_name}{timestamp} PUBLIC -D{definition})')

            # Link dependencies
            cmake_deps = []
            if lib_type == 'dynamic':
                cmake_deps.append('miracle_core')  # Always include miracle_core in dynamic libraries
            for dep in dependencies:
                if link_type == 'static' or libraries.get(dep, {}).get('type') == 'static':
                    dep_target = f'{dep}{timestamp}' if (build_type == 'hot' and dep in to_build) else dep
                    cmake_deps.append(dep_target)
            if cmake_deps:
                dep_str = ' '.join(cmake_deps)
                cmake_lines.append(f'target_link_libraries({lib_name}{timestamp} {dep_str})')
            cmake_lines.append('')

    if exe == True:
        # Build the EXE, if 'dynamic' link_type then only link 'inih' and 'miracle_core' otherwise link all target libraries too
        # Executable name should be the same as the project name

        # Build required libs
        cmake_lines.append('# INIH')
        cmake_lines.append('add_library(inih STATIC ${INIH_SRC})')
        cmake_lines.append('target_include_directories(inih PUBLIC lib/third_party/inih/include)\n')

        # Build the executable
        cmake_lines.append('# EXECUTABLE')
        cmake_lines.append(f'add_executable(${{PROJECT_NAME}} ${{EXE_SRC}})')
        cmake_lines.append('target_include_directories(${PROJECT_NAME} PUBLIC executable/include)')
        cmake_lines.append(f'target_compile_definitions(${{PROJECT_NAME}} PUBLIC -D{definition})')

        # Link to libraries
        cmake_deps = ['inih', 'miracle_core']
        if link_type != 'dynamic':
            # Link all target libraries
            for target in to_build:
                cmake_deps.append(target)
        dep_str = ' '.join(cmake_deps)
        cmake_lines.append(f'target_link_libraries(${{PROJECT_NAME}} {dep_str})\n')

    # Write CMakeLists.txt
    with open('CMakeLists.txt', 'w') as f:
        f.write('\n'.join(cmake_lines))

    print("CMakeLists.txt Generated")

def run_cmake(build_dir, platform):
    try:
        print(f"Configuring the project with CMake in '{build_dir}'...")
        if platform == 'windows':
            subprocess.check_call(['cmake', '-B', build_dir, '-DCMAKE_TOOLCHAIN_FILE=.cmake/windows.cmake'])
        else:
            subprocess.check_call(['cmake', '-B', build_dir])
        print("CMake configuration completed successfully.\n")

        print(f"Building the project with CMake in '{build_dir}'...")
        subprocess.check_call(['cmake', '--build', build_dir])
        print("CMake build completed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error: CMake failed with exit code {e.returncode}")
        sys.exit(1)
    

def build(args):
    application, libraries = parse_config()

    target = args.target
    platform = args.platform
    build_type = args.build_type

    # Determine build directories
    dir = get_directory(platform, build_type)
    build_dir = os.path.join('build', dir)
    bin_dir = os.path.join('bin', dir)
    os.makedirs(build_dir, exist_ok=True)
    os.makedirs(bin_dir, exist_ok=True)

    # Determine libraries to build
    to_build = []

    if target == 'all':
        # Build all dynamic libraries and the application
        dynamic_libs = [lib for lib in libraries if libraries[lib]['type'] == 'dynamic']
        to_build.extend(dynamic_libs)
        to_build.append('application')
        
        # Build static dependencies
        static_libs = set()
        for lib in dynamic_libs + ['application']:
            static_libs.update(get_static_dependencies(lib, application, libraries))
        to_build.extend(static_libs)
    elif target == 'application':
        # Build application and its static dependencies
        to_build.append('application')
        static_deps = get_static_dependencies('application', application, libraries)
        to_build.extend(static_deps)
    elif target in libraries:
        # Build specified library and its static dependencies
        to_build.append(target)
        static_deps = get_static_dependencies(target, application, libraries)
        to_build.extend(static_deps)
    else:
        print(f"Unknown target: {target}")
        sys.exit(1)

    # Remove duplicates while preserving order
    to_build = list(dict.fromkeys(to_build))

    # Sort build list by dependency
    to_build = topological_sort(to_build, application, libraries)

    # Generate CMakeLists.txt
    generate_cmake(application, build_type, platform, bin_dir, to_build, libraries, exe=False, link_type='dynamic')

    # Run CMake
    run_cmake(build_dir, platform)

def build_exe(args):
    application, libraries = parse_config()

    platform = args.platform
    build_type = args.build_type
    link_type = args.link

    # Determine build directories
    dir = get_directory(platform, build_type)
    build_dir = os.path.join('build', dir)
    bin_dir = os.path.join('bin', dir)
    os.makedirs(build_dir, exist_ok=True)
    os.makedirs(bin_dir, exist_ok=True)

    # Add libraries to build list
    to_build = list(libraries.keys())
    to_build.append('application')

    # Remove duplicates
    to_build = list(dict.fromkeys(to_build))

    # Sort build list by dependency
    to_build = topological_sort(to_build, application, libraries)

    # Generate CMakeLists.txt with exe=True
    generate_cmake(application, build_type, platform, bin_dir, to_build, libraries, exe=True, link_type=link_type)

    # Run CMake
    run_cmake(build_dir, platform)

def clean():
    # Remove build and bin directories
    if os.path.exists('build'):
        if os.name == 'nt':
            os.system('rmdir /s /q build')
        else:
            os.system('rm -rf build')
    if os.path.exists('bin'):
        if os.name == 'nt':
            os.system('rmdir /s /q bin')
        else:
            os.system('rm -rf bin')
    print("Cleaned build and bin directories.")

def main():
    parser = argparse.ArgumentParser(description='Miracle Framework Build Script')
    subparsers = parser.add_subparsers(dest='command')

    # Build command
    build_parser = subparsers.add_parser('build', help='Build libraries or application')
    build_parser.add_argument('--target', default='all', help='Target to build: all, application, [library name]')
    build_parser.add_argument('--platform', choices=['windows', 'linux'], required=True, help='Target platform')
    build_parser.add_argument('--build-type', choices=['debug', 'release', 'hot'], required=True, help='Build type')

    # Build-exe command
    build_exe_parser = subparsers.add_parser('build-exe', help='Build executable')
    build_exe_parser.add_argument('--platform', choices=['windows', 'linux'], required=True, help='Target platform')
    build_exe_parser.add_argument('--link', choices=['dynamic', 'static'], required=True, help='Link type')
    build_exe_parser.add_argument('--build-type', choices=['debug', 'release', 'hot'], required=True, help='Build type')

    # Clean command
    clean_parser = subparsers.add_parser('clean', help='Clean build and bin directories')

    args = parser.parse_args()

    if args.command == 'build':
        build(args)
    elif args.command == 'build-exe':
        build_exe(args)
    elif args.command == 'clean':
        clean()
    else:
        parser.print_help()

if __name__ == '__main__':
    main()