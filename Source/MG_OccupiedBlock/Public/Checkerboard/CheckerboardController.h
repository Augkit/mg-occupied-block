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

	// 检测目标拼图块在棋盘上是否有空位
	UFUNCTION(BlueprintCallable)
		bool CheckTetrominoVacancies(ATetromino* TetrominoPtr, FVector2D& ValidLocation, float& ValidDegrees);

	// 拼图块在棋盘上是否有空位
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckTetrominoOnBoardVacancie();

	// 检测目标拼图块在给定位置上是否有空位
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
