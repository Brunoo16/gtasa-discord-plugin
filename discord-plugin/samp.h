#pragma once
#include "dllmain.h"

#pragma pack(push, 1)
struct stSAMPPools
{
	struct stActorPool*			pActor;
	struct stObjectPool*		pObject;
	struct stGangzonePool*		pGangzone;
	struct stTextLabelPool*		pText3D;
	struct stTextdrawPool*		pTextdraw;
	void*						pPlayerLabels;
	struct stPlayerPool*		pPlayer;
	struct stVehiclePool*		pVehicle;
	struct stPickupPool*		pPickup;
};

struct stSAMP
{
	void*						pUnk0;
	struct stServerInfo*		pServerInfo;
	uint8_t						byteSpace[24];
	char						szIP[257];
	char						szHostname[259];
	bool						bNametagStatus;
	uint32_t					ulPort;
	uint32_t					ulMapIcons[100];
	int							iLanMode;
	int							iGameState;
	uint32_t					ulConnectTick;
	struct						stServerPresets* pSettings;
	void*						pRakClientInterface;
	struct stSAMPPools*			pPools;
};

struct stServerInfo
{
	uint32_t					uiIP;
	uint16_t					usPort;
};

struct stPlayerPool
{
	uint32_t					ulMaxPlayerID;
	uint16_t					sLocalPlayerID;
	void*						pVTBL_txtHandler;
	std::string					strLocalPlayerName;
	struct stLocalPlayer*		pLocalPlayer;
	int							iLocalPlayerPing;
	int							iLocalPlayerScore;
	struct stRemotePlayer*		pRemotePlayer[1004];
	int							iIsListed[1004];
	DWORD						dwPlayerIP[1004]; // always 0
};

struct stRemotePlayerData
{
	struct stSAMPPed*			pSAMP_Actor;
	struct stSAMPVehicle*		pSAMP_Vehicle;
	uint8_t						byteTeamID;
	uint8_t						bytePlayerState;
	uint8_t						byteSeatID;
	uint32_t					ulUnk3;
	int							iPassengerDriveBy;
	void*						pUnk0;
	uint8_t						byteUnk1[60];
	float						fSomething[3];
	float						fVehicleRoll[4];
	uint32_t					ulUnk2[3];
	float						fOnFootPos[3];
	float						fOnFootMoveSpeed[3];
	float						fVehiclePosition[3];
	float						fVehicleMoveSpeed[3];
	uint16_t					sPlayerID;
	uint16_t					sVehicleID;
	uint32_t					ulUnk5;
	int							iShowNameTag;
	int							iHasJetPack;
	uint8_t						byteSpecialAction;
	uint32_t					ulUnk4[3];
};

struct stRemotePlayer
{
	stRemotePlayerData*			pPlayerData;
	int							iIsNPC;
	void*						pVTBL_txtHandler;
	std::string					strPlayerName;
	int							iScore;
	int							iPing;
};

struct stScoreboardInfo
{
	int					iIsEnabled;
	int					iPlayersCount;
};
#pragma pack(pop)

// Functions
bool SampInit();

// global pointer externals
extern struct stSAMP* SAMP;
extern struct stScoreboardInfo* Scoreboard;