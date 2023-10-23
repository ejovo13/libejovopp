# add_executable(t_AbsView t_AbsView.cpp)
# add_executable(t_Matrix t_Matrix.cpp)
# add_executable(t_DiffEq t_DiffEq.cpp)
# add_executable(t_Plot t_Plot.cpp)
# add_executable(t_Quad t_Quad.cpp)
# add_executable(t_Grid t_Grid.cpp)
# add_executable(t_Ejovo t_Ejovo.cpp)
# add_executable(t_Vector t_Vector.cpp)
# add_executable(t_mcmc t_MCMC.cpp)
# add_executable(t_MonteCarlo t_MonteCarlo.cpp)
# add_executable(t_Linear t_Linear.cpp)
# add_executable(t_Kd t_Kd.cpp)

macro (add_exe file_name)

    add_executable(${file_name} ${file_name}.cpp)
    target_link_libraries(${file_name} PUBLIC ejovopp)

endmacro()

add_exe(t_hello)
add_exe(benchmarks)
add_exe(benchmarks_omp)


macro(add_test file_name)

    add_executable(
        ${file_name}
        ${file_name}.cpp
    )

    target_link_libraries(
        ${file_name}
        PUBLIC matrix++
        GTest::gtest_main
    )

    gtest_discover_tests(${file_name})

endmacro()

add_test(hello_test)
add_test(core_test)

include(GoogleTest)
# target_link_libraries(t_Matrix INTERFACE matplot)
# target_link_libraries(t_Matrix INTERFACE pyth3)
# target_include_directories()
# target_link_libraries(t_Matrix matplot)