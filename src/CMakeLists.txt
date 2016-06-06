aux_source_directory(. SRC_LIST)
add_compile_options("-std=c++11")

include_directories(../include)

file(GLOB_RECURSE LibFiles "../include/*.h")
add_custom_target(headers SOURCES ${LibFiles})

add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${LibFiles})

