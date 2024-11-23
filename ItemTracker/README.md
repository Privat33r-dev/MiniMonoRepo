# Item Tracker CLI





























## Part below is a part of the assignment

## Project Summary

This project is a command-line tool designed to track and analyze items from an input file or stream. At its core, the program counts occurrences of items and provides users with functionality to search for specific items, list all tracked items with their frequencies, and even display a histogram. The goal of this project was to create a simple yet powerful utility to manage and visualize item frequency data while adhering to clean and maintainable coding practices.

## Achievements

I’m particularly proud of several aspects of this project:
- **Test Coverage:** The project has robust test coverage. Each core feature is thoroughly tested to ensure reliability and correctness.
- **Code Quality:** The implementation follows the **SOLID principles** and adheres to the **Google C++ Style Guide**, making the code base maintainable, readable, and professional.
- **Maintainability:** I focused on keeping the code modular, with clear separation of responsibilities between classes like `ItemTracker` and `ItemTrackerCli`.

## Areas for Improvement

Although the project works well, there are areas where I could enhance the code:
- **Scalability for Large Datasets:** While the current implementation performs well for typical use cases, it could be adapted to process much larger datasets by integrating with distributed computing tools like Hadoop or Apache Spark. This could involve reworking the item processing logic to handle chunked or parallel data streams efficiently.
- **Memory Usage:** Dataset is stored in RAM for faster processing, which might cause issues in case of large datasets and limited memory availability.
- **Error Handling:** Currently, error reporting (e.g., when reading files) could be more detailed. Adding more descriptive error messages and logging could improve usability.
- **Extensibility:** Features like importing data from custom files and exporting data to a custom file or allowing more customization in histogram display could make the program more versatile.

These enhancements would improve performance, usability, and adaptability, ensuring the tool scales well for larger datasets or new user requirements.

## Challenges and Solutions

The most challenging part was designing a solution that balances extensibility, simplicity, and adherence to best industry practices. It was essential to ensure that the program was modular and maintainable while providing a smooth user experience.

To overcome these challenges, I relied on:
- **Documentation:** I referenced the Google C++ Style Guide frequently.
- **Testing Tools:** The Google Test framework (GTest) was invaluable in ensuring code correctness.
- **Iterative Refinement:** I continuously refactored the code, focusing on separation of concerns and modularity to align with SOLID principles.
- **Toolchain Expertise:** Setting up CI involved diving deeper in tools like GitHub Actions and configuring Visual Studio to ensure compatibility and automation of builds and tests.

## Transferable Skills

This project helped strengthen several key skills that I can apply to future projects:
- **Test-Driven Development (TDD):** Writing tests first and iterating to meet test criteria is a discipline I’ll continue using.
- **Modular Design:** Structuring the code into reusable components makes it easier to expand or adapt to new requirements.
- **Attention to Code Standards:** Following strict guidelines improved the overall quality and readability of the code.

## Maintainability and Readability

I prioritized maintainability and readability by:
- **Adopting a Consistent Style:** Following the Google C++ Style Guide ensured that the code is clean and familiar to other developers.
- **Adding Comments and Documentation:** Key parts of the code, such as functions and complex logic, are well-documented with concise comments.
- **Encapsulation:** Responsibilities are clearly divided between `ItemTracker` for data processing and `ItemTrackerCli` for user interaction, keeping the design clean and intuitive.
- **Test Coverage:** Comprehensive test coverage ensures that the code remains robust and reliable. By writing tests for all critical components, I mitigated the risk of introducing breaking changes during future refactoring. This not only helps maintain functionality over time but also allows for quicker identification of issues, making the codebase easier to modify and extend without fear of unintended side effects.

---

This project reinforced the importance of combining solid coding practices with an emphasis on usability and reliability. It provided an opportunity to refine my skills in designing maintainable, testable, and scalable systems, and I look forward to applying these practices to future projects.
