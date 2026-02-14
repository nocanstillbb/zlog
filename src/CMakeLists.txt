aux_source_directory(. SRCS)

if (NOT WIN32)
    list(REMOVE_ITEM SRCS ./zlog_win.c)
endif ()

list(REMOVE_ITEM SRCS ./zlog-chk-conf.c)

add_library(zlog ${SRCS})
add_library(zlog::zlog ALIAS zlog)

target_compile_features(zlog PRIVATE c_std_99)
target_compile_options(zlog PRIVATE -Wall -Wstrict-prototypes)
target_compile_definitions(zlog PRIVATE _DEFAULT_SOURCE)

target_include_directories(zlog
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(zlog PUBLIC Threads::Threads)

if (WIN32)
    target_link_libraries(zlog PRIVATE ${UNIXEM_LIBRARY} Ws2_32)
    target_compile_definitions(zlog PRIVATE WINVER=0x0500 _WIN32_WINNT=0x0500)
endif ()

set_target_properties(zlog PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# --- install ---

install(TARGETS zlog
    EXPORT zlog-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES zlog.h zlog_cpp.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT zlog-targets
    FILE zlog-targets.cmake
    NAMESPACE zlog::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zlog
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/zlogConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/zlogConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zlog
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/zlogConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zlogConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/zlogConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zlog
)

# --- tool ---

if (ZLOG_BUILD_TOOLS)
    add_executable(zlog-chk-conf zlog-chk-conf.c)
    target_link_libraries(zlog-chk-conf PRIVATE zlog)
    install(TARGETS zlog-chk-conf RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif ()
