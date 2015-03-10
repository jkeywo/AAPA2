// (C) 2015

#pragma once

#include "AI/AI.h"
#include "AttackAI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UAttackAI : public UAI
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackAI();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
