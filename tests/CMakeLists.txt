# add test file
add_executable(csig_test csig_test.c)
target_link_libraries(csig_test PRIVATE csig)

add_test(NAME csig_test COMMAND csig_test)
