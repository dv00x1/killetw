# killetw

<p align="center">  <img src="https://i.pinimg.com/736x/d4/d7/34/d4d734d6753d0f619d2df017487c3c5f.jpg" alt="goplant" width="200" /></p>

This tool targets the User-mode ETW (Event Tracing for Windows) by overwriting the entrypoint of NtTraceEvent with a RET instruction (0xC3). This effectively blinds the process from system event logging and internal instrumentation.

How It Works
- Loads ntdll.dll and locates the NtTraceEvent function
- Uses NtProtectVirtualMemory to make the memory writable
- Overwrites the first byte with 0xC3 (RET instruction) to force immediate return
- Restores the original memory protection

Once patched, any call to NtTraceEvent returns immediately without logging, effectively disabling ETW-based monitoring.
