// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPA2.h"
#include "AAPA2GameMode.h"

#include "AI/AI.h"
#include "Combat/Damagable.h"
#include "Combat/Weapon.h"
#include "TileMover.h"

void AAAPA2GameMode::RegisterWeapon(UWeapon* Weapon)
{
	AllWeapons[static_cast<uint8>(Weapon->Alliegence)].Add(Weapon);
}
void AAAPA2GameMode::UnregisterWeapon(UWeapon* Weapon)
{
	AllWeapons[static_cast<uint8>(Weapon->Alliegence)].Remove(Weapon);
}
void AAAPA2GameMode::RegisterMover(UTileMover* Mover)
{
	AllMovers[static_cast<uint8>(Mover->Alliegence)].Add(Mover);
}
void AAAPA2GameMode::UnregisterMover(UTileMover* Mover)
{
	AllMovers[static_cast<uint8>(Mover->Alliegence)].Remove(Mover);
}
void AAAPA2GameMode::RegisterTarget(UDamagable* Target)
{
	AllTargets[static_cast<uint8>(Target->Alliegence)].Add(Target);
}
void AAAPA2GameMode::UnregisterTarget(UDamagable* Target)
{
	AllTargets[static_cast<uint8>(Target->Alliegence)].Remove(Target);
}
void AAAPA2GameMode::RegisterAI(UAI* AI)
{
	AllAI[static_cast<uint8>(AI->Alliegence)].Add(AI);
}
void AAAPA2GameMode::UnregisterAI(UAI* AI)
{
	AllAI[static_cast<uint8>(AI->Alliegence)].Remove(AI);
}

void AAAPA2GameMode::ProcessTurn()
{
	for (uint8 i = 0; i < static_cast<uint8>(EAllieganceEnum::Count); i++)
	{
		for (UAI* AI : AllAI[i])
		{
			AI->ProcessTurn();
		}
		for (UDamagable* Target : AllTargets[i])
		{
			Target->ProcessTurn();
		}
		for (UWeapon* Weapon : AllWeapons[i])
		{
			Weapon->ProcessTurn_PreMove();
		}
		for (UTileMover* Mover : AllMovers[i])
		{
			Mover->ProcessTurn();
		}
		for (UWeapon* Weapon : AllWeapons[i])
		{
			Weapon->ProcessTurn_PostMove();
		}
	}	
}