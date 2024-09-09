cmake_minimum_required(VERSION 3.30)

# Set project name.
project(executable)

# Set output directory based on build type.
if (DEFINED PLATFORM)
    message("Building for platform '${PLATFORM}'.")
    
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM}/debug)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM}/debug)
    else()
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM}/release)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PLATFORM}/release)
    endif()
endif()

# Collect all file sources for each target.
file(GLOB_RECURSE MIRACLE_LIB_SRC "lib/src/*.c")
file(GLOB_RECURSE APPLICATION_SRC "../src/*.c")
file(GLOB_RECURSE ENGINE_SRC "engine/src/*.c")
file(GLOB_RECURSE EXECUTABLE_SRC "executable/src/*.c")

# Make the framework library
add_library(miracle STATIC ${MIRACLE_LIB_SRC})
target_include_directories(miracle PUBLIC lib/include)

# Make the rest of the libraries either statically linked or dynamically.
if (LINK STREQUAL "STATIC")

    message("Building static...")
    add_definitions(-DSTATIC_LINK)

    # Application Library
    add_library(application STATIC ${APPLICATION_SRC})
    target_include_directories(application PUBLIC ../include)
    target_link_libraries(application miracle engine)

    # Engine Library
    add_library(engine STATIC ${ENGINE_SRC})
    target_include_directories(engine PUBLIC engine/include)
    target_link_libraries(engine miracle)

    # Executable
    add_executable(${PROJECT_NAME} ${EXECUTABLE_SRC})
    target_include_directories(${PROJECT_NAME} PUBLIC executable/include)
    target_link_libraries(${PROJECT_NAME} miracle application engine)

elseif (LINK STREQUAL "DYNAMIC")

    message("Building dynamically...")
    add_definitions(-DDYNAMIC_LINK)

    # Application Library
    add_library(application SHARED ${APPLICATION_SRC})
    target_include_directories(application PUBLIC ../include)
    target_link_libraries(application miracle)

    # Engine Library
    add_library(engine SHARED ${ENGINE_SRC})
    target_include_directories(engine PUBLIC engine/include)
    target_link_libraries(engine miracle)

    # Executable
    add_executable(${PROJECT_NAME} ${EXECUTABLE_SRC})
    target_include_directories(${PROJECT_NAME} PUBLIC executable/include)
    target_link_libraries(${PROJECT_NAME} miracle)

else()
    message(FATAL_ERROR "Invalid LINK_TYPE: ${LINK_TYPE}. Use 'STATIC' or 'DYNAMIC'.")
endif()