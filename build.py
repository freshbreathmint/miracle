# command structure:
# ./build.py build
#       --target: [all], [application], [library name]
#       --platform: [windows], [linux]
#       --build-type: [debug], [release], [hot]
# ./build.py build-exe
#       --platform: [windows], [linux]
#       --link: [dynamic], [static]
#       --build-type: [debug], [release], [hot]
# ./build.py clean

# Example INI config.ini
# [application]
# name=MyApp
# icon=icon.ico
# dependencies=libengine,libmiracle
# 
# [library.libengine]
# path=miracle/engine/
# type=dynamic
# dependencies=libmiracle
# 
# [library.libmiracle]
# path=miracle/lib/core/
# type=static
# dependencies=

# build:
#   since building specific libraries or the application is a functionality only useful for runtime-loading of shared libraries, 
#   the way each library is built will be dependant on what 'type' it is in the ini file.
#
#   as an example, if the user input build --target application --platform linux --build-type debug
#   the result will be this:
#       we find every dependency used by the application (in this case, libengine, libmiracle)
#       dynamic type libraries are ignored, but we want to build libmiracle because it is a static library.
#       therefore, we need cmake to build libmiracle, then build libapplication and link libmiracle as a dependency
#       we use no toolchain (if the platform was windows, we would use windows.cmake), and we add debug flags to the final compile of the library
#
#   if the user did a library like libengine, it would be the same process except the final output would be named libengine (it is important that the library is not named "liblibengine")
#
#   if the type of the library is dynamic, make sure it gets the flag -DDYNAMIC_LINK during compile
#
#   platform and build-type control what directories are created for the build & bin process. all cmake build files should go in a build/[platform]/[build-type] directory
#   all executables and build libraries and copied resources/files should go to a bin/[platform]/[build-type] directory.
#   if the build-type is [hot], it should go in [debug] folders.
#
#   [hot] build type means the same thing as debug, adding debug flags, except the final library should be named for example "libapplication" + a unix timestamp like "libapplication1726998800"
#   it also gets output to the normal bin/[platform]/debug folder just like a normal debug build

# build-exe:
#   same thing essentially as build --target all, but different logic, because the link type for the executable is specified here.
#   if we do --link dynamic, build all the libraries and the application library as if we did --target all, and also build the executable
#       meaning we should have via the example:
#       * an executable named MyApp with an icon located at icon.ico
#       * libapplication shared library with libmiracle baked in as a static library
#       * libengine shared library with libmiracle baked in as a static library
#   if we do --link static, we build all the libraries and the application libraries as STATIC libraries, and link them to the executable as static libraries.
#   everything gets the flag -DSTATIC_LINK when we build this way.
#   so the difference is, if we build dynamically, we get the executable with shared objects all with -DDYNAMIC_LINK
#   if we build static, we get a single executable named MyApp with the icon.ico icon, compiled with -DSTATIC_LINK

# clean:
#   cleans up the build/ and bin/ folders that were created by the build process.

#!/usr/bin/env python3

import argparse
import configparser
import os
import sys

# CMAKE Global Variables
cmake_min_version = "VERSION 3.30"

def parse_config():
    config = configparser.ConfigParser()
    config.read('config.ini')

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

def generate_cmake():
    cmake_lines = []

    # Project Details
    cmake_lines.append(f'cmake_minimum_required({cmake_min_version})\n')
    cmake_lines.append(f'project()\n')



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

    # Generate CMakeLists.txt
    generate_cmake()

    # Run CMake
    run_cmake()

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