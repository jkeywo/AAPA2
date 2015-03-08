// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPA2.h"
#include "Tile.h"

#include "Grid/Grid.h"


// Sets default values
ATile::ATile()
: Highlight(false)
, Blocked(false)
, Occupier(nullptr)
, Alliegence(EAllieganceEnum::AE_None)
, Grid(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetGrid(AGrid* NewGrid, int32 NewIndex)
{
	Grid = NewGrid;
	Index = NewIndex;
}
void ATile::SetCoordinate(FVector2D CoordinatesIn)
{
	Coordinates = CoordinatesIn;
}

void ATile::SetSelected()
{
	Grid->SelectTile(this);
}
void ATile::SetDeselected()
{
	Grid->DeselectTile(this);
}
bool ATile::IsSelected()
{
	return Grid->GetSelectedTile() == this;
}
