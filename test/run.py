#!/usr/bin/env python3

import sys
import subprocess as sp

lldb = sys.argv[1]
target = sys.argv[2]

print(f"Starting {lldb} {target}")
output = sp.check_output([lldb, target])

assert "Value of foo.a: 4" in output.decode("utf-8")
