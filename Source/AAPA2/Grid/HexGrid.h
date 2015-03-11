// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Grid/Grid.h"
#include "HexGrid.generated.h"

/**
 * 
 */
UCLASS()
class AAPA2_API AHexGrid : public AGrid
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual bool ContainsTile(ATile* Tile) override;
	virtual ATile* GetTileByIndex(int32 iIndex) override;
	virtual ATile* GetTileByCoordinates(FVector2D Coordinates) override;
	virtual ATile* GetTileInDirection(ATile* Tile, int32 Direction, int32 Distance = 1) override;
	virtual ATile* GetTileFromWorldPosition(FVector Position) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	int32 GridRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	float TileRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	TSubclassOf<class ATile> DefaultTile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Generated)
	TArray<ATile*> Tiles;
	
	int32 CoordinatesToIndex(FVector2D Coordinates);
	FVector2D IndexToCoordinates(int32 Index);
	int32 GetArrayLength();
	int32 GetArrayCenter();

	UFUNCTION(BlueprintCallable, Category = Path)
	void HighlightPathTo(AActor* From, ATile* Target);

	virtual bool PathTo(ATile* Start, ATile* End, TArray<ATile*>& Path) override;

};
