cmake_minimum_required(VERSION 3.22)

project(
    comcept 
    VERSION 0.0.1
    LANGUAGES CXX 
)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(comcept INTERFACE)
add_library(comcept::comcept ALIAS comcept)
target_include_directories(
    comcept 
    INTERFACE 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> 
        $<INSTALL_INTERFACE:include>
)
target_compile_features(comcept INTERFACE cxx_std_20)
install(DIRECTORY "include/${PROJECT_NAME}" DESTINATION "include/${PROJECT_NAME}")

#########################################################################################
### Packaging
#########################################################################################
install(TARGETS  ${PROJECT_NAME}
        EXPORT   ${PROJECT_NAME}Targets
        LIBRARY  DESTINATION lib
        ARCHIVE  DESTINATION lib
        RUNTIME  DESTINATION bin
        INCLUDES DESTINATION include
)
install(EXPORT      ${PROJECT_NAME}Targets
        FILE        ${PROJECT_NAME}Targets.cmake
        NAMESPACE   ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION 
        "lib/cmake/${PROJECT_NAME}"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" DESTINATION "share/${PROJECT_NAME}")

#########################################################################################
### Tests
#########################################################################################
if(PROJECT_IS_TOP_LEVEL)
    include(CTest)
endif()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
