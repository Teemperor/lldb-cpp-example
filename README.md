# LLDB C++ example

The code in this repo demonstrates how to use LLDB's SB API from C++.
Note that you probably want to use the Python version of the SB API instead.

## How to build

```bash
cmake path/to/src
cmake --build .
ctest . --output-on-failure # To run the example
```