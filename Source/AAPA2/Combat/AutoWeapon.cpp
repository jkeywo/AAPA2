// (C) 2015

#include "AAPA2.h"
#include "AutoWeapon.h"

#include "Combat/Damagable.h"
#include "Grid/Grid.h"
#include "TileMover.h"

void Rotate60DegreesClockwise(FVector2D& Position)
{
	float X = Position.X + Position.Y;
	Position.Y = -Position.X;
	Position.X = X;
}

void UAutoWeapon::ProcessTurn_PostMove()
{
	UTileMover* Mover = Cast<UTileMover>( GetOwner()->GetComponentByClass( UTileMover::StaticClass() ) );
	// get hexes in arc
	for (FVector2D TilePosition : TargetedTiles)
	{ 
		// apply damage to targets
		for (int i = 0; i < Mover->Facing; i++)
		{
			Rotate60DegreesClockwise(TilePosition);
		}
		TilePosition += Mover->CurrentTile->Coordinates;

		ATile* TargetTile = AGrid::GetStaticGrid()->GetTileByCoordinates(TilePosition);
		
		if (TargetTile != nullptr && TargetTile->Occupier != nullptr)
		{
			UDamagable* TargetComponent = Cast<UDamagable>(TargetTile->Occupier->GetComponentByClass(UDamagable::StaticClass()));
			if (TargetComponent != nullptr)
			{
				TargetComponent->ApplyDamage( Damage, GetOwner()->GetActorLocation() );

				// Play PFX

			}
		}
	}
}
