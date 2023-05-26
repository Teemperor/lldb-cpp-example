# LLDB C++ example

![example workflow](https://github.com/Teemperor/lldb-cpp-example/actions/workflows/tests.yml/badge.svg)

The code in this repo demonstrates how to use LLDB's SB API from C++.
Note that you probably want to use the Python version of the SB API instead.

## How to build

```bash
cmake path/to/src
cmake --build .
ctest . --output-on-failure # To run the example
```

Note that you might have to set your lldb-server path to the path
of where the lldb-server binary is located on your system. You can do this
via the `LLDB_DEBUGSERVER_PATH` environment variable (example: `LLDB_DEBUGSERVER_PATH=/usr/lib/llvm-14/bin/lldb-server`).