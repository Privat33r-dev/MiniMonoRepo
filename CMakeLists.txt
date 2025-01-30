cmake_minimum_required(VERSION 3.15)
project(MonoRepo LANGUAGES CXX)

# Bring in each subdirectory
add_subdirectory(MiniUtils)
add_subdirectory(InvestmentPlanner)
add_subdirectory(Clock)
add_subdirectory(ItemTracker)
