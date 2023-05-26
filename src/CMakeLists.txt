add_executable (${BINARY_NAME}
  main.cpp
  LLDBScope.h
)
target_link_libraries (${BINARY_NAME} lldb)
