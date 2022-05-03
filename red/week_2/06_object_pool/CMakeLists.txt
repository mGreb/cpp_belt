get_filename_component(NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${NAME})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)
add_executable(${NAME} ${NAME}.cpp)
