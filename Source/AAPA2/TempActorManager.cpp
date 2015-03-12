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
UParticleSystemComponent* TempActorManager::AddParticle(UWorld* World, UParticleSystem* Particles, FVector Position, FRotator Orientation, float Duration)
{
	AActor* NewActor = World->SpawnActor<AActor>(AActor::StaticClass(), Position, Orientation);

	UParticleSystemComponent* NewParticle = UGameplayStatics::SpawnEmitterAttached(Particles,
		NewActor->GetRootComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::KeepWorldPosition, true);

	ActorDataArray.Add(ActorData(NewActor, Duration));

	return NewParticle;
}


