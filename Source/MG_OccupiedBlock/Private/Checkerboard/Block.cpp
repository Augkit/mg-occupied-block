// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkerboard/Block.h"

// Sets default values
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	RootStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

FVector2D ABlock::GetRowCol()
{
	return  FVector2D(IndexCol, IndexRow);
}

void ABlock::SetColor(FLinearColor Color)
{

	if (MIColor == nullptr)
	{
		UMaterialInterface* ColorMaterial = RootStaticMesh->GetMaterial(ColorMaterialIndex);
		if (ColorMaterial != nullptr)
		{
			MIColor = UMaterialInstanceDynamic::Create(ColorMaterial, this);
			RootStaticMesh->SetMaterial(ColorMaterialIndex, MIColor);
		}
	}
	if (MIColor != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hello, %s"), *ColorMaterialParamName.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My Location is: %s"), *Color.ToString()));
		MIColor->SetVectorParameterValue(ColorMaterialParamName, Color);
	}
}

void ABlock::SetSideAndColor(int32 iSide, FLinearColor Color)
{
	Side = iSide;
	SetColor(Color);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	SetColor(NormalColor);
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

