add_executable (LLDBTestTarget
  test-target.cpp
)
target_compile_options(LLDBTestTarget PRIVATE -g)

add_test(NAME mytest
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run.py
                 $<TARGET_FILE:${BINARY_NAME}>
                 $<TARGET_FILE:LLDBTestTarget>
)