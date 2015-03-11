// (C) 2015

#include "AAPA2.h"
#include "TileMover.h"

#include "Grid/Grid.h"
#include "AAPA2GameMode.h"

// Sets default values for this component's properties
UTileMover::UTileMover()
	: Facing(0)
	, MoveProgress(1.0f)
	, TargetTile(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	Alliegence = EAllieganceEnum::AE_None;
}


// Called when the game starts
void UTileMover::InitializeComponent()
{
	Super::InitializeComponent();

	// Snap to nearest grid point
	if (AGrid::GetStaticGrid() && GetOwner())
	{
		ATile* StartingTile = AGrid::GetStaticGrid()->GetTileFromWorldPosition(GetOwner()->GetActorLocation());
		SetOccupiedTile(StartingTile);
		SnapToTile(CurrentTile.Get());
	}

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->RegisterMover(this);
	}
}
void UTileMover::UninitializeComponent()
{
	Super::UninitializeComponent();

	AAAPA2GameMode* GameMode = Cast<AAAPA2GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->UnregisterMover(this);
	}
	SetOccupiedTile(nullptr);
}


// Called every frame
void UTileMover::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If moving, move
	if (MoveProgress < 1.0f)
	{ 
		MoveProgress += DeltaTime;

		if (MoveProgress >= 1.0f)
		{
			SnapToTile(TargetTile.Get());
			TargetTile = nullptr;
		}
		else
		{
			GetOwner()->SetActorLocation(FMath::Lerp(PreviousPosition, TargetTile->GetActorLocation(), MoveProgress));
			FRotator xTargetDir = (TargetTile->GetActorLocation() - PreviousPosition).Rotation();
			GetOwner()->SetActorRotation(FMath::Lerp(GetOwner()->GetActorRotation(), xTargetDir, MoveProgress));
		}
	}
}

bool UTileMover::Move(int32 Direction)
{
	ATile* NewTile = AGrid::GetStaticGrid()->GetTileInDirection(CurrentTile.Get(), Direction);
	if (!NewTile->Blocked && NewTile->Occupier == nullptr)
	{
		TargetTile = NewTile;
		Facing = Direction;
		return true;
	}
	return false;
}

bool UTileMover::MoveTowardsTile(ATile* NewTile)
{
	ATile* StartTile = CurrentTile.Get();
	TArray<ATile*> NewPath;
	if (AGrid::GetStaticGrid()->PathTo(StartTile, NewTile, NewPath) && NewPath.Num() > 0)
	{
		if (!NewPath[0]->Blocked && NewPath[0]->Occupier == nullptr)
		{
			for (int i = 0; i < 6; i++)
			{
				if (NewPath[0] == StartTile->GetNeighbour(i))
				{
					Facing = i;
					break;
				}
			} 
			TargetTile = NewPath[0];
			return true;
		}
	}
	return false;
}


bool UTileMover::TeleportToTile(ATile* NewTile)
{
	if (!NewTile->Blocked && NewTile->Occupier == nullptr)
	{
		SetOccupiedTile(NewTile);
		SnapToTile(CurrentTile.Get());
		return true;
	}
	return false;
}

void UTileMover::ProcessTurn()
{
	if(TargetTile != nullptr)
	{
		MoveProgress = 0.0f;
		SetOccupiedTile(TargetTile.Get());
	}
}

void UTileMover::SetOccupiedTile(ATile* Tile)
{
	if (GetOwner())
	{
		PreviousPosition = GetOwner()->GetActorLocation();
	}
	if (CurrentTile.Get() && CurrentTile.Get()->Occupier == GetOwner())
	{
		CurrentTile->Occupier = nullptr;
		CurrentTile->Alliegence = EAllieganceEnum::AE_None;
	}
	CurrentTile = Tile;
	if (CurrentTile != nullptr)
	{ 
		CurrentTile->Occupier = GetOwner();
		CurrentTile->Alliegence = Alliegence;
	}
}
void UTileMover::SnapToTile(ATile* Tile)
{
	if (Tile != nullptr)
	{
		GetOwner()->SetActorLocation(Tile->GetActorLocation());
		PreviousPosition = Tile->GetActorLocation();
	}
}
