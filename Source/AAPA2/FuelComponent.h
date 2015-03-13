// (C) 2015

#pragma once

#include "Components/ActorComponent.h"
#include "FuelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UFuelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFuelComponent();

	virtual void InitializeComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fuel)
	int32 MaxFuel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fuel)
	int32 CurrentFuel;

	UFUNCTION(BlueprintCallable, Category = Fuel)
	bool CanRefuel();
	UFUNCTION(BlueprintCallable, Category = Fuel)
	void Refuel();

};
