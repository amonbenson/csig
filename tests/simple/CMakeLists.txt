# add test file
add_executable(simple src/counter.c src/main.c)
target_include_directories(simple PRIVATE include ${bdd_SOURCE_DIR})
target_link_libraries(simple PRIVATE csig)

add_test(NAME simple_test COMMAND simple)
