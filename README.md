# DLLHiding
A simple program designed to hide x32/x64 modules using PEB

## Summary
A simple command-line application to Hide DLLs in any Windows Process. Works on both x32 and x64 Processes.

This program should work on all Windows versions from XP to 11. However,  it has only been tested on versions 7 and 10.

Every process maintains an internal set of loaded Modules/DLLs in the form of three linked lists within the PE Block.
- Load Order List
- Memory Order List
- Initialization Order List

## How to use
Open `CMD` and run
```- DLLHiding.exe <Process Name> <DLL Name>```

Ex: ```DLLHiding.exe brave.exe test.dll```

## Limitations
Should effectively hide modules from all user-mode applications. Applications with ring0/Kernel mode access can enumerate the hidden modules; such applications include Process Explorer as the Kernel Object remains unchanged. Additionally, user-mode applications can enumerate an application's memory using NtQueryVirtualMemory() and find the modules.
