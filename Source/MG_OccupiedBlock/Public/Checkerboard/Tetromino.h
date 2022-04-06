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
	// ƴͼ�����ݵ���
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		TSubclassOf<UTetrominoOrigin> OriginClass;
	// �������
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		TSubclassOf<ABlock> BlockClass;
	// ����Ŀ��
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		float BlockWidthHeight;
	// ����Actor
	UPROPERTY(BlueprintReadWrite, Category = Checkerboard)
		TArray<ABlock*> BlockInstances;

	// ���̿�����
	UPROPERTY(Meta = (ExposeOnSpawn = true), BlueprintReadWrite)
		UCheckerboardController* CheckerboardController;
	// Sets default values for this actor's properties
	ATetromino();

	UFUNCTION(BlueprintCallable)
		void SetDisable(bool value);
	bool GetDisable();

	// ���ɷ���Actor
	UFUNCTION(BlueprintCallable)
		void SpawnBlocks();

	// ��תָ���Ƕ�
	UFUNCTION(BlueprintCallable)
		void RotateTo(float Degrees);

	// ��ת90�ȵı���
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

	// ��ȡƴͼ��ԭ���ݵ�����
	UFUNCTION(BlueprintCallable)
		void GetOriginBlockOccupations(TArray<FVector2D>& Out);

	// ��ȡƴͼ�����ݵ�ָ��
	UTetrominoOrigin* GetTetrominoOrigin();


	// ��ʼ����
	UFUNCTION(BlueprintCallable)
		void StartShake(float Time, UCurveFloat* Curve);

	// ��ƴͼ��ԭʼ���ݷ����仯ʱִ��
	void HandleChangeSide(int32 Side);

protected:
	UPROPERTY(EditAnywhere, Meta = (ExposeOnSpawn = true), BlueprintReadOnly)
		bool Disable = true;

	UPROPERTY()
		UMaterialInterface* DisableMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* DynamicDisableMaterial;

	/* �ӷ���Actor����
	 �������ڲ�Ӱ��ƴͼ��Actor��rotater�������ʵ����ת
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* ContainerSceneComponentPtr;

	// ��ʾ�Ƿ���õ�Widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* DisablePanelComponentPtr;

	// ƴͼ������Դʵ��
	UPROPERTY()
		UTetrominoOrigin* Origin;

	// ��תĿ��
	FRotator RotationTarget;

	// �Ƿ�Ҫ��ת����תĿ��
	bool bIsRotating = false;

	// �ƶ���Ŀ��λ��
	FVector MoveTargetWorldLocation;
	// �Ƿ�Ҫ�ƶ���Ŀ��λ��
	bool bIsMoveing;

	// �������ߣ������򶶶�ʱ�䣬���򶶶��Ƕ�
	UPROPERTY()
		UCurveFloat* ShakeCurve;
	// ��Ҫ������ʱ��
	float LimitedShakingTime = 0;
	// ��ǰ����ʱ��
	float CurrentShakingTime = 0;
	// �Ƿ���Ҫ����
	bool bIsShaking = false;

	virtual void PostInitProperties() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
