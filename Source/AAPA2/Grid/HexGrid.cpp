// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPA2.h"
#include "HexGrid.h"

#define SQRT_3 1.732050808f

const uint8 NeighbourBits[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20 };

const FMatrix HexToWorld(
	FVector(3.0f / 2.0f,	SQRT_3 / 2.0f, 0.0f),
	FVector(0.0f,			SQRT_3, 0.0f),
	FVector(0.0f,			0.0f, 1.0f), FVector());

const FMatrix WorldToHex(
	FVector(2.0f / 3.0f, -1.0f / 3.0f, 0.0f),
	FVector(0.0f, SQRT_3 / 3.0f, 0.0f),
	FVector(0.0f,			0.0f,			1.0f), FVector() );

const FVector WorldSpaceNeighbours[] =
{
	FVector( 3.0f / 2.0f, SQRT_3 / 2.0f,0.0f),
	FVector( 0.0f,		  SQRT_3,		0.0f),
	FVector(-3.0f / 2.0f, SQRT_3 / 2.0f,0.0f),
	FVector(-3.0f / 2.0f,-SQRT_3 / 2.0f,0.0f),
	FVector( 0.0f,		 -SQRT_3,		0.0f),
	FVector( 3.0f / 2.0f,-SQRT_3 / 2.0f,0.0f)
};
const FVector WorldSpaceCorners[] =
{
	FVector( 1.0f, 0.0f,  0.0f),
	FVector( 0.5f, 0.0f,  SQRT_3 / 2.0f),
	FVector(-0.5f, 0.0f,  SQRT_3 / 2.0f),
	FVector(-1.0f, 0.0f,  0.0f),
	FVector(-0.5f, 0.0f, -SQRT_3 / 2.0f),
	FVector( 0.5f, 0.0f, -SQRT_3 / 2.0f),
};
const FVector2D HexSpaceNeighbours[] =
{
	FVector2D( 0,  1),
	FVector2D(-1,  1),
	FVector2D(-1,  0),
	FVector2D( 0, -1),
	FVector2D( 1, -1),
	FVector2D( 1,  0)
};

void AHexGrid::OnConstruction(const FTransform& Transform)
{
	for (ATile* pxTile : Tiles)
	{
		if (pxTile)
		{
			pxTile->Destroy();
		}
	}
	Tiles.Empty();

	int ArrayLength = (2 * GridRadius - 1);
	for (int32 i = 0; i < ArrayLength * ArrayLength; i++)
	{
		FVector2D xCoordinates = IndexToCoordinates(i);
		if (FMath::Abs(- xCoordinates.X - xCoordinates.Y) >= GridRadius)
		{
			Tiles.Add(nullptr);
			continue;
		}

		FVector xPosition = 2.0f * TileRadius * HexToWorld.TransformVector(FVector(xCoordinates.X, xCoordinates.Y, 0.0f));
		ATile* pxTile = GetWorld()->SpawnActor<ATile>(DefaultTile, xPosition, FRotator::ZeroRotator);
		if (pxTile)
		{
			pxTile->AttachRootComponentToActor(this);
			pxTile->SetGrid(this, i);
			pxTile->SetCoordinate(xCoordinates);
		}
		Tiles.Add(pxTile);
	}
}

bool AHexGrid::ContainsTile(ATile* Tile)
{
	return Tiles.Contains( Tile );
}

ATile* AHexGrid::GetTileByIndex(int32 iIndex)
{
	return Tiles[iIndex];
}
ATile* AHexGrid::GetTileByCoordinates(FVector2D Coordinates)
{
	int32 Index = CoordinatesToIndex(Coordinates);
	return Tiles.IsValidIndex(Index) ? Tiles[Index] : nullptr;
}
ATile* AHexGrid::GetTileInDirection(ATile* Tile, int32 Direction, int32 Distance /*= 1*/)
{
	if (Tile == nullptr)
	{
		return nullptr;
	}
	int Index = Tile->Index;
	FVector2D Coordinates = IndexToCoordinates(Index) + (HexSpaceNeighbours[Direction] * Distance);
	Index = CoordinatesToIndex(Coordinates);
	return Tiles.IsValidIndex(Index) ? Tiles[Index] : nullptr;
}
ATile* AHexGrid::GetTileFromWorldPosition(FVector Position)
{
	Position /= (TileRadius * 2.0f);
	FVector TilePosition = WorldToHex.TransformVector(Position);

	return GetTileByCoordinates(FVector2D(TilePosition.X, TilePosition.Y));
}

int32 AHexGrid::CoordinatesToIndex(FVector2D Coordinates)
{
	int32 AdjustedX = FMath::RoundToInt(Coordinates.X) + GetArrayCenter();
	int32 AdjustedY = FMath::RoundToInt(Coordinates.Y) + GetArrayCenter();

	if (AdjustedX >= 0 && AdjustedX < GetArrayLength() 
		&& AdjustedY >= 0 && AdjustedY < GetArrayLength())
	{
		return AdjustedX + AdjustedY * GetArrayLength();
	}
	return -1;	
}
FVector2D AHexGrid::IndexToCoordinates(int32 Index)
{
	int32 iArrayX = Index % GetArrayLength();
	int32 iArrayY = Index / GetArrayLength();


	return FVector2D(iArrayX - GetArrayCenter(), iArrayY - GetArrayCenter());
}
int32 AHexGrid::GetArrayLength()
{
	return (2 * GridRadius) - 1;
}
int32 AHexGrid::GetArrayCenter()
{
	return GridRadius - 1;
}
void AHexGrid::HighlightPathTo(AActor* From, ATile* Target)
{
	if (From == nullptr || Target == nullptr)
	{
		return;
	}
	for (ATile* Tile : Tiles)
	{
		if (Tile)
		{
			Tile->Highlight = false;
		}
	}

	TArray<ATile*> Path;
	ATile* FromTile = GetTileFromWorldPosition( From->GetActorLocation() );
	PathTo(FromTile, Target, Path);

	for (ATile* Tile : Path)
	{
		Tile->Highlight = true;
	}
}

bool AHexGrid::PathTo(ATile* Start, ATile* End, TArray<ATile*>& Path)
{
	struct Node
	{
		Node() : Tile(nullptr), F(0.0f), G(0.0f), H(0.0f), CameFrom(-1) {}
		Node(ATile* tile, float g, float h, int32 cameFrom)
			: Tile(tile), F(g + h), G(g), H(h), CameFrom(cameFrom) {}
		Node(const Node& Copy)
			: Tile(Copy.Tile), F(Copy.F), G(Copy.G), H(Copy.H), CameFrom(Copy.CameFrom) {}

		ATile* Tile;
		float F;
		float G;
		float H;
		int32 CameFrom;

		bool operator==(const Node& RHS) const { return Tile == RHS.Tile; }
		bool operator==(int32 RHS) const { return Tile && Tile->Index == RHS; }
		bool operator<(const Node& RHS) const { return F < RHS.F; }
	};
	TArray<Node> OpenSet;
	TArray<Node> ClosedSet;

	OpenSet.Emplace(Start, 0, FVector::Dist(Start->GetActorLocation(), End->GetActorLocation()), -1);

	while (OpenSet.Num() > 0)
	{
		Node CurrentNode = OpenSet[0];

		ClosedSet.Add(CurrentNode);
		OpenSet.RemoveAtSwap(0);

		if (CurrentNode == End->Index)
		{
			// done
			TArray<ATile*> ReversePath;
			Node* PathNode = &CurrentNode;
			while (PathNode->CameFrom != -1)
			{
				ReversePath.Add(PathNode->Tile);
				PathNode = ClosedSet.FindByKey(PathNode->CameFrom);
			}
			while( ReversePath.Num() > 0 )
			{
				ATile* Tile = ReversePath.Pop();
				if (Tile && !Tile->Blocked && Tile->Occupier == nullptr)
				{
					Path.Add(Tile);
				}
			}
			return true;
		}
		for (int32 i = 0; i < 6; i++)
		{
			ATile* Neighbour = GetTileInDirection(CurrentNode.Tile, i);
			// if closed or blocked, continue	
			if (Neighbour == nullptr || Neighbour->Blocked || Neighbour->Occupier != nullptr)
			{ 
				if (End != Neighbour)
				{
					continue;
				}
			}
			if ( ClosedSet.FindByKey(Neighbour->Index) != nullptr )
			{
				continue;
			}
			float tentative_g_score = CurrentNode.G + TileRadius * 2.0f;
			Node* NeighbourNodePtr = OpenSet.FindByKey(Neighbour->Index);
			if (NeighbourNodePtr == nullptr)
			{
				OpenSet.Emplace(Neighbour, tentative_g_score, FVector::Dist(Neighbour->GetActorLocation(), End->GetActorLocation()), CurrentNode.Tile->Index);
			}
			else if (NeighbourNodePtr->G > tentative_g_score)
			{
				NeighbourNodePtr->G = tentative_g_score;
				NeighbourNodePtr->CameFrom = CurrentNode.Tile->Index;
			}
		}
		OpenSet.Sort();
	}
	return false;
}