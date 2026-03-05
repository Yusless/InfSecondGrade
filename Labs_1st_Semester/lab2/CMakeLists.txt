include_directories(include)

add_executable(list_test src/list_test.cpp src/subforwardlist.cpp)
add_executable(matrix_test src/matrix.cpp)
add_executable(subvector_test src/subvector_test.cpp src/subvector.cpp)

target_include_directories(list_test PRIVATE include)
target_include_directories(matrix_test PRIVATE include)
target_include_directories(subvector_test PRIVATE include) 