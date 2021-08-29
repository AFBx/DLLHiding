
#include <windows.h>
#include <iostream>

#include "../DLLHiding/process/process.h"
#include "../DLLHiding/misc/encryption/xor.h"

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif
