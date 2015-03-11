
#pragma once

#include "Alliegance.generated.h"

UENUM(BlueprintType)
enum class EAllieganceEnum : uint8
{
	AE_Player 	UMETA(DisplayName = "Player"),
	AE_Ally 	UMETA(DisplayName = "Ally"),
	AE_Neutral	UMETA(DisplayName = "Neutral"),
	AE_Enemy	UMETA(DisplayName = "Enemy"),
	AE_None		UMETA(DisplayName = "None"),

	Count
};

class Alliegance
{
public:
	static bool IsAllied(EAllieganceEnum A, EAllieganceEnum B)
	{
		const bool Allies[5][5] = {
			/*				  AE_Player, AE_Ally, AE_Neutral, AE_Enemy, AE_None */
			/*AE_Player*/	{ true,		 true,	  false,	  false,	false },
			/*AE_Ally*/		{ true,		 true,	  false,	  false,	false },
			/*AE_Neutral*/	{ false,	 false,	  false,	  false,	false },
			/*AE_Enemy*/	{ false,	 false,	  false,	  true,		false },
			/*AE_None*/		{ false,	 false,	  false,	  false,	false }
		};
		return Allies[static_cast<uint8>(A)][static_cast<uint8>(B)];
	}
	static bool IsHostile(EAllieganceEnum A, EAllieganceEnum B)
	{
		const bool Enemies[5][5] = {
			/*				  AE_Player, AE_Ally, AE_Neutral, AE_Enemy, AE_None */
			/*AE_Player*/	{ false, false, false, true, false },
			/*AE_Ally*/		{ false, false, false, true, false },
			/*AE_Neutral*/	{ false, false, false, false, false },
			/*AE_Enemy*/	{ true, true, false, false, false },
			/*AE_None*/		{ false, false, false, false, false }
		};
		return Enemies[static_cast<uint8>(A)][static_cast<uint8>(B)];
	}
};
