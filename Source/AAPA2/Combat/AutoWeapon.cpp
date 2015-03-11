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

void UAutoWeapon::ProcessTurn_PreMove()
{
	while (Beams.Num() > 0)
	{
		UParticleSystemComponent* ParticleTemp = Beams.Pop();
		ParticleTemp->DestroyComponent();
	}
	
	if (FirePreMove)
	{
		Fire();
	}
}

void UAutoWeapon::ProcessTurn_PostMove()
{
	if (!FirePreMove)
	{
		Fire();
	}
}
void UAutoWeapon::Fire()
{
	UTileMover* Mover = Cast<UTileMover>(GetOwner()->GetComponentByClass(UTileMover::StaticClass()));
	// get hexes in arc

	for (int32 r = RangeMin; r <= RangeMax; r++)
	{
		for (int32 i = ArcStart; i <= ArcStop; i++)
		{
			int32 dir = i + Mover->Facing;
			while (dir < 0) { dir += 6; }
			dir %= 6;
			ATile* StartTile = AGrid::GetStaticGrid()->GetTileInDirection(Mover->CurrentTile.Get(), dir, r);

			for (int32 j = 0; j < (i == ArcStop ? 1 : r); j++)
			{
				int iNextDir = (dir + 1) % 6;
				ATile* TargetTile = AGrid::GetStaticGrid()->GetTileInDirection(StartTile, iNextDir, j);
				AActor* TargetActor = (TargetTile != nullptr) ? TargetTile->Occupier.Get() : nullptr;
				UDamagable* TargetComponent = (TargetActor != nullptr) ? Cast<UDamagable>(TargetActor->GetComponentByClass(UDamagable::StaticClass())) : nullptr;
				if (TargetComponent && Alliegance::IsHostile(Mover->Alliegence, TargetComponent->Alliegence))
				{
					TargetComponent->ApplyDamage(Damage, GetOwner()->GetActorLocation());

					UParticleSystemComponent* ParticleTemp = UGameplayStatics::SpawnEmitterAttached(Beam, 
						GetOwner()->GetRootComponent(), NAME_None, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), 
						EAttachLocation::KeepWorldPosition, true);
					if (ParticleTemp)
					{
						ParticleTemp->InstanceParameters.Add(FParticleSysParam());
						ParticleTemp->InstanceParameters[0].Name = "BeamSource";
						ParticleTemp->InstanceParameters[0].Actor = GetOwner();
						ParticleTemp->InstanceParameters.Add(FParticleSysParam());
						ParticleTemp->InstanceParameters[1].Name = "BeamTarget";
						ParticleTemp->InstanceParameters[1].Actor = TargetActor;
						
						Beams.Add(ParticleTemp);
					}
				}
			}
		}
	}
}
