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

	// ��תָ���Ƕ�
	UFUNCTION(BlueprintCallable)
		void RotateTo(float Degrees);

	UFUNCTION(BlueprintCallable)
		void Rotate90Degrees(float Scale = 1);

	// �ƶ���ָ�����������λ��
	UFUNCTION(BlueprintCallable)
		void MoveToWorldLocation(FVector TargetLocation);

	// ��ȡƴͼ����Ӫ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetSide();
	// ����ƴͼ����Ӫ
	UFUNCTION(BlueprintCallable)
		void SetSide(int32 Side);

	UFUNCTION(BlueprintCallable)
		void GetOriginBlockOccupations(TArray<FVector2D>& Out);


	UTetrominoOrigin* GetTetrominoOrigin();

	void HandleChangeSide(int32 Side);

protected:
	// ƴͼ������Դʵ��
	UTetrominoOrigin* Origin;

	USceneComponent* ContainerSceneComponentPtr;

	// ��תĿ��
	FRotator RotationTarget;

	// �Ƿ�Ҫ��ת����תĿ��
	bool bIsRotating = false;

	// �ƶ���Ŀ��λ��
	FVector MoveTargetWorldLocation;
	// �Ƿ�Ҫ�ƶ���Ŀ��λ��
	bool bIsMoveing;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
