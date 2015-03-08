// (C) 2015

#include "AAPA2.h"
#include "TileMover.h"

#include "Grid/Grid.h"

// Sets default values for this component's properties
UTileMover::UTileMover()
	: MoveTime(0.0f)
	, MoveProgress(0.0f)
	, OccupiedTile(nullptr)
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
		CurrentTile = AGrid::GetStaticGrid()->GetTileFromWorldPosition(GetOwner()->GetActorLocation());
		SnapToTile(CurrentTile.Get());
		SetOccupiedTile(CurrentTile.Get());
	}
	if (ControlTime)
	{
		GetWorld()->GetWorldSettings()->TimeDilation = 0.0f;
	}
}


// Called every frame
void UTileMover::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If moving, move
	if (Path.Num() > 0)
	{ 
		MoveProgress += DeltaTime / MoveTime;

		if (MoveProgress >= 1.0f)
		{
			CurrentTile = Path[0];
			Path.RemoveAt(0);
			SnapToTile(CurrentTile.Get());
			MoveProgress -= 1.0f;
		}

		if (Path.Num() > 0)
		{
			GetOwner()->SetActorLocation(FMath::Lerp(CurrentTile->GetActorLocation(), Path[0]->GetActorLocation(), MoveProgress));
			FRotator xTargetDir = (Path[0]->GetActorLocation() - CurrentTile->GetActorLocation()).Rotation();
			GetOwner()->SetActorRotation(FMath::Lerp(GetOwner()->GetActorRotation(), xTargetDir, MoveProgress));
		}

		if (ControlTime && Path.Num() == 0)
		{
			GetWorld()->GetWorldSettings()->TimeDilation = 0.0f;
		}
	}
}

void UTileMover::Move(int32 Direction, float OverTime)
{
	ATile* NewTile = nullptr;
	if (Path.Num() == 0)
	{
		NewTile = AGrid::GetStaticGrid()->GetTileInDirection(CurrentTile.Get(), Direction);
	}
	else
	{
		NewTile = AGrid::GetStaticGrid()->GetTileInDirection(Path.Top(), Direction);
	}

	MoveToTile(NewTile, OverTime);
}

void UTileMover::MoveToTile(ATile* NewTile, float OverTime)
{
	if (NewTile != nullptr)
	{
		if (NewTile->Blocked || NewTile->Occupier != nullptr)
		{
			return;
		}

		Path.Push(NewTile);

		MoveTime = OverTime / Path.Num();
		if (ControlTime)
		{
			GetWorld()->GetWorldSettings()->TimeDilation = 1.0f;
		}

		SetOccupiedTile(NewTile);
	}
}
void UTileMover::MoveTowardsTile(ATile* NewTile, float OverTime)
{
	ATile* StartTile = Path.Num() == 0 ? CurrentTile.Get() : Path.Top();
	TArray<ATile*> NewPath;
	if (AGrid::GetStaticGrid()->PathTo(StartTile, NewTile, NewPath) && NewPath.Num() > 0)
	{
		MoveToTile(NewPath[0], OverTime);
	}
}

void UTileMover::PathToTile(ATile* NewTile, float Speed)
{
	ATile* StartTile = Path.Num() == 0 ? CurrentTile.Get() : Path.Top();
	TArray<ATile*> NewPath;
	if (AGrid::GetStaticGrid()->PathTo(StartTile, NewTile, NewPath) && NewPath.Num() > 0)
	{
		MoveTime += Speed * NewPath.Num();
		Path += NewPath;
		SetOccupiedTile(Path.Top());
	}
}

void UTileMover::TeleportToTile(ATile* NewTile)
{
	Path.Empty();
	CurrentTile = NewTile;
	SnapToTile(CurrentTile.Get());
	SetOccupiedTile(NewTile);
}

void UTileMover::SnapToTile(ATile* Tile)
{
	if (Tile != nullptr)
	{
		GetOwner()->SetActorLocation(Tile->GetActorLocation());
	}
}

void UTileMover::SetOccupiedTile(ATile* Tile)
{
	if (OccupiedTile.Get() && OccupiedTile.Get()->Occupier == GetOwner())
	{
		OccupiedTile->Occupier = nullptr;
		OccupiedTile->Alliegence = EAllieganceEnum::AE_None;
	}
	OccupiedTile = Tile;
	if (OccupiedTile != nullptr)
	{ 
		OccupiedTile->Occupier = GetOwner();
		OccupiedTile->Alliegence = Alliegence;
	}
}