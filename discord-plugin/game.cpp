#include "game.h"

namespace Game
{
	HMODULE handler = NULL;
	time_t start_timestamp = NULL;

	namespace Functions
	{
		void Initialize(HMODULE handle)
		{
			handler = handle;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Game::Functions::PluginThread, 0, 0, 0); // Thread because we don't want to end up in a deadlock when initializing on dllmain.
		}

		void Shutdown()
		{
			Discord_Shutdown();
		}

		std::string GetWeaponName(int id)
		{
			std::string weapon_name;
			switch (id)
			{
				case 311:
				{
					weapon_name = "Brass Knuckles";
					break;
				}
				case 333:
				{
					weapon_name = "Golf Club";
					break;
				}
				case 334:
				{
					weapon_name = "Nightstick";
					break;
				}
				case 335:
				{
					weapon_name = "Knife";
					break;
				}
				case 336:
				{
					weapon_name = "Baseball Bat";
					break;
				}
				case 337:
				{
					weapon_name = "Shovel";
					break;
				}
				case 338:
				{
					weapon_name = "Pool Cue";
					break;
				}
				case 339:
				{
					weapon_name = "Katana";
					break;
				}
				case 341:
				{
					weapon_name = "Chainsaw";
					break;
				}
				case 321:
				{
					weapon_name = "Purple Dildo";
					break;
				}
				case 322:
				{
					weapon_name = "Dildo";
					break;
				}
				case 323:
				{
					weapon_name = "Vibrator";
					break;
				}
				case 324:
				{
					weapon_name = "Silver Vibrator";
					break;
				}
				case 325:
				{
					weapon_name = "Flowers";
					break;
				}
				case 326:
				{
					weapon_name = "Cane";
					break;
				}
				case 342:
				{
					weapon_name = "Grenade";
					break;
				}
				case 343:
				{
					weapon_name = "Tear Gas";
					break;
				}
				case 344:
				{
					weapon_name = "Molotov Cocktail";
					break;
				}
				case 346:
				{
					weapon_name = "9mm";
					break;
				}
				case 347:
				{
					weapon_name = "Silenced 9mm";
					break;
				}
				case 348:
				{
					weapon_name = "Desert Eagle";
					break;
				}
				case 349:
				{
					weapon_name = "Shotgun";
					break;
				}
				case 350:
				{
					weapon_name = "Sawnoff Shotgun";
					break;
				}
				case 351:
				{
					weapon_name = "Combat Shotgun";
					break;
				}
				case 352:
				{
					weapon_name = "Micro SMG";
					break;
				}
				case 353:
				{
					weapon_name = "MP5";
					break;
				}
				case 355:
				{
					weapon_name = "AK-47";
					break;
				}
				case 356:
				{
					weapon_name = "M4";
					break;
				}
				case 372:
				{
					weapon_name = "Tec-9";
					break;
				}
				case 357:
				{
					weapon_name = "Country Rifle";
					break;
				}
				case 358:
				{
					weapon_name = "Sniper Rifle";
					break;
				}
				case 359:
				{
					weapon_name = "Rocket Launcher";
					break;
				}
				case 360:
				{
					weapon_name = "Heat Seeker";
					break;
				}
				case 361:
				{
					weapon_name = "Flamethrower";
					break;
				}
				case 362:
				{
					weapon_name = "Minigun";
					break;
				}
				case 363:
				{
					weapon_name = "Satchel Charge";
					break;
				}
				case 364:
				{
					weapon_name = "Detonator";
					break;
				}
				case 365:
				{
					weapon_name = "Spraycan";
					break;
				}
				case 366:
				{
					weapon_name = "Fire Extinguisher";
					break;
				}
				case 367:
				{
					weapon_name = "Camera";
					break;
				}
				case 368:
				{
					weapon_name = "NV Googles";
					break;
				}
				case 369:
				{
					weapon_name = "Thermal Googles";
					break;
				}
				case 371:
				{
					weapon_name = "Parachute";
					break;
				}
				default:
				{
					weapon_name = "None";
					break;
				}
			}
			return weapon_name;
		}

		void PluginThread()
		{
			Discord_Initialize("424599965164371968", 0, 1, 0);

			start_timestamp = time(0);

			while (1)
			{
				int CPed = *(int*)0xB6F5F0; // Player pointer.

				if (CPed)
				{
					std::string details, state, small_img, large_img;

					DiscordRichPresence drp;

					memset(&drp, 0, sizeof(drp));

					drp.largeImageKey = "game_icon";
					drp.startTimestamp = start_timestamp;

					if (*(unsigned char*)(CPed + 0x46C) == 1) // Player is on vehicle, let's consider other states as "on-foot".
					{
						drp.smallImageKey = "player_on_vehicle";
						small_img = "On vehicle - Wanted level: " + std::to_string(*(int*)0xBAA420);
					}
					else
					{
						small_img = "On foot - Wanted level: " + std::to_string(*(int*)0xBAA420);
						drp.smallImageKey = "player_on_foot";
					}

					details = "Money: $" + std::to_string(*(int*)0xB7CE50);
					state = "Weapon: " + GetWeaponName(*(int*)(CPed + 0x740));
					large_img = std::to_string(*(int*)0xB79038) + " day(s) passed.";

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