add_library(MiniUtils STATIC
        mini_utils.cc
)

# Tell consumers (other targets) that they can include MiniUtils headers
# using #include "mini_utils.h" without specifying extra paths.
target_include_directories(MiniUtils
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
