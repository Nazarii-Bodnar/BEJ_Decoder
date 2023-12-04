if(BUILD_TESTING)
    add_executable(mytests mytests.cpp)
    target_link_libraries(mytests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(mytests)
endif()