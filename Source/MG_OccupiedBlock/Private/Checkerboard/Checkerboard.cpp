// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Checkerboard/Checkerboard.h"

// Sets default values
ACheckerboard::ACheckerboard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACheckerboard::SpawnBlocks()
{
	const FTransform CheckerboardTransform = GetActorTransform();
	const float CenterOffset = (Size - 1) * WidthHeight / 2;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	for (int32 Row = 0; Row < Size; Row++)
	{
		for (int32 Col = 0; Col < Size; Col++)
		{
			FTransform BlockRelativeTransform;
			FVector BlockLocation = FVector(Col * WidthHeight - CenterOffset, Row * WidthHeight - CenterOffset, 0);
			BlockRelativeTransform.SetLocation(BlockLocation);
			FTransform BlockWorldTransform = UKismetMathLibrary::ComposeTransforms(BlockRelativeTransform, CheckerboardTransform);

			ABlock* BlockActor = GetWorld()->SpawnActor<ABlock>(BlockClass, BlockWorldTransform, SpawnParameters);
			BlockActor->IndexCol = Col;
			BlockActor->IndexRow = Row;
			BlockActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			BlockInstances.Add(BlockActor);
		}
	}
}

int32 ACheckerboard::GetBlockIndexByColRow(FVector2D Location)
{
	return FMath::RoundToInt(Location.Y) * Size + FMath::RoundToInt(Location.X);
}

FVector ACheckerboard::GetWorldLocationByColRow(int32 Col, int32 Row)
{
	const FTransform CheckerboardTransform = GetActorTransform();
	const float CenterOffset = (Size - 1) * WidthHeight / 2;
	FVector BlockLocation;
	BlockLocation.X = Col * WidthHeight - CenterOffset;
	BlockLocation.Y = Row * WidthHeight - CenterOffset;
	return UKismetMathLibrary::TransformLocation(CheckerboardTransform, BlockLocation);
}

FVector ACheckerboard::GetWorldLocationByBlock(ABlock* Block, bool& Success)
{
	for (int32 i = 0; i < BlockInstances.Num(); i++)
	{
		if (Block == BlockInstances[i])
		{
			const FTransform CheckerboardTransform = GetActorTransform();
			Success = true;
			return GetWorldLocationByColRow(Block->IndexCol, Block->IndexRow);
		}
	}
	Success = false;
	return FVector();

}

ABlock* ACheckerboard::GetBlockByLocation(FVector2D Location)
{
	int32 BlockIndex = GetBlockIndexByColRow(Location);
	if (BlockIndex >= BlockInstances.Num() || BlockIndex < 0)
	{
		return nullptr;
	}
	return BlockInstances[BlockIndex];
}
bool ACheckerboard::IsOutOfBounds(FVector2D Location)
{
	int32 Col = FMath::RoundToInt(Location.X);
	int32 Row = FMath::RoundToInt(Location.Y);
	return Col < 0 || Col >= Size || Row < 0 || Row >= Size;
}

bool ACheckerboard::IsSameSideByLocation(int32 Side, FVector2D Location)
{
	ABlock* TargetBlock = GetBlockByLocation(Location);
	if(TargetBlock != nullptr)
	{
		return TargetBlock->Side == Side;
	}
	return false;
}

bool ACheckerboard::SetBlockSide(FVector2D Location, int32 Side)
{
	if (IsOutOfBounds(Location)) return false;
	int32 BlockIndex = GetBlockIndexByColRow(Location);
	FLinearColor SideColor = CheckerboardController->GetColorBySide(Side);
	BlockInstances[BlockIndex]->SetSideAndColor(Side, SideColor);
	return true;
}

void ACheckerboard::SetBlocksSide(TArray<FVector2D> BlockLocations, int32 Side)
{
	for (const FVector2D BlockLocation : BlockLocations)
	{
		SetBlockSide(BlockLocation, Side);
	}

}

void ACheckerboard::SetCheckerboardController(UCheckerboardController* CheckerboardControllerPtr)
{
	CheckerboardController = CheckerboardControllerPtr;
}

// Called when the game starts or when spawned
void ACheckerboard::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlocks();
}

// Called every frame
void ACheckerboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

