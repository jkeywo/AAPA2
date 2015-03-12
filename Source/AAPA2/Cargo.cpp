// (C) 2015

#include "AAPA2.h"
#include "Cargo.h"

// Sets default values for this component's properties
UCargo::UCargo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCargo::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called every frame
void UCargo::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

int32 UCargo::GetCargo(ECargoType CargoType)
{
	switch (CargoType)
	{
	case ECargoType::CE_Food:		return Food;
	case ECargoType::CE_Ore:		return Ore;
	case ECargoType::CE_Machinery:	return Machinery;
	default:						return -1;
	}
}
int32 UCargo::SetCargo(ECargoType CargoType, int32 Amount)
{
	switch (CargoType)
	{
	case ECargoType::CE_Food:		Food = Amount;		return Food;
	case ECargoType::CE_Ore:		Ore = Amount;		return Ore;
	case ECargoType::CE_Machinery:	Machinery = Amount;	return Machinery;
	default:						return -1;
	}
}
int32 UCargo::AddCargo(ECargoType CargoType, int32 Amount)
{
	switch (CargoType)
	{
	case ECargoType::CE_Food:		Food += Amount;			return Food;
	case ECargoType::CE_Ore:		Ore += Amount;			return Ore;
	case ECargoType::CE_Machinery:	Machinery += Amount;	return Machinery;
	default:						return -1;
	}
}
bool UCargo::RemoveCargo(ECargoType CargoType, int32 Amount)
{
	if (HasCargo(CargoType, Amount))
	{
		AddCargo(CargoType, -Amount);
		return true;
	}
	return false;
}
bool UCargo::HasCargo(ECargoType CargoType, int32 Amount)
{
	switch (CargoType)
	{
	case ECargoType::CE_Food:		return Food >= Amount;
	case ECargoType::CE_Ore:		return Ore >= Amount;
	case ECargoType::CE_Machinery:	return Machinery >= Amount;
	default:						return false;
	}
}
