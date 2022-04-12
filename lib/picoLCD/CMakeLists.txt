
file(GLOB_RECURSE FILES src/*.c)

add_library(picoLCD ${FILES})
target_link_libraries(picoLCD pico_stdlib)
target_include_directories (picoLCD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
