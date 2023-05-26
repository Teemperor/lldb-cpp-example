add_executable (${BINARY_NAME}
  main.cpp
  LLDBScope.h
)

# Setup linking/compiling against LLDB.
target_link_libraries(${BINARY_NAME} lldb-${LLDB_VERSION_SUFFIX})
target_link_directories(${BINAR_NAME}
  "/usr/lib/llvm${LLDB_VERSION_SUFFIX}/lib/"
)
target_include_directories(${BINARY_NAME}
  "/usr/lib/llvm${LLDB_VERSION_SUFFIX}/include/"
)
