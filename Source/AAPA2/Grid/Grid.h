// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Grid/Tile.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS(Abstract)
class AAPA2_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	virtual ~AGrid();

	UFUNCTION(BlueprintCallable, Category = Static)
	static AGrid* GetStaticGrid();

	UFUNCTION(BlueprintCallable, Category = Tiles)
	virtual bool ContainsTile(ATile* Tile);

	UFUNCTION(BlueprintCallable, Category = Tiles)
	virtual ATile* GetTileByIndex(int32 iIndex);
	UFUNCTION(BlueprintCallable, Category = Tiles)
	virtual ATile* GetTileByCoordinates(FVector2D Coordinates);
	UFUNCTION(BlueprintCallable, Category = Tiles)
	virtual ATile* GetTileInDirection(ATile* Tile, int32 Direction, int32 Distance = 1);
	UFUNCTION(BlueprintCallable, Category = Tiles)
	virtual ATile* GetTileFromWorldPosition(FVector Position);

	UFUNCTION(BlueprintCallable, Category = Selection)
	void SelectTile(ATile* pxSelected);
	UFUNCTION(BlueprintCallable, Category = Selection)
	ATile* GetSelectedTile();
	UFUNCTION(BlueprintCallable, Category = Selection)
	void DeselectTile(ATile* pxSelected = nullptr);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<ATile> MouseOverTile;

	virtual bool PathTo(ATile* Start, ATile* End, TArray<ATile*>& Path) { return false; }

protected:
	ATile*  m_pxSelectedTile = nullptr;
	static TWeakObjectPtr<AGrid> StaticGrid;
};
