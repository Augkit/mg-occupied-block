// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkerboard/Checkerboard.h"
#include "Checkerboard/CheckerboardController.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACheckerboard::ACheckerboard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACheckerboard::SpawnBlocks()
{
	const FTransform CheckerboardTransform = GetActorTransform();
	// 每个棋盘格需要进行偏移，让棋盘的正中心保持在Actor的WorldLocation的位置
	const float CenterOffset = (Size - 1) * WidthHeight / 2;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	for (int32 Row = 0; Row < Size; Row++)
	{
		for (int32 Col = 0; Col < Size; Col++)
		{
			//棋盘格的相对位置
			FTransform BlockRelativeTransform;
			FVector BlockLocation = FVector(Col * WidthHeight - CenterOffset, Row * WidthHeight - CenterOffset, 0);
			BlockRelativeTransform.SetLocation(BlockLocation);
			// 将棋盘格的相对位置通过棋盘的Transform来进行偏移，计算出棋盘格附加在棋盘上之后的世界位置
			FTransform BlockWorldTransform = UKismetMathLibrary::ComposeTransforms(BlockRelativeTransform, CheckerboardTransform);

			ABlock* BlockActor = GetWorld()->SpawnActor<ABlock>(BlockClass, BlockWorldTransform, SpawnParameters);
			BlockActor->IndexCol = Col;
			BlockActor->IndexRow = Row;
			// 将生成的格子Attach到棋盘下面
			BlockActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			BlockInstances.Add(BlockActor);
		}
	}
}

void ACheckerboard::InitBlockSide(TArray<int32> Sides)
{
		
	for (ABlock* BlockInstance : BlockInstances)
	{
		int32 Side = GetDefaultSideByColRow(BlockInstance->IndexCol, BlockInstance->IndexRow);
		if(Sides.Find(Side) != INDEX_NONE)
		{
			BlockInstance->SetSideAndColor(Side, CheckerboardController->GetColorBySide(Side));
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
	FVector BlockLocation = FVector(Col * WidthHeight - CenterOffset, Row * WidthHeight - CenterOffset, 0);
	return UKismetMathLibrary::TransformLocation(CheckerboardTransform, BlockLocation);
}

FVector ACheckerboard::GetWorldLocationByBlock(ABlock* Block, bool& Success)
{
	for (int32 i = 0; i < BlockInstances.Num(); i++)
	{
		if (Block == BlockInstances[i])
		{
			Success = true;
			return GetWorldLocationByColRow(Block->IndexCol, Block->IndexRow);
		}
	}
	Success = false;
	return FVector();

}

ABlock* ACheckerboard::GetBlockByLocation(FVector2D Location)
{
	if(IsOutOfBounds(Location))
	{
		return nullptr;
	}
	int32 BlockIndex = GetBlockIndexByColRow(Location);
	return BlockInstances[BlockIndex];
}
bool ACheckerboard::IsOutOfBounds(FVector2D Location)
{
	int32 Col = FMath::RoundToInt(Location.X);
	int32 Row = FMath::RoundToInt(Location.Y);
	return Col < 0 || Col >= Size || Row < 0 || Row >= Size;
}

int32 ACheckerboard::GetScoreBySide(int32 Side)
{
	int32 Score = 0;
	for (ABlock* BlockInstance : BlockInstances)
	{
		if (BlockInstance->Side == Side)
		{
			++Score;
		}
	}
	return Score;
}

bool ACheckerboard::IsSameSideByLocation(int32 Side, FVector2D Location)
{
	ABlock* TargetBlock = GetBlockByLocation(Location);
	if (IsValid(TargetBlock))
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

int32 ACheckerboard::GetDefaultSideByColRow(int32 Col, int32 Row)
{
	for (FBlockSide BlocksSide : DefaultBlocksSide)
	{
		if(BlocksSide.Col == Col && BlocksSide.Row == Row)
		{
			return BlocksSide.Side;
		}
	}
	return -1;
}

// Called when the game starts or when spawned
void ACheckerboard::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlocks();
}

void ACheckerboard::Destroyed()
{
	Super::Destroyed();
	for (ABlock* BlockInstance : BlockInstances)
	{
		if(IsValid(BlockInstance))
		{
			BlockInstance->Destroy();
		}
	}
}

// Called every frame
void ACheckerboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

