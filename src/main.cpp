#include "LLDBScope.h"

#include <lldb/API/SBCommandInterpreter.h>
#include <lldb/API/SBCommandReturnObject.h>
#include <lldb/API/SBDebugger.h>
#include <lldb/API/SBError.h>
#include <lldb/API/SBFrame.h>
#include <lldb/API/SBProcess.h>
#include <lldb/API/SBTarget.h>
#include <lldb/API/SBThread.h>

#include <iostream>
#include <string>
#include <vector>

using namespace lldb;

// Debugging helper that allows running arbitrary LLDB commands.
void runCmd(lldb::SBDebugger &dbg, std::string cmd) {
  SBCommandReturnObject result;
  std::cout << "# Running command: " << cmd << "\n";
  dbg.GetCommandInterpreter().HandleCommand(cmd.c_str(), result);
  std::cerr << "Output: " << result.GetOutput() << "\n";
  if (result.GetErrorSize() != 0)
    std::cerr << result.GetError() << "\n";
}

int main(int argc, char **argv) {
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i)
    args.push_back(argv[i]);

  if (args.size() < 2) {
    std::cerr << "Usage: " << args.at(0) << " TARGET\n";
    return 1;
  }

  std::string targetName = args.at(1);

  LLDBScope scope;

  // Setup the debugger instance.
  const bool source_init_files = false;
  SBDebugger dbg = SBDebugger::Create(source_init_files);
  // Make LLDB's API not run commands async in the background.
  // This is not very convenient for this simple example.
  dbg.SetAsync(false);

  // Create a target out of our executable.
  SBTarget target = dbg.CreateTarget(targetName.c_str());
  if (!target.IsValid()) {
    std::cerr << "Failed to create target\n";
    return 1;
  }

  // Set a breakpoint by a source file regex.
  const std::string marker = "DEBUGGER_STOP_MARKER";
  // Empty list = search all available sources.
  SBFileSpec allFiles;
  SBBreakpoint breakpoint =
      target.BreakpointCreateBySourceRegex(marker.c_str(), allFiles);
  if (!breakpoint.IsValid()) {
    std::cerr << "Failed to create breakpoint\n";
    return 1;
  }

  // Launch the target executable to get a process.
  // This vector represents a null-terminated argv.
  std::vector<const char *> targetArgs = {targetName.c_str(), nullptr};
  SBLaunchInfo launchInfo = SBLaunchInfo(targetArgs.data());

  SBError launchError;
  lldb::SBProcess process = target.Launch(launchInfo, launchError);
  if (launchError.Fail()) {
    std::cerr << "Failed to launch target process: ";
    std::cerr << launchError.GetCString() << "\n";
    return 1;
  }
  scope.process = process;

  // Check process status with a command. Only useful for debugging.
  runCmd(dbg, "process status");

  // Get the frame we stopped at and inspect a value.
  SBFrame frame = process.GetThreadAtIndex(0).GetFrameAtIndex(0);
  SBValue value = frame.GetValueForVariablePath("foo");
  if (value.GetError().Fail()) {
    std::cerr << "Error retrieving value: " << value.GetError().GetCString()
              << "\n";
    return 1;
  }

  std::cout << "Value of foo.a: " << value.GetChildAtIndex(0).GetValue()
            << "\n";
}
