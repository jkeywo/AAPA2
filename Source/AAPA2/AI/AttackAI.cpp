// (C) 2015

#include "AAPA2.h"
#include "AttackAI.h"


// Sets default values for this component's properties
UAttackAI::UAttackAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackAI::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UAttackAI::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

