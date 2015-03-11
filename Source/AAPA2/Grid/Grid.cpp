// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPA2.h"
#include "Grid.h"

TWeakObjectPtr<AGrid> AGrid::StaticGrid = nullptr;


// Sets default values
AGrid::AGrid()
{
	StaticGrid = this;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
AGrid::~AGrid()
{
	if (StaticGrid == this)
	{
		StaticGrid = nullptr;
	}
}

AGrid* AGrid::GetStaticGrid()
{
	return StaticGrid.Get();
}



bool AGrid::ContainsTile(ATile* Tile)
{
	return false;
}

ATile* AGrid::GetTileByIndex(int32 iIndex)
{
	return nullptr;
}

ATile* AGrid::GetTileByCoordinates(FVector2D Coordinates)
{
	return nullptr;
}

ATile* AGrid::GetTileInDirection(ATile* Tile, int32 Direction, int32 Distance /*= 1*/)
{
	return nullptr;
}
ATile* AGrid::GetTileFromWorldPosition(FVector Position)
{
	return nullptr;
}

void AGrid::SelectTile(ATile* pxSelected)
{
	if (m_pxSelectedTile != nullptr)
	{
		m_pxSelectedTile->OnDeselected();
	}
	if (pxSelected && ContainsTile(pxSelected))
	{
		m_pxSelectedTile = pxSelected;
		m_pxSelectedTile->OnSelected();
	}
}
ATile* AGrid::GetSelectedTile()
{
	return m_pxSelectedTile;
}

void AGrid::DeselectTile(ATile* pxSelected /*= nullptr*/)
{
	if (pxSelected != nullptr && pxSelected == m_pxSelectedTile)
	{
		m_pxSelectedTile->OnDeselected();
		m_pxSelectedTile = nullptr;
	}
	else if (pxSelected == nullptr && m_pxSelectedTile != nullptr)
	{
		m_pxSelectedTile->OnDeselected();
		m_pxSelectedTile = nullptr;
	}
}
