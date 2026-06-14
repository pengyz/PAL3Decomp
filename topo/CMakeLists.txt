# topo.dll — 数学库
# 依赖: 无（纯数学运算，仅依赖 libc）
# 被依赖: gbengine.dll → topo.lib

message(STATUS "  topo: ${TOPO_SOURCES}")
link_directories("${CMAKE_SOURCE_DIR}/lib")

file(GLOB TOPO_SOURCES "src/*.cpp" "src/*.c")

if(TOPO_SOURCES)
    add_library(topo SHARED ${TOPO_SOURCES})
    target_include_directories(topo PUBLIC ${CMAKE_SOURCE_DIR}/include)
    set_target_properties(topo PROPERTIES OUTPUT_NAME "topo" PREFIX "" SUFFIX ".dll")
    target_compile_options(topo PRIVATE ${TOPO_GBENGINE_COMPILE_FLAGS} /Zp4)
    target_link_libraries(topo LIBCMT.LIB kernel32.lib)
    if(MSVC_VERSION EQUAL 1200)
        set_target_properties(topo PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/topo/topo.def\" /MAP:\"${CMAKE_BINARY_DIR}/topo.map\"")
    else()
        set_target_properties(topo PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/topo/topo.def\" /SAFESEH:NO /MAP:\"${CMAKE_BINARY_DIR}/topo.map\"")
        target_link_libraries(topo vcruntime.lib ucrt.lib)
        target_link_options(topo PRIVATE /FORCE:MULTIPLE)
    endif()
endif()
