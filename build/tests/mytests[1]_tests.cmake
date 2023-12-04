add_test([=[separatorTest.CheckOutput]=]  C:/Users/Nazar/Documents/BEJ_decoder/build/tests/mytests.exe [==[--gtest_filter=separatorTest.CheckOutput]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[separatorTest.CheckOutput]=]  PROPERTIES WORKING_DIRECTORY C:/Users/Nazar/Documents/BEJ_decoder/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  mytests_TESTS separatorTest.CheckOutput)
