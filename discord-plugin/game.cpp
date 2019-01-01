#include "game.h"

namespace Game
{
	HMODULE module = NULL;

	namespace Functions
	{
		void Initialize()
		{
			CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Functions::PluginThread), 0, 0, 0);
		}

		void Shutdown()
		{
			Discord_Shutdown();
		}

		std::string GetCurrentZone()
		{
			const float position_x = *reinterpret_cast<float*>(0xB6F2E4), position_y = *reinterpret_cast<float*>(0xB6F2E8), position_z = *reinterpret_cast<float*>(0x8CCC44);

			for (int i = 0; i < sizeof(zone) / sizeof(zone[0]); i++)
			{
				if (position_x > zone[i].min_x && position_y > zone[i].min_y && position_z > zone[i].min_z && position_x < zone[i].max_x && position_y < zone[i].max_y && position_z < zone[i].max_z)
				{
					return zone[i].zone_name;
				}
			}

			return std::string("San Andreas");
		}

		void PluginThread()
		{
			if (GetModuleHandle("samp.dll")) // This plugin is not supposed to be used with SA-MP.
			{
				FreeLibraryAndExitThread(Game::module, 0);
			}
			else
			{
				Discord_Initialize(APPLICATION_ID, 0, 0, 0);

				std::string details, state, small_img, large_img;

				DiscordRichPresence drp;

				drp = { 0 };
				drp.largeImageKey = "game_icon";
				drp.startTimestamp = time(0);

				while (1)
				{
					if (*reinterpret_cast<int*>(0xB6F5F0))
					{
						if (*reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(0xB6F5F0) + 0x46C) == 1) // Player is on vehicle, let's consider other states as "on-foot".
						{
							drp.smallImageKey = "player_on_vehicle";
						}
						else
						{
							drp.smallImageKey = "player_on_foot";
						}

						details = "Money: $" + std::to_string(*reinterpret_cast<int*>(0xB7CE50));
						state = "Weapon: " + WeaponNames[*reinterpret_cast<int*>(0xBAA410)];
						large_img = std::to_string(*reinterpret_cast<int*>(0xB79038)) + " day(s) passed.";
						small_img = "Location: " + GetCurrentZone();

						drp.smallImageText = small_img.c_str();
						drp.details = details.c_str();
						drp.state = state.c_str();
						drp.largeImageText = large_img.c_str();

						Discord_UpdatePresence(&drp);

						Sleep(15000);
					}
				}
			}
		}
	}
}