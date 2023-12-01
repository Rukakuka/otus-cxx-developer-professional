cmake_minimum_required(VERSION 3.10)

set(PROJECT_REVISION 1 CACHE INTERNAL "Project revision (CI)")
set(PROJECT_VESRION 0.0.${PROJECT_REVISION})

project(vector_editor
    VERSION 0.0.${PROJECT_REVISION}
    DESCRIPTION "05-homework"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY G_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY G_CXX_STANDARD_REQUIRED ON)

# Include utility functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GNUInstallDirs)
include(compiler)

# 3rd-party

# Transparent versioning
include_directories(cmake/version)
configure_file(cmake/version/version.h.in version.h)
configure_file(cmake/version/VERSION.in VERSION)
add_library(version cmake/version/project.cpp)
target_include_directories(version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Describe build targets
include_directories(include/)
add_executable(vector_editor src/main.cpp)
find_package(fmt REQUIRED)
target_link_libraries(vector_editor PRIVATE
    version fmt::fmt
)

set_compile_options(vector_editor)
set_compile_options(version)

install(TARGETS vector_editor
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
