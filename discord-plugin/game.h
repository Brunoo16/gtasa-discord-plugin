#ifndef DP_GAME_H_
#define DP_GAME_H_

#include "dllmain.h"

namespace Game
{
	extern HMODULE handler;
	extern time_t start_timestamp;

	namespace Functions
	{
		void Initialize(HMODULE handle);
		void Shutdown();

		std::string GetWeaponName(int id);

		void PluginThread();
	}
}

#endif
