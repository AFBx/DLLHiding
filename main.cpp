
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

	tstring title = (xorstr("DLLHider 0.1"));
	SetConsoleTitle(title.c_str());

	if (argc > 3 || argc <= 2) {
		std::cout << (xorstr("\n"));
		std::cout << (xorstr("Invalid arguments!\n")) << std::endl;
		std::cout << (xorstr("DLLHiding.exe <Process Name> <DLL Name>\n")) << std::endl;
		std::cout << (xorstr("Ex: ")) << (xorstr("DllHiding.exe brave.exe test.dll\n")) << std::endl;
		return 0;
	}

	std::string strNameProcess = argv[1];
	std::string strDLLName = argv[2];
	std::wstring wstrDLLName = s2ws(strDLLName);

	Process* A = new Process(strNameProcess, wstrDLLName);

	std::cout << (xorstr("Process Name: ")) << strNameProcess << " " << (xorstr("DLL Name: ")) << strDLLName << std::endl;
	std::cout << "\n" << (xorstr("Status:")) << std::endl;
	std::cout << "\t" << (xorstr("InLoadOrderModuleList: ")) << BoolToString(A->DLLInLoadStatus) << std::endl;
	std::cout << "\t" << (xorstr("InMemoryOrderModuleList: ")) << BoolToString(A->DLLInMemStatus) << std::endl;
	std::cout << "\t" << (xorstr("InInitializationOrderModuleList: ")) << BoolToString(A->DLLInInInitializationStatus) << std::endl;

	// print InLoadOrderModuleList in forward order
	// A->ListModules(A->Pinfo.Process_ID, 0, 0);

	delete A;

	return 0;
}
