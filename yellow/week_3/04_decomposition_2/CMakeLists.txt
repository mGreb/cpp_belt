set(proj_name "04_decomposition_2")
project(${proj_name})
set(source_files main.cpp query.cpp query.h responses.cpp responses.h bus_manager.cpp bus_manager.h)
add_executable(${proj_name} ${source_files})
