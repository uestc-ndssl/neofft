add_executable(rfft1_512 rfft1_512.cpp)
target_link_libraries(rfft1_512 Boost::unit_test_framework hdf5_cpp-shared fftw3)
add_test(NAME rfft1_512 COMMAND rfft1_512 -- ../../data/fft1_512.h5)

add_executable(rfft1_4096 rfft1_4096.cpp)
target_link_libraries(rfft1_4096 Boost::unit_test_framework hdf5_cpp-shared fftw3)
add_test(NAME rfft1_4096 COMMAND rfft1_4096 -- ../../data/fft1_4096.h5)