set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

add_subdirectory(google_benchmark)

add_executable(cli11bench main.cpp)

target_include_directories(cli11bench PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cli11bench benchmark::benchmark)
