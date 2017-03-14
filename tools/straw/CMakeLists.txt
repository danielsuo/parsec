cmake_minimum_required (VERSION 3.5)
project (straw)

set (CMAKE_C_STANDARD 99)
file (GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/**)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(
  ${PROJECT_NAME}
  pthread
)
