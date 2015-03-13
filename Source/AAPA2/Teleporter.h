// (C) 2015

#pragma once

#include "Components/ActorComponent.h"
#include "Teleporter.generated.h"

class ATile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UTeleporter : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTeleporter();
	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable, Category = Teleport)
	void Teleport(ATile* Tile);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FuelCost;
};
