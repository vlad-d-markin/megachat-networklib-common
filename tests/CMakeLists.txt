find_package(GTest REQUIRED)

aux_source_directory(. TEST_SRC)

include_directories(${GTEST_INCLUDE_DIRS} ../include)

add_executable(test-${PROJECT_NAME} ${TEST_SRC})

#add_library(mega-networklib STATIC IMPORTED)
#set_target_properties(mega-networklib PROPERTIES IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/src/lib${PROJECT_NAME}.a)

# mega-networklib
target_link_libraries(test-${PROJECT_NAME} ${GTEST_LIBRARIES} pthread  ${PROJECT_NAME})
