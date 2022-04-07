// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkerboard/Block.h"
#include "Checkerboard.generated.h"

class UCheckerboardController;
USTRUCT(BlueprintType)
struct FBlockSide
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Side;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Col;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Row;
};

UCLASS()
class MG_OCCUPIEDBLOCK_API ACheckerboard : public AActor
{
	GENERATED_BODY()

public:
	// ���̸����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Checkerboard)
		TSubclassOf<ABlock> BlockClass;
	// �ߴ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		int32 Size;
	// ��С
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		float WidthHeight;
	// Ĭ�ϵ����̸���Ӫ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		TArray<FBlockSide> DefaultBlocksSide;

	UPROPERTY(BlueprintReadOnly, Category = Checkerboard)
		TArray<ABlock*> BlockInstances;
	// Sets default values for this actor's properties
	ACheckerboard();

	UFUNCTION(BlueprintCallable)
		void SpawnBlocks();

	// �����û���������Ӫ�б�����ʼ����Ӫ
	UFUNCTION(BlueprintCallable)
		void InitBlockSide(TArray<int32> Sides);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetBlockIndexByColRow(FVector2D Location);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FVector GetWorldLocationByColRow(int32 Col, int32 Row);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FVector GetWorldLocationByBlock(ABlock* Block, bool& Success);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		ABlock* GetBlockByLocation(FVector2D Location);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsOutOfBounds(FVector2D Location);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetScoreBySide(int32 Side);

	// ָ��λ���Ƿ���ͬһ��Ӫ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsSameSideByLocation(int32 Side, FVector2D Location);

	UFUNCTION(BlueprintCallable)
		bool SetBlockSide(FVector2D Location, int32 Side);

	UFUNCTION(BlueprintCallable)
		void SetBlocksSide(TArray<FVector2D> BlockLocations, int32 Side);

	void SetCheckerboardController(UCheckerboardController* CheckerboardControllerPtr);

	int32 GetDefaultSideByColRow(int32 Col, int32 Row);

protected:
	UCheckerboardController* CheckerboardController;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
