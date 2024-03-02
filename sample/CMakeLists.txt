add_executable(sample test_runner.c strlen.test.c reverse.test.c)
target_link_libraries(sample PRIVATE picotest)
