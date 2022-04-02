// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tetromino.h"
#include "Checkerboard.h"
#include "CheckerboardController.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class MG_OCCUPIEDBLOCK_API UCheckerboardController : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, FLinearColor> SideColorMapping;
	UFUNCTION(BlueprintCallable)
		void MoveTetrominoToBoardLocation(ATetromino* TargetTetromino, FVector2D BoardLocation);
	UFUNCTION(BlueprintCallable)
		void MoveTetrominoOnBoardByStep(FVector2D Step);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FLinearColor GetColorBySide(int32 Side);

	UFUNCTION(BlueprintCallable)
		void SetCheckerboard(ACheckerboard* CheckerboardPtr);

	UFUNCTION(BlueprintCallable)
		void SetTetrominoOnBoard(ATetromino* TetrominoPtr);

	// ���Ŀ��ƴͼ�����������Ƿ��п�λ
	UFUNCTION(BlueprintCallable)
		bool CheckTetrominoVacancies(ATetromino* TetrominoPtr, FVector2D& ValidLocation, float& ValidDegrees);

	// ƴͼ�����������Ƿ��п�λ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckTetrominoOnBoardVacancie();

	// ���Ŀ��ƴͼ���ڸ���λ�����Ƿ��п�λ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckTetrominoVacancieAtLocation(ATetromino* TetrominoPtr, FVector2D BoardLocation);
	bool CheckTetrominoVacancieAtLocation(UTetrominoOrigin* TetrominoOrigin, FVector2D BoardLocation);

	UFUNCTION(BlueprintCallable)
		void PutTetrominoToBoard(bool& Success);

protected:
	UPROPERTY(BlueprintReadOnly)
		ACheckerboard* Checkerboard;
	UPROPERTY(BlueprintReadOnly)
		ATetromino* TetrominoOnBoard;
	UPROPERTY(BlueprintReadOnly)
		FVector2D TetrominoBoardLocation;
};
