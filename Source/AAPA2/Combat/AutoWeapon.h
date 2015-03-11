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
	virtual void ProcessTurn_PreMove();
	virtual void ProcessTurn_PostMove();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 ArcStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 ArcStop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 RangeMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 RangeMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool FirePreMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UParticleSystem* Beam;

protected:
	void Fire();

	TArray<UParticleSystemComponent*> Beams;
};
