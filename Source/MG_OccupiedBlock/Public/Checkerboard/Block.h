// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS(BlueprintType)
class MG_OCCUPIEDBLOCK_API ABlock : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* RootStaticMesh;
	// 可修改颜色材质的Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ColorMaterialIndex = 0;
	// 可修改颜色材质的颜色参数名
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ColorMaterialParamName = FName(TEXT("BaseColor"));
	UPROPERTY(BlueprintReadOnly)
		UMaterialInstanceDynamic* MIColor;

	// 区块中立时的颜色
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor NormalColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadOnly)
		int32 IndexRow = 0;

	UPROPERTY(BlueprintReadOnly)
		int32 IndexCol = 0;

	// 此区块的阵营 -1 为中立
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Side = -1;


	// 区块属于某一阵营的颜色
	UPROPERTY(BlueprintReadWrite)
		FLinearColor SideColor;

	// Sets default values for this actor's properties
	ABlock();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FVector2D GetRowCol();

	// 设置区块颜色
	UFUNCTION(BlueprintCallable)
		void SetColor(FLinearColor Color);

	UFUNCTION(BlueprintCallable)
		void SetSideAndColor(int32 iSide, FLinearColor Color);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
