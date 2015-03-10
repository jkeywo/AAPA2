// (C) 2015

#pragma once

#include "Combat/Weapon.h"
#include "AutoWeapon.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AAPA2_API UAutoWeapon : public UWeapon
{
	GENERATED_BODY()

public:
	virtual void ProcessTurn_PostMove();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<FVector2D> TargetedTiles;

};
