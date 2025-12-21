# _h0micide_etw

<p align="center">  <img src="https://i.pinimg.com/736x/ac/7e/9d/ac7e9d646ad8d8fb472ef0b4e016850c.jpg" alt="goplant" width="200" /></p>

This tool targets the User-mode ETW (Event Tracing for Windows) by overwriting the entrypoint of NtTraceEvent with a RET instruction (0xC3). This effectively blinds the process from system event logging and internal instrumentation.

How It Works
Loads ntdll.dll and locates the NtTraceEvent function
Uses NtProtectVirtualMemory to make the memory writable
Overwrites the first byte with 0xC3 (RET instruction) to force immediate return
Restores the original memory protection

Once patched, any call to NtTraceEvent returns immediately without logging, effectively disabling ETW-based monitoring.
