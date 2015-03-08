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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ControlTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<ATile> CurrentTile;

	UFUNCTION(BlueprintCallable, Category = Move)
	void Move(int32 Direction, float OverTime);

	UFUNCTION(BlueprintCallable, Category = Move)
	void MoveToTile(ATile* Tile, float OverTime);

	UFUNCTION(BlueprintCallable, Category = Move)
	void MoveTowardsTile(ATile* Tile, float OverTime);

	UFUNCTION(BlueprintCallable, Category = Move)
	void PathToTile(ATile* Tile, float Speed);

	UFUNCTION(BlueprintCallable, Category = Move)
	void TeleportToTile( ATile* Tile );

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAllieganceEnum Alliegence;

protected:
	void SnapToTile(ATile* Tile);
	void SetOccupiedTile(ATile* Tile);
	float MoveTime;
	float MoveProgress;
	TArray<ATile*> Path;
	TWeakObjectPtr<ATile> OccupiedTile;
};
