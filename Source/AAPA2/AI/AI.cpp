// (C) 2015

#include "AAPA2.h"
#include "AI.h"

#include "AAPA2GameMode.h"

// Sets default values for this component's properties
UAI::UAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAI::InitializeComponent()
{
	Super::InitializeComponent();

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->RegisterAI(this);
	}
}
void UAI::UninitializeComponent()
{
	Super::UninitializeComponent();

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->UnregisterAI(this);
	}
}



// Called every frame
void UAI::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

