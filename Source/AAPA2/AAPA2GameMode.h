// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Grid/Tile.h"
#include "GameFramework/GameMode.h"
#include "AAPA2GameMode.generated.h"

class UAI;
class UDamagable;
class UTileMover;
class UWeapon;

UCLASS()
class AAPA2_API AAAPA2GameMode : public AGameMode
{
	GENERATED_BODY()
	

public:
	virtual void StartPlay();
	virtual void Tick(float DeltaSeconds) override;

	virtual void RegisterWeapon( UWeapon* Weapon );
	virtual void UnregisterWeapon( UWeapon* Weapon );
	virtual void RegisterMover( UTileMover* Mover );
	virtual void UnregisterMover( UTileMover* Mover );
	virtual void RegisterTarget(UDamagable* Target);
	virtual void UnregisterTarget(UDamagable* Target);
	virtual void RegisterAI(UAI* AI);
	virtual void UnregisterAI(UAI* AI);

	UFUNCTION(BlueprintCallable, Category = Turn)
	virtual void ProcessTurn();

	virtual TSet< UDamagable* >& GetTargets(EAllieganceEnum Alliegance);

protected:
	TSet< UAI* > AllAI[EAllieganceEnum::Count];
	TSet< UWeapon* > AllWeapons[EAllieganceEnum::Count];
	TSet< UTileMover* > AllMovers[EAllieganceEnum::Count];
	TSet< UDamagable* > AllTargets[EAllieganceEnum::Count];
	float TurnTimer;
	int32 TurnCounter;
};
