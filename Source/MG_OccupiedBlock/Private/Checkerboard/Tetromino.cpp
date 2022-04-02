// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkerboard/Tetromino.h"

#include "Checkerboard/CheckerboardController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATetromino::ATetromino()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootScene"));
	ContainerSceneComponentPtr = CreateDefaultSubobject<USceneComponent>(TEXT("ContainerScene"));
	ContainerSceneComponentPtr->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

ATetromino::ATetromino(TSubclassOf<UTetrominoOrigin> OC) : OriginClass(OC)
{
	ATetromino();
}

ATetromino::ATetromino(TSubclassOf<ABlock> BC) : BlockClass(BC)
{
	ATetromino();
}

void ATetromino::SpawnBlocks()
{
	//const FTransform TetrominoTransform = GetActorTransform();
	//FVector2D Center = Origin->GetOffsetCenter();
	//float OffsetX = Center.X;
	//float OffsetY = Center.Y;
	//AddActorWorldOffset(FVector(-OffsetX * BlockWidthHeight, -OffsetY * BlockWidthHeight, 0));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	TArray<FVector2D> BlockOccupationArray;
	Origin->GetBlockOccupationArrayRef(BlockOccupationArray);
	for (FVector2D BlockOccupation : BlockOccupationArray)
	{
		const float Col = BlockOccupation.X;
		const float Row = BlockOccupation.Y;
		FTransform BlockRelativeTransform;
		FVector BlockLocation = FVector(Col * BlockWidthHeight, Row * BlockWidthHeight, 0);
		BlockRelativeTransform.SetLocation(BlockLocation);
		//FTransform BlockWorldTransform = UKismetMathLibrary::ComposeTransforms(BlockRelativeTransform, TetrominoTransform);
		//ABlock* BlockActor = GetWorld()->SpawnActor<ABlock>(BlockClass, BlockWorldTransform, SpawnParameters);
		ABlock* BlockActor = GetWorld()->SpawnActor<ABlock>(BlockClass, BlockRelativeTransform, SpawnParameters);
		BlockActor->IndexCol = Col;
		BlockActor->IndexRow = Row;
		//BlockActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	
		//BlockActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		BlockActor->AttachToComponent(ContainerSceneComponentPtr, FAttachmentTransformRules::KeepRelativeTransform);
		BlockInstances.Add(BlockActor);
	}

}

void ATetromino::RotateTo(float Degrees)
{
	// 数据层旋转
	Origin->RotateTo(Degrees);
	// 表现层旋转
	bIsRotating = true;
	RotationTarget = FRotator(0, Degrees, 0);
	RotationTarget = FRotator(0, Degrees, 0);
}

void ATetromino::Rotate90Degrees(float Scale)
{
	RotateTo(Origin->GetRotateDegree() + 90 * Scale);
}

void ATetromino::MoveToWorldLocation(FVector TargetLocation)
{
	MoveTargetWorldLocation = TargetLocation;
	bIsMoveing = true;
}

int32 ATetromino::GetSide()
{
	return Origin->GetSide();
}

void ATetromino::SetSide(int32 Side)
{
	Origin->SetSide(Side);
}

void ATetromino::GetOriginBlockOccupations(TArray<FVector2D>& Out)
{
	Out = Origin->GetBlockOccupationArray();
}

UTetrominoOrigin* ATetromino::GetTetrominoOrigin()
{
	return Origin;
}

void ATetromino::HandleChangeSide(int32 Side)
{
	FLinearColor Color = CheckerboardController->GetColorBySide(Side);
	for (ABlock* BlockInstance : BlockInstances)
	{
		if(BlockInstance != nullptr)
		{
			BlockInstance->SetSideAndColor(Side, Color);
		}
	}
}

// Called when the game starts or when spawned
void ATetromino::BeginPlay()
{
	Super::BeginPlay();
	// 实例化拼图块元数据
	Origin = NewObject<UTetrominoOrigin>(this, OriginClass);
	Origin->OnChangeSide.AddUObject(this, &ATetromino::HandleChangeSide);
	Origin->GetOffsetCenter();
	//HandleChangeSide(Origin->GetSide());
	SpawnBlocks();
}

// Called every frame
void ATetromino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsRotating)
	{
		const FRotator CurrentRotation = ContainerSceneComponentPtr->GetRelativeRotation();
		if ((CurrentRotation - RotationTarget).IsNearlyZero())
		{
			//SetActorRelativeRotation(RotationTarget);
			//SetActorRotation(RotationTarget);
			ContainerSceneComponentPtr->SetRelativeRotation(RotationTarget);
			bIsRotating = false;

		}
		else
		{
			//SetActorRelativeRotation(FMath::RInterpTo(CurrentRotation, RotationTarget, DeltaTime, 10));
			//SetActorRotation(FMath::RInterpTo(CurrentRotation, RotationTarget, DeltaTime, 10));
			ContainerSceneComponentPtr->SetRelativeRotation(FMath::RInterpTo(CurrentRotation, RotationTarget, DeltaTime, 10));
		}

	}

	if (bIsMoveing)
	{
		const FVector CurrentLocation = GetActorLocation();
		if ((CurrentLocation - MoveTargetWorldLocation).IsNearlyZero())
		{
			SetActorLocation(MoveTargetWorldLocation);
			bIsMoveing = false;

		}
		else
		{
			SetActorLocation(FMath::VInterpTo(CurrentLocation, MoveTargetWorldLocation, DeltaTime, 10));
		}

	}
}

