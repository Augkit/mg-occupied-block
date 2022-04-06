// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkerboard/TetrominoOrigin.h"
#include "Checkerboard/Block.h"
#include "Components/WidgetComponent.h"
#include "Tetromino.generated.h"

class UCheckerboardController;
UCLASS()
class MG_OCCUPIEDBLOCK_API ATetromino : public AActor
{
	GENERATED_BODY()

public:
	// 拼图块数据的类
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		TSubclassOf<UTetrominoOrigin> OriginClass;
	// 方块的类
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		TSubclassOf<ABlock> BlockClass;
	// 方块的宽高
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		float BlockWidthHeight;
	// 方块Actor
	UPROPERTY(BlueprintReadWrite, Category = Checkerboard)
		TArray<ABlock*> BlockInstances;

	// 棋盘控制器
	UPROPERTY(Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		UCheckerboardController* CheckerboardController;
	// Sets default values for this actor's properties
	ATetromino();

	UFUNCTION(BlueprintCallable)
		void SetDisable(bool value);
	bool GetDisable();

	// 生成方块Actor
	UFUNCTION(BlueprintCallable)
		void SpawnBlocks();

	// 旋转指定角度
	UFUNCTION(BlueprintCallable)
		void RotateTo(float Degrees);

	// 旋转90度的倍数
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

	// 获取拼图块原数据的引用
	UFUNCTION(BlueprintCallable)
		void GetOriginBlockOccupations(TArray<FVector2D>& Out);

	// 获取拼图块数据的指针
	UTetrominoOrigin* GetTetrominoOrigin();


	// 开始抖动
	UFUNCTION(BlueprintCallable)
		void StartShake(float Time, UCurveFloat* Curve);

	// 当拼图块原始数据发生变化时执行
	void HandleChangeSide(int32 Side);

protected:
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadOnly)
		bool Disable = true;

	UPROPERTY()
		UMaterialInterface* DisableMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* DynamicDisableMaterial;

	/* 子方块Actor容器
	 方便用于不影响拼图块Actor的rotater的情况下实现旋转
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* ContainerSceneComponentPtr;

	// 显示是否可用的Widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* DisablePanelComponentPtr;

	// 拼图块数据源实例
	UPROPERTY()
		UTetrominoOrigin* Origin;

	// 旋转目标
	FRotator RotationTarget;

	// 是否要旋转到旋转目标
	bool bIsRotating = false;

	// 移动的目标位置
	FVector MoveTargetWorldLocation;
	// 是否要移动到目标位置
	bool bIsMoveing;

	// 抖动曲线，横纵向抖动时间，纵向抖动角度
	UPROPERTY()
		UCurveFloat* ShakeCurve;
	// 需要抖动的时间
	float LimitedShakingTime = 0;
	// 当前抖动时间
	float CurrentShakingTime = 0;
	// 是否需要抖动
	bool bIsShaking = false;

	virtual void PostInitProperties() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
