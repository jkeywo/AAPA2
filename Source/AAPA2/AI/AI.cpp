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
}


// Called when the game starts
void UAI::InitializeComponent()
{
	Super::InitializeComponent();

	AAAPA2GameMode* GameMode = GameMode = GetWorld() ? Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
	if (GameMode != nullptr)
	{
		GameMode->RegisterAI(this);
	}
}
void UAI::DestroyComponent(bool bPromoteChildren /*= false*/)
{
	Super::DestroyComponent(bPromoteChildren);

	AAAPA2GameMode* GameMode = GameMode = GetWorld() ? Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
	if (GameMode != nullptr)
	{
		GameMode->UnregisterAI(this);
	}
}


