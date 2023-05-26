#ifndef LLDBSCOPE_H
#define LLDBSCOPE_H

#include <iostream>
#include <lldb/API/SBDebugger.h>
#include <lldb/API/SBError.h>
#include <lldb/API/SBProcess.h>

#include <optional>

class LLDBScope {
  std::optional<lldb::SBError> initError;

public:
  LLDBScope() {
    lldb::SBError err = lldb::SBDebugger::InitializeWithErrorHandling();
    if (err.Fail())
      initError = err;
  }

  ~LLDBScope() {
    // If there is a process, then kill it now. Without this the LLDB
    // termination might get stuck waiting for the thread handling the process.
    if (process.IsValid()) {
      if (lldb::SBError killError = process.Kill(); killError.Fail()) {
        std::cerr << "Failed to kill target process: ";
        std::cerr << killError.GetCString() << "\n";
      }
    }

    // Tear down the global LLDB data structures.
    if (!initError)
      lldb::SBDebugger::Terminate();
  }

  [[nodiscard]] std::optional<lldb::SBError> maybeGetInitError() const {
    return initError;
  }

  lldb::SBProcess process;
};

#endif // LLDBSCOPE_H
