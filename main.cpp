
#include "main.h"

inline const char* const BoolToString(const bool b) {
	return b ? "TRUE" : "FALSE";
}

// convert string to wstring
std::wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	std::wstring r(len, L'\0');
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
	return r;
}

int main(int argc, char* argv[]) {

	tstring title = (xors("DLLHider 0.1"));
	SetConsoleTitle(title.c_str());

	if (argc > 3 || argc <= 2) {
		std::cout << (xors("\n"));
		std::cout << (xors("Invalid arguments!\n")) << std::endl;
		std::cout << (xors("DLLHiding.exe <Process Name> <DLL Name>\n")) << std::endl;
		std::cout << (xors("Ex: ")) << (xors("DllHiding.exe brave.exe test.dll\n")) << std::endl;
		return 0;
	}

	std::string strNameProcess = argv[1];
	std::string strDLLName = argv[2];
	std::wstring wstrDLLName = s2ws(strDLLName);

	Process* A = new Process(strNameProcess, wstrDLLName);

	std::cout << (xors("Process Name: ")) << strNameProcess << " " << (xors("DLL Name: ")) << strDLLName << std::endl;
	std::cout << "\n" << (xors("Status:")) << std::endl;
	std::cout << "\t" << (xors("InLoadOrderModuleList: ")) << BoolToString(A->DLLInLoadStatus) << std::endl;
	std::cout << "\t" << (xors("InMemoryOrderModuleList: ")) << BoolToString(A->DLLInMemStatus) << std::endl;
	std::cout << "\t" << (xors("InInitializationOrderModuleList: ")) << BoolToString(A->DLLInInInitializationStatus) << std::endl;

	// print InLoadOrderModuleList in forward order
	// A->ListModules(A->Pinfo.Process_ID, 0, 0);

	delete A;

	return 0;
}