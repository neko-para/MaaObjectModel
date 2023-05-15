cmake_minimum_required(VERSION 3.21)

project(maa-object-model CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif ()

if (MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/MP")
    add_compile_options("/W4;/WX")
    # add_compile_options("/wd4127")  # conditional expression is constant
    # add_compile_options("/Wv:19.35.32217")  # disable warning introduced after this version 

    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else ()
    add_compile_options("-Wall;-Werror;-Wextra;-Wpedantic;-Wno-missing-field-initializers")
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
        add_compile_options("-Wno-restrict")
    endif()
endif ()


add_library(MaaObjectModel SHARED
    src/class.cpp
    src/id.cpp
    src/memory.cpp
    src/string.cpp
    src/object.cpp
    include/MaaObjectModel.h
    include/MaaObjectModel/class.h
    include/MaaObjectModel/id.h
    include/MaaObjectModel/object.h
    include/MaaObjectModel/port.h
    include/MaaObjectModel/string.h
    include/MaaObjectModel/type.h
) 

if (WIN32)
    #注意：相比VS版本缺少了 -D_CONSOLE -D_WINDLL 两项
    target_compile_definitions(MaaObjectModel PRIVATE MAA_DLL_EXPORTS _UNICODE UNICODE)
endif ()

target_include_directories(MaaObjectModel PUBLIC include PRIVATE src)

set_target_properties(MaaObjectModel PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

add_executable(test test/main.cpp test/tc.cpp test/tc.h)

target_link_libraries(test MaaObjectModel)

set_target_properties(test PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
