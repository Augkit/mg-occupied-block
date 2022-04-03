// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkerboard/TetrominoOrigin.h"
#include "Checkerboard/Block.h"
#include "Tetromino.generated.h"

class UCheckerboardController;
UCLASS()
class MG_OCCUPIEDBLOCK_API ATetromino : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		TSubclassOf<UTetrominoOrigin> OriginClass;
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		TSubclassOf<ABlock> BlockClass;
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		float BlockWidthHeight;
	UPROPERTY(Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		UCheckerboardController* CheckerboardController;

	UPROPERTY(BlueprintReadWrite, Category = Checkerboard)
		TArray<ABlock*> BlockInstances;
	// Sets default values for this actor's properties
	ATetromino();
	ATetromino(TSubclassOf<UTetrominoOrigin> OC);
	ATetromino(TSubclassOf<ABlock> BC);

	UFUNCTION(BlueprintCallable)
		void SpawnBlocks();

	// 旋转指定角度
	UFUNCTION(BlueprintCallable)
		void RotateTo(float Degrees);

	UFUNCTION(BlueprintCallable)
		void Rotate90Degrees(float Scale = 1);

	// 移动到指定世界坐标的位置
	UFUNCTION(BlueprintCallable)
		void MoveToWorldLocation(FVector TargetLocation);

	// 获取拼图快阵营
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetSide();
	// 设置拼图块阵营
	UFUNCTION(BlueprintCallable)
		void SetSide(int32 Side);

	UFUNCTION(BlueprintCallable)
		void GetOriginBlockOccupations(TArray<FVector2D>& Out);


	UTetrominoOrigin* GetTetrominoOrigin();

	void HandleChangeSide(int32 Side);

protected:
	// 拼图块数据源实例
	UTetrominoOrigin* Origin;

	USceneComponent* ContainerSceneComponentPtr;

	// 旋转目标
	FRotator RotationTarget;

	// 是否要旋转到旋转目标
	bool bIsRotating = false;

	// 移动的目标位置
	FVector MoveTargetWorldLocation;
	// 是否要移动到目标位置
	bool bIsMoveing;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
