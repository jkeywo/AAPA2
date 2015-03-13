// (C) 2015

#include "AAPA2.h"
#include "FuelComponent.h"

#include "Grid/Grid.h"
#include "TileMover.h"

UFuelComponent::UFuelComponent()
{
	bWantsInitializeComponent = true;
}

void UFuelComponent::InitializeComponent()
{
	Super::InitializeComponent();
	CurrentFuel = MaxFuel;
}

bool UFuelComponent::CanRefuel()
{
	// search adjacent tiles for allied tile movers
	AGrid* Grid = AGrid::GetStaticGrid();
	ATile* MyTile = Grid->GetTileFromWorldPosition( GetOwner()->GetActorLocation() );
	for (int32 i = 0; i < 6; i++)
	{
		ATile* Tile = Grid->GetTileInDirection(MyTile, i);
		if (Tile != nullptr && Tile->Occupier != nullptr)
		{
			UTileMover* TargetComponent = Cast<UTileMover>(Tile->Occupier->GetComponentByClass(UTileMover::StaticClass()));
			if (TargetComponent != nullptr && TargetComponent->Alliegence == EAllieganceEnum::AE_Ally )
			{
				return true;
			}
		}
	}
	return false;
}
void UFuelComponent::Refuel()
{
	// search adjacent tiles for allied tile movers
	AGrid* Grid = AGrid::GetStaticGrid();
	ATile* MyTile = Grid->GetTileFromWorldPosition(GetOwner()->GetActorLocation());
	for (int32 i = 0; i < 6; i++)
	{
		ATile* Tile = Grid->GetTileInDirection(MyTile, i);
		if (Tile != nullptr && Tile->Occupier != nullptr)
		{
			UTileMover* TargetComponent = Cast<UTileMover>(Tile->Occupier->GetComponentByClass(UTileMover::StaticClass()));
			if (TargetComponent != nullptr && TargetComponent->Alliegence == EAllieganceEnum::AE_Ally)
			{
				Tile->Alliegence = TargetComponent->Alliegence = EAllieganceEnum::AE_Neutral;
				CurrentFuel = MaxFuel;
				return;
			}
		}
	}
}

