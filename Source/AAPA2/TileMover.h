// (C) 2015

#pragma once

#include "Grid/Tile.h"
#include "Components/ActorComponent.h"
#include "TileMover.generated.h"

class AGrid;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UTileMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTileMover();

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<ATile> CurrentTile;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Facing;

	UFUNCTION(BlueprintCallable, Category = Move)
	bool Move(int32 Direction);

	UFUNCTION(BlueprintCallable, Category = Move)
	bool MoveTowardsTile(ATile* Tile);

	UFUNCTION(BlueprintCallable, Category = Move)
	bool TeleportToTile( ATile* Tile );

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAllieganceEnum Alliegence;

	virtual void ProcessTurn();

protected:
	void SnapToTile(ATile* Tile);
	void SetOccupiedTile(ATile* Tile);

	float MoveProgress;
	TWeakObjectPtr<ATile> TargetTile;
};
