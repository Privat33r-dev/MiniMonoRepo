add_executable(InvestmentPlanner
        investment_planner_cli.cc
        main.cc
)

target_include_directories(InvestmentPlanner
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(InvestmentPlanner
        PRIVATE
        MiniUtils
)
