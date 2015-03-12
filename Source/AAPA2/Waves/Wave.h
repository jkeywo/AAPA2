// (C) 2015

#pragma once

#include "AI/AI.h"
#include "Wave.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AAPA2_API UWave : public UAI
{
	GENERATED_BODY()

public:
	virtual void ProcessTurn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	TSubclassOf<class AActor> SpawnType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	int32 Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	int32 Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	int32 SpawnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wave)
	UParticleSystem* WaveInPFX;
};
