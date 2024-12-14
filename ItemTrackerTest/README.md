# Item Tracker Tests

This project contains tests for [Item Tracker](../ItemTracker) project.

Tests are located in [item_tracker_test.cc](item_tracker_test.cc) file.

### Precompiled Header Files
Files [pch.h](pch.h) is a [Precompiled Header](https://learn.microsoft.com/en-us/cpp/build/creating-precompiled-header-files?view=msvc-170). In theory, it speeds up compilation by caching `gtest.h` compilation, however compilation performance tests need to be done to confirm or deny it. File `pch.cc` is essential for its functionality.
