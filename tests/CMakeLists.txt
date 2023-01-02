# add test file
add_executable(csig_test src/counter.c src/main.c)
target_include_directories(csig_test PRIVATE include)
target_link_libraries(csig_test PRIVATE csig)

add_test(NAME csig_test COMMAND csig_test)
