cmake_minimum_required(VERSION 3.22)

project(
    comcept 
    VERSION 0.0.1
    LANGUAGES CXX 
)

add_library(comcept INTERFACE)
target_include_directories(
    comcept 
    INTERFACE 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> 
        $<INSTALL_INTERFACE:include>
)
target_compile_features(comcept INTERFACE cxx_std_20)
install(DIRECTORY "include/${PROJECT_NAME}" DESTINATION "include/${PROJECT_NAME}")

# Packaging
install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
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


add_executable(comcept_tests)
target_link_libraries(comcept_tests PRIVATE comcept)
target_sources(comcept_tests PRIVATE tests/range_of.cpp)
target_compile_options(comcept_tests PRIVATE -fconcepts-diagnostics-depth=5)



