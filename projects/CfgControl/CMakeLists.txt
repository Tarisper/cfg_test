# ---[ Project.
project (CfgControl
  VERSION 0.2.0.0
  DESCRIPTION "Config parser"
  LANGUAGES CXX
)

# ---[ Modules.
include (FetchContent)
include (GNUInstallDirs)

# ---[ Current CMake modules.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ---[ Target.
add_library (${PROJECT_NAME})
add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# ---[ Compile definitions.
string (TIMESTAMP BUILD_TIMESTAMP)
target_compile_definitions (${PROJECT_NAME}
  PRIVATE
    PROJECT_NAME="${PROJECT_NAME}"
    PROJECT_DESCRIPTION="${PROJECT_DESCRIPTION}"
    PROJECT_VERSION="${PROJECT_VERSION}"
#    BUILD_TIMESTAMP="${BUILD_TIMESTAMP}"
    WITH_DATE_TZ=0
    WITH_FMT=0
    WITH_UUID=0
)

if (BUILD_SHARED_LIBS)
  target_compile_definitions (${PROJECT_NAME}
    PUBLIC
      $<BUILD_INTERFACE:SROUTER_DSO>
      $<INSTALL_INTERFACE:SROUTER_DSO>
    PRIVATE
      SROUTER_DSO_EXPORT
  )
endif ()

# ---[ Dependencies.

# ---[ Include directories.
target_include_directories (${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# ---[ Link libraries.
target_link_libraries (${PROJECT_NAME}
  PRIVATE
    CONAN_PKG::nlohmann_json
    CONAN_PKG::inih
    $<$<PLATFORM_ID:Linux>:stdc++fs>
)

# ---[ Compile features.
target_compile_features (${PROJECT_NAME}
  INTERFACE
    cxx_std_17
)

# ---[ Compile options.
target_compile_options (${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      -Wall
      -Wextra
      -Wpedantic
      -pedantic-errors
    >
    $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:
      -ftree-vectorize
      -march=native
      -mfpmath=sse
      -funroll-loops
    >
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:
      -fopt-info-loop-optimized
      -ftree-loop-distribution
      -ftree-vectorizer-verbose=3
    >
    $<$<CXX_COMPILER_ID:MSVC>:
      /Wall
      /EHsc
      /MP
      /Qpar
      /Qpar-report:2
      /Qvec-report:2
    >
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:
      /MDd
    >
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:
      /Zi
      /MD
    >
)

# ---[ Link options.
target_link_options (${PROJECT_NAME}
  PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:
     /INCREMENTAL:NO
     /DEBUG
     /OPT:REF
     /OPT:ICF
     /MAP:${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
     /MAPINFO:EXPORTS
   >
)

# ---[ Sources.
set (API_FILES
  "./include/cfgcontrol/cfgcontrol.hpp"
  "./include/cfgcontrol/types.hpp"
  "./include/cfgcontrol/visibility.hpp"
)

set (SOURCE_FILES
  ${API_FILES}
  "./src/cfgcontrol.cpp"
  "./src/backends/json_parser.cpp"
  "./src/backends/json_parser.hpp"
  "./src/backends/ini_parser.cpp"
  "./src/backends/ini_parser.hpp"
  "./src/backends/backends.cpp"
  "./src/backends/backends.hpp"
  "./src/backends/parser_manager.cpp"
  "./src/backends/parser_manager.hpp"
  "./src/backends/get_meta_info/get_meta_info.cpp"
  "./src/backends/get_meta_info/get_meta_info.hpp"
  "./src/utilities/utilities.hpp"
  "./src/utilities/INIReader/INIReader.cpp"
  "./src/utilities/INIReader/INIReader.h"
)

source_group (TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  FILES
    ${SOURCE_FILES}
)

target_sources (${PROJECT_NAME}
  PRIVATE
    ${SOURCE_FILES}
)

# ---[ Target properties.
set_target_properties (${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
    PUBLIC_HEADER "${API_FILES}"
    CXX_VISIBILITY_PRESET "hidden"
    LINK_WHAT_YOU_USE ON
    POSITION_INDEPENDENT_CODE ON
    ENABLE_EXPORTS ${BUILD_SHARED_LIBS}
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    VISIBILITY_INLINES_HIDDEN ON
    DEBUG_POSTFIX "d"
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    COMPILE_PDB_NAME ${PROJECT_NAME}
    COMPILE_PDB_OUTPUT_DIR "${CMAKE_BINARY_DIR}"
    USE_FOLDERS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
)

# ---[ Install rules.
include (InstallRequiredSystemLibraries)
install (TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}-targets"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

include (CMakePackageConfigHelpers)
configure_package_config_file ("cmake/${PROJECT_NAME}-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file ("${PROJECT_NAME}-config-version.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

export (TARGETS ${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE "${PROJECT_NAME}-targets.cmake"
)
export (PACKAGE ${PROJECT_NAME})

install (FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
install (EXPORT "${PROJECT_NAME}-targets"
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
