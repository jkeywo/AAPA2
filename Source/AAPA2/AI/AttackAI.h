// (C) 2015

#pragma once

#include "AI/AI.h"
#include "AttackAI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UAttackAI : public UAI
{
	GENERATED_BODY()

public:	
	UAttackAI();

	virtual void InitializeComponent() override;
	virtual void ProcessTurn();
};
