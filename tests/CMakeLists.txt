#########################################################################################
### Tests
add_executable(comcept_tests)
target_link_libraries(comcept_tests PRIVATE comcept::comcept)
target_sources(comcept_tests 
    PRIVATE
        main.cpp 
        range_of.cpp 
        decays_to.cpp
        compose.cpp
        map_of.cpp
        set_of.cpp
        variant_of.cpp
        cvref.cpp
        all_of.cpp
        any_of.cpp
        not_a.cpp
)

include(FetchContent)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_Declare(doctest GIT_REPOSITORY https://github.com/onqtam/doctest GIT_TAG v2.4.11)
FetchContent_MakeAvailable(doctest)
target_link_libraries(comcept_tests PRIVATE doctest::doctest)
# target_compile_options(comcept_tests PRIVATE -fconcepts-diagnostics-depth=5)

enable_testing()
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(comcept_tests)