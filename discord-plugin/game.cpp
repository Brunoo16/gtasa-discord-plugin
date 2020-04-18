#include "game.h"

HMODULE module = NULL;

void Initialize()
{
	CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(PluginThread), 0, 0, 0);
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
	Discord_Initialize(APPLICATION_ID, 0, 0, 0);

	std::string details, smallImageText, largeImageText;
	char state[256];

	DiscordRichPresence drp;

	drp = { 0 };
	drp.startTimestamp = time(0);

	if (GetModuleHandle("samp.dll"))
	{
		while (!SampInit())
			Sleep(500);

		while (SAMP->iGameState != 14)
			Sleep(100);

		int partySize;

		std::string serverIP = SAMP->szIP;
		std::string serverName = cp1251_to_utf8(SAMP->szHostname);
		int playersCount = Scoreboard->iPlayersCount;

		if (!SAMP->pPools->pPlayer)
			return;

		int playersMax = SAMP->pPools->pPlayer->ulMaxPlayerID;
		int playerId = SAMP->pPools->pPlayer->sLocalPlayerID;
		std::string playerName = cp1251_to_utf8(SAMP->pPools->pPlayer->strLocalPlayerName.c_str());

		int partyMax = playersMax;
				
		drp.smallImageKey = "samp_icon";

		// SA-MP loop
		while (true)
		{
			partySize = playersCount;
			details = playerName + " [" + std::to_string(playerId) + "]";
			smallImageText = "Location: " + GetCurrentZone();
			
			drp.largeImageKey = WeaponIcons[*reinterpret_cast<int*>(0xBAA410)].c_str();
			drp.largeImageText = "Current weapon";
			drp.smallImageText = smallImageText.c_str();
			drp.details = details.c_str();
			drp.state = serverName.c_str();
			drp.partySize = partySize;
			drp.partyMax = partyMax;

			Discord_UpdatePresence(&drp);

			Sleep(15000);
		}
	}
	else
	{
		drp.smallImageKey = "game_icon";

		// Singleplayer loop
		while (true)
		{
			if (*reinterpret_cast<int*>(0xB6F5F0))
			{
				// details = "Money: $" + std::to_string(*reinterpret_cast<int*>(0xB7CE50));
				sprintf_s(state, "Progress: %.2f%%", (*reinterpret_cast<float*>(0x00A4A61C)));
				largeImageText = std::to_string(*reinterpret_cast<int*>(0xB79038)) + " day(s) passed.";
				smallImageText = "Location: " + GetCurrentZone();

				drp.largeImageKey = WeaponIcons[*reinterpret_cast<int*>(0xBAA410)].c_str();
				drp.largeImageText = "Current weapon";
				drp.smallImageText = smallImageText.c_str();
				drp.details = details.c_str();
				drp.state = state;
				drp.largeImageText = largeImageText.c_str();

				Discord_UpdatePresence(&drp);

				Sleep(15000);
			}
		}
	}
}