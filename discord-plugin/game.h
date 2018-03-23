#ifndef DP_GAME_H_
#define DP_GAME_H_

#include "dllmain.h"

namespace Game
{
	namespace Functions
	{
		void Initialize();
		void Shutdown();

		std::string GetWeaponName(int id);

		void PluginThread();
	}
}

#endif
