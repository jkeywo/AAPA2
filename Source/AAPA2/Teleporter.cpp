// (C) 2015

#include "AAPA2.h"
#include "Teleporter.h"

#include "FuelComponent.h"
#include "TileMover.h"

// Sets default values for this component's properties
UTeleporter::UTeleporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UTeleporter::InitializeComponent()
{
	Super::InitializeComponent();
	
}

bool UTeleporter::Teleport(ATile* Tile)
{
	UFuelComponent* Fuel = Cast<UFuelComponent>(GetOwner()->GetComponentByClass(UFuelComponent::StaticClass()));
	UTileMover* Mover = Cast<UTileMover>(GetOwner()->GetComponentByClass(UTileMover::StaticClass()));
	if (Fuel == nullptr || Fuel->CurrentFuel < FuelCost || Mover == nullptr)
	{
		return false;
	}
	// charge fuel
	Fuel->CurrentFuel -= FuelCost;
	// teleport
	Mover->TeleportToTile(Tile);

	return true;
}
