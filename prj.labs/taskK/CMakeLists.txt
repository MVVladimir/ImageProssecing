project(taskK)
add_executable(taskK taskK.cpp taskK.report.md.in.txt)
target_link_libraries(taskK ${OpenCV_LIBS})

# prepare report md file
file(READ taskK.cpp cpp_source)
configure_file(taskK.report.md.in.txt ${CMAKE_CURRENT_BINARY_DIR}/taskK.report.md @ONLY)
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/taskK.report.md" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")