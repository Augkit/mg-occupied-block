// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TetrominoOrigin.generated.h"

/**
 * ƴͼ��Ԫ����
 *
 */

DECLARE_MULTICAST_DELEGATE_OneParam(DelegateOnChangeSide, int32)

UCLASS(Blueprintable, BlueprintType)
class MG_OCCUPIEDBLOCK_API UTetrominoOrigin : public UObject
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;

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
	DelegateOnChangeSide OnChangeSide;
protected:
	// ԭʼ��ƴͼ��λ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector2D> NormalBlockOccupationArray;

	// ��ǰ�������ӵ�λ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector2D> BlockOccupationArray;

	// ƴͼ�������ƫ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D OffsetCenter;

	// ��ǰƴͼ����ת�ĽǶ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RotateDegree = 0;

	TArray<FVector2D> OriginBlockOccupationArray;

	int32 Side = -1;
};
