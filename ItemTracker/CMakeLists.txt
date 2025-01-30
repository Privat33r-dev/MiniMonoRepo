cmake_minimum_required(VERSION 3.15)
project(ItemTracker LANGUAGES CXX)

option(BUILD_TESTS "Enable building tests" ON)  # or OFF by default

# 1) Create a library with your core logic
add_library(ItemTrackerLib STATIC
        item_tracker.cc
        item_tracker.h
)
target_link_libraries(ItemTrackerLib
        PUBLIC
        MiniUtils
)
target_include_directories(ItemTrackerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 2) Create the actual executable from main.cc
add_executable(ItemTrackerExe main.cc)
target_link_libraries(ItemTrackerExe PRIVATE ItemTrackerLib)

# 3) Conditionally build the tests if requested
if(BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            # This URL points to a .zip of a specific commit of GoogleTest.
            # Update this commit/URL regularly to keep in sync with the latest stable GTest.
            URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # (Windows-specific) Prevent overriding parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Actually fetch and add googletest to our build
    FetchContent_MakeAvailable(googletest)

    # Now create our test executable
    add_executable(ItemTrackerTest
            tests/unit/item_tracker_test.cc
    )
    target_link_libraries(ItemTrackerTest
            PRIVATE
            ItemTrackerLib     # link your core logic
            gtest              # link GTest
            gtest_main         # link GTest main if you prefer
    )

    enable_testing()
    add_test(NAME ItemTrackerTest COMMAND ItemTrackerTest)
endif()
