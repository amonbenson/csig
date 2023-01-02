# include bdd for c
FetchContent_Declare(bdd
    GIT_REPOSITORY https://github.com/schlegelflegel/bdd-for-c.git
    GIT_TAG 2647763d531bb73240aed5f7736e230e342eafd5)
FetchContent_MakeAvailable(bdd)


# add all test projects
add_subdirectory(simple)
