// (C) 2015

#pragma once

#include "Alliegance.h"
#include "Components/ActorComponent.h"
#include "AI.generated.h"


UCLASS()
class AAPA2_API UAI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAI();

	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAllieganceEnum Alliegence;

	virtual void ProcessTurn() {}
	
};
