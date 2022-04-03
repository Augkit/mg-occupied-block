// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkerboard/TetrominoOrigin.h"

void UTetrominoOrigin::PostInitProperties()
{
	UObject::PostInitProperties();

	// 根据中心位置进行偏移
	if (!OffsetCenter.IsNearlyZero())
	{
		for (int32 i = 0; i < BlockOccupationArray.Num(); i++)
		{
			FVector2D* BlockOccupation = &BlockOccupationArray[i];
			*BlockOccupation -= OffsetCenter;
		}
	}
	// 将格子位置做个备份
	NormalBlockOccupationArray = BlockOccupationArray;

	// 初始化旋转
	if (!FMath::IsNearlyZero(RotateDegree))
	{
		RotateTo(RotateDegree);
	}
}

int32 UTetrominoOrigin::GetSide()
{
	return Side;
}

void UTetrominoOrigin::SetSide(int32 NewSide)
{
	Side = NewSide;
	OnChangeSide.Broadcast(Side);
}

TArray<FVector2D> UTetrominoOrigin::GetBlockOccupationArray()
{
	return BlockOccupationArray;
}

void UTetrominoOrigin::GetBlockOccupationArrayRef(TArray<FVector2D>& Out)
{
	Out = BlockOccupationArray;
}

int32 UTetrominoOrigin::BlockNum()
{
	return BlockOccupationArray.Num();
}

FVector2D UTetrominoOrigin::GetOffsetCenter()
{
	return OffsetCenter;
}

float UTetrominoOrigin::GetRotateDegree()
{
	return RotateDegree;
}

void UTetrominoOrigin::RotateTo(float Degrees)
{
	float OffsetDegrees = Degrees - RotateDegree;
	if (FMath::IsNearlyZero(OffsetDegrees)) return;
	BlockOccupationArray = NormalBlockOccupationArray;
	FMath::DivideAndRoundNearest<float>(Degrees, 360.f);
	int32 FloorDegrees = FMath::FloorToInt(Degrees);
	RotateDegree = Degrees - FloorDegrees + FloorDegrees % 360;

	for (int32 i = 0; i < BlockOccupationArray.Num(); i++)
	{
		BlockOccupationArray[i] = BlockOccupationArray[i].GetRotated(RotateDegree);
	}

}
