// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Alliegance.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class AGrid;

UCLASS()
class AAPA2_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SetGrid(AGrid* NewGrid, int32 NewIndex);
	void SetCoordinate(FVector2D Coordinates);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SetSelected();
	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SetDeselected();
	UFUNCTION(BlueprintPure, Category = "Selection")
	bool IsSelected();

	UFUNCTION(BlueprintImplementableEvent, Category = Events)
	void OnSelected();
	UFUNCTION(BlueprintImplementableEvent, Category = Events)
	void OnDeselected();

	UFUNCTION(BlueprintCallable, Category = Grid)
	ATile* GetNeighbour( int32 Direction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Highlight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Blocked;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> Occupier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Index;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D Coordinates;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAllieganceEnum Alliegence;

protected:
	UPROPERTY()
	AGrid* Grid;
};
