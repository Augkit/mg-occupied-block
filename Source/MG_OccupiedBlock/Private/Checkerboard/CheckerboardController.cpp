// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkerboard/CheckerboardController.h"

FVector2D FourWay[4] = { FVector2D(1,0), FVector2D(-1,0),FVector2D(0,1),FVector2D(0,-1) };

void UCheckerboardController::MoveTetrominoToBoardLocation(ATetromino* TargetTetromino, FVector2D BoardLocation)
{
	FVector WorldLocation = Checkerboard->GetWorldLocationByColRow(BoardLocation.X, BoardLocation.Y);
	TetrominoBoardLocation = FVector2D(FMath::RoundToInt(BoardLocation.X), FMath::RoundToInt(BoardLocation.Y));
	TargetTetromino->MoveToWorldLocation(WorldLocation);
}

void UCheckerboardController::MoveTetrominoOnBoardByStep(FVector2D Step)
{
	if (IsValid(TetrominoOnBoard))
	{
		MoveTetrominoToBoardLocation(TetrominoOnBoard, TetrominoBoardLocation + Step);
	}
}

FLinearColor UCheckerboardController::GetColorBySide(int32 Side)
{
	FLinearColor* ColorPtr = SideColorMapping.Find(Side);
	if (ColorPtr != nullptr)
	{
		return *ColorPtr;
	}
	return 	FLinearColor();
}

void UCheckerboardController::SetCheckerboard(ACheckerboard* CheckerboardPtr)
{
	Checkerboard = CheckerboardPtr;
	Checkerboard->SetCheckerboardController(this);
}

void UCheckerboardController::SetTetrominoOnBoard(ATetromino* TetrominoPtr)
{
	TetrominoOnBoard = TetrominoPtr;
}

bool UCheckerboardController::CheckTetrominoVacancies(ATetromino* TetrominoPtr, FVector2D& ValidLocation, float& ValidDegrees)
{
	UTetrominoOrigin* OriginCopy = DuplicateObject<UTetrominoOrigin>(TetrominoPtr->GetTetrominoOrigin(), this);

	int32 BlockMount = OriginCopy->BlockNum();
	int32 TetrominoSide = TetrominoPtr->GetSide();

	// 旋转4次，对每次旋转后的拼图块与棋盘每个网格进行校验是否放的下
	for (int32 i = 0; i < 4; i++)
	{
		float Degrees = i * 90;
		OriginCopy->RotateTo(Degrees);
		TArray<FVector2D> TetrominoBlockRelativeLocation = OriginCopy->GetBlockOccupationArray();

		// 检测当前棋盘块为中心点是否可以放下4个角度下拼图块
		for (ABlock* BoardBlockInstance : Checkerboard->BlockInstances)
		{
			// 当前检测的棋盘块的位置
			FVector2D BoardBlockLocation = BoardBlockInstance->GetRowCol();

			// 是否符合规则 （不越界，拼图块的各个区块对应的棋盘区块都要为中立）
			bool IsMatchRules = true;
			// 是否存在拼图块相邻的同阵营棋盘区块
			bool HasNearlySameSideBlock = false;

			// 遍历前角度下拼图块所有的区块
			for (int32 ITetrominoBlock = 0; ITetrominoBlock < BlockMount; ITetrominoBlock++)
			{
				// 计算拼图块之于棋盘的相对位置
				FVector2D TetrominoBlockBoardLocation = TetrominoBlockRelativeLocation[ITetrominoBlock] + BoardBlockLocation;

				// 棋盘区块是否中立 || 判断是否越界
				if (
					!Checkerboard->IsSameSideByLocation(-1, TetrominoBlockBoardLocation) ||
					Checkerboard->IsOutOfBounds(TetrominoBlockBoardLocation)
					)
				{
					IsMatchRules = false;
					break;
				}
				// 如果已经存在相邻的同阵营区块则跳过检测
				if (HasNearlySameSideBlock) continue;
				for (FVector2D Way : FourWay)
				{
					if (Checkerboard->IsSameSideByLocation(TetrominoSide, Way + TetrominoBlockBoardLocation))
					{
						HasNearlySameSideBlock = true;
						break;
					}
				}
			}
			// 如果当前棋盘区块为中心点可以放下当前角度的拼图块则结束检测逻辑
			if (IsMatchRules && HasNearlySameSideBlock)
			{
				ValidLocation = BoardBlockLocation;
				ValidDegrees = Degrees;
				return true;
			}

		}
	}
	return false;
}

bool UCheckerboardController::CheckTetrominoOnBoardVacancie()
{
	return CheckTetrominoVacancieAtLocation(TetrominoOnBoard, TetrominoBoardLocation);
}

bool UCheckerboardController::CheckTetrominoVacancieAtLocation(ATetromino* TetrominoPtr, FVector2D BoardLocation)
{
	return CheckTetrominoVacancieAtLocation(TetrominoPtr->GetTetrominoOrigin(), BoardLocation);
}

bool UCheckerboardController::CheckTetrominoVacancieAtLocation(UTetrominoOrigin* TetrominoOrigin, FVector2D BoardLocation)
{
	int32 TetrominoSide = TetrominoOrigin->GetSide();
	int32 BlockMount = TetrominoOrigin->BlockNum();

	TArray<FVector2D> TetrominoBlockRelativeLocation = TetrominoOrigin->GetBlockOccupationArray();
	//TetrominoOrigin->GetBlockOccupationArrayRef(TetrominoBlockRelativeLocation);

	// 是否符合规则 （不越界，拼图块的各个区块对应的棋盘区块都要为中立）
	bool IsMatchRules = true;
	// 是否存在拼图块相邻的同阵营棋盘区块
	bool HasNearlySameSideBlock = false;

	// 遍历拼图块所有的区块
	for (int32 ITetrominoBlock = 0; ITetrominoBlock < BlockMount; ITetrominoBlock++)
	{
		// 计算拼图块之于棋盘的相对位置
		FVector2D TetrominoBlockBoardLocation = TetrominoBlockRelativeLocation[ITetrominoBlock] + BoardLocation;

		// 棋盘区块是否中立 || 判断是否越界
		if (
			!Checkerboard->IsSameSideByLocation(-1, TetrominoBlockBoardLocation) ||
			Checkerboard->IsOutOfBounds(TetrominoBlockBoardLocation)
			)
		{
			IsMatchRules = false;
			break;
		}
		// 如果已经存在相邻的同阵营区块则跳过检测
		if (HasNearlySameSideBlock) continue;
		for (FVector2D Way : FourWay)
		{
			if (Checkerboard->IsSameSideByLocation(TetrominoSide, Way + TetrominoBlockBoardLocation))
			{
				HasNearlySameSideBlock = true;
				break;
			}
		}
	}

	// 如果当前棋盘区块为中心点可以放下当前角度的拼图块则结束检测逻辑
	return IsMatchRules && HasNearlySameSideBlock;
}

void UCheckerboardController::PutTetrominoToBoard(bool& Success)
{
	Success = CheckTetrominoOnBoardVacancie();
	if (!Success) return;
	TArray<FVector2D> TetronminoBlocks;
	TetrominoOnBoard->GetOriginBlockOccupations(TetronminoBlocks);
	for (int32 i = 0; i < TetronminoBlocks.Num(); i++)
	{
		TetronminoBlocks[i] += TetrominoBoardLocation;
	}
	Checkerboard->SetBlocksSide(TetronminoBlocks, TetrominoOnBoard->GetSide());
}
