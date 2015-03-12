// (C) 2015

#include "AAPA2.h"
#include "Damagable.h"

#include "Combat/Weapon.h"
#include "AAPA2GameMode.h"
#include "TempActorManager.h"
#include "TileMover.h"

// Sets default values for this component's properties
UDamagable::UDamagable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UDamagable::InitializeComponent()
{
	Super::InitializeComponent();

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->RegisterTarget(this);
	}

	ShieldStates.Empty();
	ArmourStates.Empty();
	for (int i = 0; i < 4; i++)
	{ 
		if (HasDirectionalShields || i == 0)
		{
			ShieldStates.Add(HasShields ? 0 : -1);
		}
		if (HasDirectionalArmour || i == 0)
		{
			ArmourStates.Add(HasArmour);
		}
	}
	HullState = MaxHull;
}
void UDamagable::UninitializeComponent()
{
	Super::UninitializeComponent();

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->UnregisterTarget(this);
	}
	ShieldStates.Empty();
	ArmourStates.Empty();
}

void UDamagable::ProcessTurn()
{
	for (int32& Shield : ShieldStates)
	{
		if (Shield > 0)
		{
			Shield -= 1;
		}
	}
}

bool UDamagable::ApplyDamage(int32 Amount, FVector Origin)
{
	FVector HitDirection = Origin - GetOwner()->GetActorLocation();
	HitDirection.Normalize();

	FVector ForwardDirection = GetOwner()->GetActorForwardVector();
	
	float Dot = FVector::DotProduct(ForwardDirection, HitDirection);
	float Cross = (ForwardDirection.X * HitDirection.Z) + (ForwardDirection.Z * HitDirection.X);
	int32 Side = 0;
	if (Dot > 0.7f)
	{
		Side = 0;
	}
	else if (Dot < -0.7f)
	{
		Side = 2;
	}
	else if (Cross > 0.0f)
	{ 
		Side = 1;
	}
	else
	{
		Side = 3;
	}
	return ApplyDamageToSide(Amount, Side);
}
bool UDamagable::ApplyDamageToSide(int32 Amount, int32 Side)
{
	while (Amount > 0)
	{
		if (HasDirectionalShields && ShieldStates[Side] == 0)
		{
			ShieldStates[Side] = ShieldRechargeTime;
		}
		else if (!HasDirectionalShields && ShieldStates[0] == 0)
		{
			ShieldStates[0] = ShieldRechargeTime;
		}
		else if (HasDirectionalArmour && ArmourStates[Side])
		{
			ArmourStates[Side] = false;
		}
		else if (!HasDirectionalArmour && ArmourStates[0])
		{
			ArmourStates[0] = false;
		}
		else
		{
			HullState -= 1;
			if (HullState == 0)
			{
				if (DestroyedPFX != nullptr)
				{
					AActor* TempActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
					USceneComponent* NewComponent = NewObject<USceneComponent>(TempActor);
					TempActor->SetRootComponent(NewComponent);
					TempActor->SetActorLocation(GetOwner()->GetActorLocation());
					TempActorManager::AddParticle(TempActor, DestroyedPFX, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), 1.9f);
				}
				TempActorManager::AddActor(GetOwner(), 0.9f);
				
				UActorComponent* Weapon = GetOwner()->GetComponentByClass(UWeapon::StaticClass());
				while (Weapon != nullptr)
				{
					GetOwner()->RemoveOwnedComponent(Weapon);
					Weapon->DestroyComponent();
					Weapon = GetOwner()->GetComponentByClass(UWeapon::StaticClass());
				}
				UActorComponent* Mover = GetOwner()->GetComponentByClass(UTileMover::StaticClass());
				while (Mover != nullptr)
				{
					GetOwner()->RemoveOwnedComponent(Mover);
					Mover->DestroyComponent();
					Mover = GetOwner()->GetComponentByClass(UTileMover::StaticClass());
				}

				APawn* Pawn = Cast<APawn>(GetOwner());
				if (Pawn != nullptr)
				{
					Pawn->GetController()->UnPossess();
				}
				return true;
			}
		}
		Amount -= 1;
	}
	return false;
}

