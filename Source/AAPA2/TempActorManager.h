

#pragma once

class AActor;
class UParticleSystem;
class UParticleSystemComponent;

class TempActorManager
{
public:
	static void Initialise();
	static void Tick(float DeltaTime);
	static void Shutdown();

	static void AddActor(AActor* Actor, float Duration);
	static UParticleSystemComponent* AddParticle(AActor* Actor, UParticleSystem* Particles, FVector Position, FRotator Orientation, float Duration);

protected:
	struct ActorData
	{
		ActorData(AActor* actor, float duration)
			: Actor(actor), Duration(duration) {}
		bool operator== (const ActorData& RHS) const { return Actor == RHS.Actor; }

		AActor* Actor;
		float Duration;
	};
	static TArray< ActorData > ActorDataArray;

};