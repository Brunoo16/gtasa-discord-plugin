#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		Game::Functions::Initialize(module);
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		if (Game::handler == module)
		{
			Game::Functions::Shutdown();
		}
	}
	return TRUE;
}