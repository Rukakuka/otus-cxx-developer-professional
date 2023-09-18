cmake_minimum_required(VERSION 3.10)

set(PROJECT_REVISION 1 CACHE INTERNAL "Project revision (CI)")
set(PROJECT_VESRION 0.0.${PROJECT_REVISION})

project(ip_filter
    VERSION 0.0.${PROJECT_REVISION}
    DESCRIPTION "02-homework"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY G_CXX_STANDARD 14)
set_property(GLOBAL PROPERTY G_CXX_STANDARD_REQUIRED ON)

# Include utility functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GNUInstallDirs)
include(compiler)
include(test)

# Transparent versioning
include_directories(cmake/version)
configure_file(cmake/version/version.h.in version.h)
configure_file(cmake/version/VERSION.in VERSION)
add_library(version cmake/version/project.cpp)
target_include_directories(version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Describe build targets
add_executable(ip_filter src/ip_filter.cpp)
target_link_libraries(ip_filter PRIVATE
    version
)

set_compile_options(ip_filter)
set_compile_options(version)

install(TARGETS ip_filter
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# set(CPACK_GENERATOR DEB)

# set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
# set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
# set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# set(CPACK_PACKAGE_CONTACT example@example.com)

# include(CPack)

# Describe unit tests
enable_testing()
add_unit_test(test/test_version.cpp version)

# Packaging
option(MAKE_PACKAGE "Add 'package' and 'package_source' build targets for packages" ON)
if (MAKE_PACKAGE)
	add_subdirectory(cmake/packaging)
endif()