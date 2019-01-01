#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		Game::module = module;
		Game::Functions::Initialize();
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		Game::Functions::Shutdown();
	}
	return TRUE;
}