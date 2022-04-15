project(yellow_week_6)

set(source_files
        condition_parser.cpp
        condition_parser_test.cpp
        test_runner.cpp
        database.cpp
        db_tests.cpp
        db_container.cpp
        date.cpp
        event.cpp
        node.cpp
        token.cpp
        main.cpp)
add_executable(yellow_final ${source_files})
target_compile_options(yellow_final PRIVATE -Wall -Wextra -Wpedantic) # -Werror)
