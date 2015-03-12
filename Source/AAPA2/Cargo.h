// (C) 2015

#pragma once

#include "Components/ActorComponent.h"
#include "Cargo.generated.h"

UENUM(BlueprintType)
enum class ECargoType : uint8
{
	CE_Food 		UMETA(DisplayName = "Food"),
	CE_Ore 			UMETA(DisplayName = "Ore"),
	CE_Machinery	UMETA(DisplayName = "Machinery"),

	Count
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AAPA2_API UCargo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCargo();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cargo)
	int32 Food;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cargo)
	int32 Ore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cargo)
	int32 Machinery;

	UFUNCTION(BlueprintCallable, Category = Cargo)
	int32 GetCargo(ECargoType CargoType);
	UFUNCTION(BlueprintCallable, Category = Cargo)
	int32 SetCargo(ECargoType CargoType, int32 Amount);
	UFUNCTION(BlueprintCallable, Category = Cargo)
	int32 AddCargo(ECargoType CargoType, int32 Amount);
	UFUNCTION(BlueprintCallable, Category = Cargo)
	bool RemoveCargo(ECargoType CargoType, int32 Amount);
	UFUNCTION(BlueprintCallable, Category = Cargo)
	bool HasCargo(ECargoType CargoType, int32 Amount);

};
