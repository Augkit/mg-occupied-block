// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrominoOrigin.generated.h"

/**
 * 拼图块元数据
 *
 */

DECLARE_MULTICAST_DELEGATE_OneParam(OnChangeSideDelegate, int32)

UCLASS(Blueprintable, BlueprintType)
class MG_OCCUPIEDBLOCK_API UTetrominoOrigin : public UObject
{
	GENERATED_BODY()

public:
	// 世界位置的偏移
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D OffsetCenterWorld;

	UFUNCTION(BlueprintCallable)
		void SetSide(int32 NewSide);
	UFUNCTION(BlueprintCallable)
		int32 GetSide();

	UFUNCTION(BlueprintCallable)
		TArray<FVector2D> GetBlockOccupationArray();

	UFUNCTION(BlueprintCallable)
		void GetBlockOccupationArrayRef(TArray<FVector2D>& Out);

	UFUNCTION(BlueprintCallable)
		int32 BlockNum();

	UFUNCTION(BlueprintCallable)
		FVector2D GetOffsetCenter();

	UFUNCTION(BlueprintCallable)
		float GetRotateDegree();

	UFUNCTION(BlueprintCallable)
		void RotateTo(float Degrees);

	// 阵营数据发生变化时的钩子
	OnChangeSideDelegate OnChangeSide;
protected:
	// 原始的拼图块位置，做备份用
	TArray<FVector2D> NormalBlockOccupationArray;
	// 拼图块所占的位置
	TArray<FVector2D> OriginBlockOccupationArray;

	// 当前各个格子的位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector2D> BlockOccupationArray;

	// 拼图块的中心偏移
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D OffsetCenter;

	// 当前拼图块旋转的角度
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RotateDegree = 0;

	// 阵营
	int32 Side = -1;

	virtual void PostInitProperties() override;

};
