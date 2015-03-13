// (C) 2015

#include "AAPA2.h"
#include "Weapon.h"

#include "AAPA2GameMode.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;

}


// Called when the game starts
void UWeapon::InitializeComponent()
{
	Super::InitializeComponent();

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->RegisterWeapon(this);
	}
}
void UWeapon::DestroyComponent(bool bPromoteChildren /*= false*/)
{
	Super::DestroyComponent(bPromoteChildren);

	AAAPA2GameMode* GameMode = GetWorld() ? Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
	if (GameMode != nullptr)
	{
		GameMode->UnregisterWeapon(this);
	}
}
