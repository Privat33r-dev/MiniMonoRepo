# Item Tracker CLI

## Project Summary

This project is a command-line tool designed to track and analyze items from an input file or stream.

At its core, the program counts occurrences of items and provides users with functionality to search for specific items, list all tracked items with their frequencies, and even display a histogram.

## Build Guide
### Linux 
```bash
# Install dependencies

# Build the program
cmake -B build
cmake --build build
```
Program binaries would be located in [{PROJECT}/build/ItemTracker](../build/ItemTracker).

### Windows
TBD.

### Contribution Guide
To achieve maintainability and readability, the project follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

Contributions are welcome. For instruction, see [Contributing to a Project on GitHub](https://docs.github.com/en/get-started/exploring-projects-on-github/contributing-to-a-project).

## Areas for Improvement

Although the project works well, there are areas where I could enhance the project:
- [ ] **Test Coverage:** currently test coverage is not calculated by any tool.
- [ ] **Scalability for Large Datasets:** While the current implementation performs well for simple use cases, it could be adapted to process much larger datasets by integrating with distributed computing tools like Hadoop or Apache Spark. This could involve reworking the item processing logic to handle chunked or parallel data streams efficiently. It might also be beneficial to optimize core functionality and make use of multithreading to utilize available hardware resources to their full extent.
- [ ] **Memory Usage:** Dataset is stored in RAM for faster processing, which might cause issues in case of large datasets and limited memory availability.
- [ ] **Error Handling:** Currently, error reporting (e.g., when reading files) could be more detailed. Adding more descriptive error messages and logging could improve usability.
- [ ] **Extensibility:** Features like importing data from custom files and exporting data to a custom file or allowing more customization in histogram display could make the program more versatile.
- [ ] **Containerization:** Containerizing this application into a service might help its intergration into systems, thus enhancing its modularity.
- [ ] **Observability:** The code lacks output which can be used for debugging. Applying consistent debug-, warn- and error-level output might enhance it.
- [ ] **CI Pipeline:** Current CI does not perform automatic release, nor does it differentiate between changes in projects, nor does it perform testing as a part of the process. Improving these parts may improve maintainability.

These enhancements would improve performance, usability, and adaptability, ensuring the tool scales well for larger datasets or new user requirements.
