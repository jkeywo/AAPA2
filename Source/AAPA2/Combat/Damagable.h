// (C) 2015

#pragma once

#include "Grid/Tile.h"
#include "Components/ActorComponent.h"
#include "Damagable.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UDamagable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamagable();

	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

	virtual void ProcessTurn();

	UFUNCTION(BlueprintCallable, Category = Damage)
	virtual bool ApplyDamage(int32 Amount, FVector Origin);
	UFUNCTION(BlueprintCallable, Category = Damage)
	virtual bool ApplyDamageToSide(int32 Amount, int32 Side);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAllieganceEnum Alliegence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Health")
	bool HasShields;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Health")
	bool HasDirectionalShields;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Health")
	int32 ShieldRechargeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Health")
	bool HasArmour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Health")
	bool HasDirectionalArmour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Health")
	int32 MaxHull;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Health")
	TArray<int32> ShieldStates;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Health")
	TArray<bool> ArmourStates;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Health")
	int32 HullState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	UParticleSystem* DestroyedPFX;

	UFUNCTION(BlueprintCallable, Category = Repair)
	bool CanRepair();
	UFUNCTION(BlueprintCallable, Category = Repair)
	void Repair();

};
