# gbengine.dll — 引擎核心 (depends on topo)
# 依赖: topo.lib
# 被依赖: PAL3.exe → gbengine.lib

link_directories("${CMAKE_SOURCE_DIR}/lib")

file(GLOB_RECURSE GBENGINE_SOURCES "src/*.cpp" "src/*.c")

if(GBENGINE_SOURCES)
    add_library(gbengine SHARED ${GBENGINE_SOURCES})
    target_include_directories(gbengine PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        "${CMAKE_SOURCE_DIR}/tools/vc6/Include"
    )
    set_target_properties(gbengine PROPERTIES OUTPUT_NAME "gbengine" PREFIX "" SUFFIX ".dll")
    target_link_libraries(gbengine
        topo
        ${PLATFORM_LIBS}
        LIBCMT.LIB
        d3d9.lib
        d3dx9.lib
        dinput8.lib
        mss32.lib
        ijl15.lib
    )
    target_compile_options(gbengine PRIVATE ${TOPO_GBENGINE_COMPILE_FLAGS})
    if(MSVC_VERSION EQUAL 1200)
        set_target_properties(gbengine PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/gbengine/gbengine.def\" /BASE:0x10000000 /MAP:\"${CMAKE_BINARY_DIR}/gbengine.map\"")
    else()
        set_target_properties(gbengine PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/gbengine/gbengine.def\" /BASE:0x10000000 /SAFESEH:NO /MAP:\"${CMAKE_BINARY_DIR}/gbengine.map\"")
        target_link_libraries(gbengine vcruntime.lib ucrt.lib)
        target_link_options(gbengine PRIVATE /FORCE:MULTIPLE)
    endif()
endif()
