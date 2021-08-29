
#include "../main.h"

int CheckHardwareBreakpoints() {
	unsigned int NumBps = 0;

	// This structure is key to the function and is the 
	// medium for detection and removal
	CONTEXT ctx;
	ZeroMemory(&ctx, sizeof(CONTEXT));

	// The CONTEXT structure is an in/out parameter therefore we have
	// to set the flags so Get/SetThreadContext knows what to set or get.
	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

	// Get a handle to our thread
	HANDLE hThread = GetCurrentThread();

	// Get the registers
	if (GetThreadContext(hThread, &ctx) == 0)
		return -1;

	// Now we can check for hardware breakpoints, its not 
	// necessary to check Dr6 and Dr7, however feel free to
	if (ctx.Dr0 != 0)
		++NumBps;
	if (ctx.Dr1 != 0)
		++NumBps;
	if (ctx.Dr2 != 0)
		++NumBps;
	if (ctx.Dr3 != 0)
		++NumBps;

	return NumBps;
}

// CheckOutputDebugString checks whether or OutputDebugString causes an error to occur and if the error does occur then we know there's no debugger, otherwise if there IS a debugger no error will occur
inline bool CheckOutputDebugString(LPCTSTR String) {
	OutputDebugString(String);
	if (GetLastError() == 0)
		return true;
	else
		return false;
}

// DebugSelf is a function that uses CreateProcess to create an identical copy of the current process and debugs it
void DebugSelf() {
	HANDLE hProcess = NULL;
	DEBUG_EVENT de;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&de, sizeof(DEBUG_EVENT));

	GetStartupInfo(&si);

	// Create the copy of ourself
	CreateProcess(NULL, GetCommandLine(), NULL, NULL, FALSE,
		DEBUG_PROCESS, NULL, NULL, &si, &pi);

	// Continue execution
	ContinueDebugEvent(pi.dwProcessId, pi.dwThreadId, DBG_CONTINUE);

	// Wait for an event
	WaitForDebugEvent(&de, INFINITE);
}

// This function will erase the current images PE header from memory preventing a successful image if dumped
inline void ErasePEHeaderFromMemory() {
	DWORD OldProtect = 0;

	// Get base address of module
	char* pBaseAddr = (char*)GetModuleHandle(NULL);

	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
		PAGE_READWRITE, &OldProtect);

	// Erase the header
	ZeroMemory(pBaseAddr, 4096);
}