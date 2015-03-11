// (C) 2015

#include "AAPA2.h"
#include "AttackAI.h"

#include "Combat/Damagable.h"
#include "AAPA2GameMode.h"
#include "TileMover.h"

// Sets default values for this component's properties
UAttackAI::UAttackAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAttackAI::InitializeComponent()
{
	Super::InitializeComponent();
	
}

void UAttackAI::ProcessTurn()
{
	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode == nullptr)
	{
		return;
	}

	// find closest hostile target and move to it
	float ClosestDistance = FLT_MAX;
	AActor* ClosestActor = nullptr;
	for (int32 i = 0; i < static_cast<int32>(EAllieganceEnum::Count); i++)
	{
		EAllieganceEnum TargetAlliegance = static_cast<EAllieganceEnum>(i);
		if (!Alliegance::IsHostile(Alliegence, TargetAlliegance))
		{
			continue;
		}
		TSet< UDamagable* >& Targets = GameMode->GetTargets(TargetAlliegance);
		for (UDamagable* Target : Targets)
		{
			float Distance = FVector::Dist(Target->GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestActor = Target->GetOwner();
			}
		}
	}

	UTileMover* Mover = Cast<UTileMover>(GetOwner()->GetComponentByClass(UTileMover::StaticClass()));
	UTileMover* TargetMover = ClosestActor != nullptr ? Cast<UTileMover>(ClosestActor->GetComponentByClass(UTileMover::StaticClass())) : nullptr;
	if (Mover != nullptr && ClosestActor != nullptr)
	{
		Mover->MoveTowardsTile( TargetMover->CurrentTile.Get() );
	}
}
