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

# Make the application library with temporary source list
# add_library(application STATIC ../src/library.c)
# target_include_directories(application PUBLIC ../src)

# Make the framework library with temporary source list
add_library(miracle STATIC lib/src/containers/dynamic_array.c)
target_include_directories(miracle PUBLIC lib/include)

# Make the shared application library with temporary source list
add_library(application SHARED ../src/app.c)
target_include_directories(application PUBLIC ../include)
target_link_libraries(application miracle)

# Make the shared engine library with temporary source list
add_library(engine SHARED engine/engine.c)
target_include_directories(engine PUBLIC engine/include)
target_link_libraries(engine miracle)

# Make executable with temporary source list.
add_executable(${PROJECT_NAME} 
    src/library.c
    src/main.c
    src/platform/windows.c 
    src/platform/linux.c
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} miracle)

# Link the application to the executable
# target_link_libraries(${PROJECT_NAME} application)