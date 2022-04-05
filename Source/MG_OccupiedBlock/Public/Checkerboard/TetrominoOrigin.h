// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrominoOrigin.generated.h"

/**
 * ƴͼ��Ԫ����
 *
 */

DECLARE_MULTICAST_DELEGATE_OneParam(OnChangeSideDelegate, int32)

UCLASS(Blueprintable, BlueprintType)
class MG_OCCUPIEDBLOCK_API UTetrominoOrigin : public UObject
{
	GENERATED_BODY()

public:
	// ����λ�õ�ƫ��
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

	// ��Ӫ���ݷ����仯ʱ�Ĺ���
	OnChangeSideDelegate OnChangeSide;
protected:
	// ԭʼ��ƴͼ��λ�ã���������
	TArray<FVector2D> NormalBlockOccupationArray;
	// ƴͼ����ռ��λ��
	TArray<FVector2D> OriginBlockOccupationArray;

	// ��ǰ�������ӵ�λ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector2D> BlockOccupationArray;

	// ƴͼ�������ƫ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D OffsetCenter;

	// ��ǰƴͼ����ת�ĽǶ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RotateDegree = 0;

	// ��Ӫ
	int32 Side = -1;

	virtual void PostInitProperties() override;

};
