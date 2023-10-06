# Neofft

Yet another FFT implementation

## Build

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Test

```bash
cd build
ctest
BOOST_TEST_LOG_LEVEL=message ctest -V # more details
```
