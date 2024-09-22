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