#include "AAPA2.h"
#include "TempActorManager.h"

TArray< TempActorManager::ActorData > TempActorManager::ActorDataArray;

void TempActorManager::Initialise()
{
	ActorDataArray.Empty();
}
void TempActorManager::Tick(float DeltaTime)
{
	for (int32 i = 0; i < ActorDataArray.Num(); )
	{
		ActorDataArray[i].Duration -= DeltaTime;
		if (ActorDataArray[i].Duration <= 0.0f)
		{
			AActor* OldActor = ActorDataArray[i].Actor;
			ActorDataArray.RemoveAtSwap(i);
			OldActor->Destroy();
		}
		else
		{
			i++;
		}
	}
}
void TempActorManager::Shutdown()
{
	ActorDataArray.Empty();
}

void TempActorManager::AddActor(AActor* Actor, float Duration)
{
	ActorDataArray.Add(ActorData(Actor, Duration));
}
UParticleSystemComponent* TempActorManager::AddParticle(AActor* TempActor, UParticleSystem* Particles, FVector Position, FRotator Orientation, float Duration)
{
	UParticleSystemComponent* NewParticle = UGameplayStatics::SpawnEmitterAttached(Particles,
		TempActor->GetRootComponent(), NAME_None, Position, Orientation,
		EAttachLocation::KeepWorldPosition, true);

	ActorDataArray.Add(ActorData(TempActor, Duration));

	return NewParticle;
}


