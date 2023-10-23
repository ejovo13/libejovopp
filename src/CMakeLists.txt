# set(EJOVOPP_SRC lib.cpp ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/rng.cpp)
# message("EJOVOPP_SRC: ${EJOVOPP_SRC}")

# add_library(ejovopp STATIC ${EJOVOPP_SRC})
add_library(ejovopp STATIC lib.cpp)
target_link_libraries(ejovopp PUBLIC matrix++)

# target_link_libraries(ejovopp INTERFACE matrix++)

target_include_directories(
    ejovopp PUBLIC
    "$<BUILD_INTERFACE:${PROJ_INC}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)


install(TARGETS matrix++
        EXPORT matrix++Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS ejovopp
        EXPORT ejovoppTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
set_property(TARGET ejovopp PROPERTY CXX_STANDARD 20)

install(DIRECTORY ${PROJ_INC}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(TARGETS ejovopp matrix++
      FILE ejovoppTargets.cmake
      NAMESPACE ejovopp::
)

    # install(EXPORT ejovoppTargets matrix++Targets
    #         FILE ejovoppTargets.cmake
    #         NAMESPACE ejovopp::
    #         DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ejovopp
    # )