
#include "AAPA2.h"
#include "Waves/Wave.h"

#include "Grid/Grid.h"
#include "Grid/Tile.h"
#include "TempActorManager.h"

void UWave::ProcessTurn()
{
	if (Delay > 0)
	{
		Delay -= 1;
	}
	else if (Duration > 0)
	{
		Duration -= 1;

		ATile* CurrentTile = AGrid::GetStaticGrid()->GetTileFromWorldPosition(GetOwner()->GetActorLocation());
		for (int32 i = 0; i < SpawnRate; i++)
		{
			// Find random nearby tile
			int Range = 0;
			ATile* Tile = nullptr;
			while (Tile == nullptr && Range < 100)
			{
				Range += 1;
				for (int32 j = 0; j < 6; j++)
				{
					ATile* PotentialTile = AGrid::GetStaticGrid()->GetTileInDirection(CurrentTile, j, Range);
					if (PotentialTile != nullptr && !PotentialTile->Blocked && PotentialTile->Occupier == nullptr)
					{
						Tile = PotentialTile;
						break;
					}
				}
			}

			// Spawn in enemy
			if (Tile != nullptr)
			{
				FVector Position = Tile->GetActorLocation();
				AActor* Enemy = GetOwner()->GetWorld()->SpawnActor<AActor>(SpawnType, Position, FRotator::ZeroRotator);
				if (Enemy)
				{
					Enemy->AttachRootComponentToActor(GetOwner());
					Enemy->SetActorLocation(Position);

					AActor* TempActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), Position, Tile->GetActorRotation());
					USceneComponent* NewComponent = NewObject<USceneComponent>(TempActor);
					TempActor->SetRootComponent(NewComponent);
					TempActor->SetActorLocation(Position);
					TempActorManager::AddParticle(TempActor, WaveInPFX, Position, Tile->GetActorRotation(), 0.9f);
				}
			}
		}
	}
}