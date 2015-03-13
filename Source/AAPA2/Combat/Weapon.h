// (C) 2015

#pragma once

#include "Grid/Tile.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAllieganceEnum Alliegence;

	virtual void ProcessTurn_PreMove() {}
	virtual void ProcessTurn_PostMove() {}

};
