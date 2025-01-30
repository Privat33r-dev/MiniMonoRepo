add_executable(Clock
        clock.cc
        main.cc
)

target_include_directories(Clock
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Clock
        PRIVATE
        MiniUtils
)
