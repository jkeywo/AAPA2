// (C) 2015

#include "AAPA2.h"
#include "AutoWeapon.h"

#include "Combat/Damagable.h"
#include "Grid/Grid.h"
#include "TempActorManager.h"
#include "TileMover.h"
#include "FuelComponent.h"

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
bool RequiresActivation;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
int32 FuelCost;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
bool Active;




void Rotate60DegreesClockwise(FVector2D& Position)
{
	float X = Position.X + Position.Y;
	Position.Y = -Position.X;
	Position.X = X;
}

void UAutoWeapon::ProcessTurn_PreMove()
{
	while(Beams.Num() > 0)
	{
		Beams.Pop()->DestroyComponent();
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
	if (Mover == nullptr)
	{
		return;
	}

	if (RequiresActivation && !Active)
	{
		return;
	}
	Active = false;

	if (FuelCost > 0)
	{
		UFuelComponent* Fuel = Cast<UFuelComponent>(GetOwner()->GetComponentByClass(UFuelComponent::StaticClass()));
		if (Fuel == nullptr || Fuel->CurrentFuel < FuelCost)
		{
			return;
		}
		Fuel->CurrentFuel -= FuelCost;
	}

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
					FVector TargetPosition = TargetActor->GetActorLocation();
					bool Destroyed = TargetComponent->ApplyDamage(Damage, GetOwner()->GetActorLocation());
					UParticleSystemComponent* ParticleTemp = UGameplayStatics::SpawnEmitterAttached(Beam, 
						GetOwner()->GetRootComponent(), NAME_None, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), 
						EAttachLocation::KeepWorldPosition, true);

					if (Destroyed)
					{
						AActor* NewActor = World->SpawnActor<AActor>(AActor::StaticClass(), TargetPosition, FRotator::ZeroRotator);
						USceneComponent* NewComponent = NewObject<USceneComponent>(NewActor);
						NewActor->SetRootComponent(NewComponent);
						NewActor->SetActorLocation(TargetPosition);
						TempActorManager::AddActor(NewActor, 0.9f);
						TargetActor = NewActor;
					}

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
