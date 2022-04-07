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

	// ��ת4�Σ���ÿ����ת���ƴͼ��������ÿ���������У���Ƿ�ŵ���
	for (int32 i = 0; i < 4; i++)
	{
		float Degrees = i * 90;
		OriginCopy->RotateTo(Degrees);
		TArray<FVector2D> TetrominoBlockRelativeLocation = OriginCopy->GetBlockOccupationArray();

		// ��⵱ǰ���̿�Ϊ���ĵ��Ƿ���Է���4���Ƕ���ƴͼ��
		for (ABlock* BoardBlockInstance : Checkerboard->BlockInstances)
		{
			// ��ǰ�������̿��λ��
			FVector2D BoardBlockLocation = BoardBlockInstance->GetRowCol();

			// �Ƿ���Ϲ��� ����Խ�磬ƴͼ��ĸ��������Ӧ���������鶼ҪΪ������
			bool IsMatchRules = true;
			// �Ƿ����ƴͼ�����ڵ�ͬ��Ӫ��������
			bool HasNearlySameSideBlock = false;

			// ����ǰ�Ƕ���ƴͼ�����е�����
			for (int32 ITetrominoBlock = 0; ITetrominoBlock < BlockMount; ITetrominoBlock++)
			{
				// ����ƴͼ��֮�����̵����λ��
				FVector2D TetrominoBlockBoardLocation = TetrominoBlockRelativeLocation[ITetrominoBlock] + BoardBlockLocation;

				// ���������Ƿ����� || �ж��Ƿ�Խ��
				if (
					!Checkerboard->IsSameSideByLocation(-1, TetrominoBlockBoardLocation) ||
					Checkerboard->IsOutOfBounds(TetrominoBlockBoardLocation)
					)
				{
					IsMatchRules = false;
					break;
				}
				// ����Ѿ��������ڵ�ͬ��Ӫ�������������
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
			// �����ǰ��������Ϊ���ĵ���Է��µ�ǰ�Ƕȵ�ƴͼ�����������߼�
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

	// �Ƿ���Ϲ��� ����Խ�磬ƴͼ��ĸ��������Ӧ���������鶼ҪΪ������
	bool IsMatchRules = true;
	// �Ƿ����ƴͼ�����ڵ�ͬ��Ӫ��������
	bool HasNearlySameSideBlock = false;

	// ����ƴͼ�����е�����
	for (int32 ITetrominoBlock = 0; ITetrominoBlock < BlockMount; ITetrominoBlock++)
	{
		// ����ƴͼ��֮�����̵����λ��
		FVector2D TetrominoBlockBoardLocation = TetrominoBlockRelativeLocation[ITetrominoBlock] + BoardLocation;

		// ���������Ƿ����� || �ж��Ƿ�Խ��
		if (
			!Checkerboard->IsSameSideByLocation(-1, TetrominoBlockBoardLocation) ||
			Checkerboard->IsOutOfBounds(TetrominoBlockBoardLocation)
			)
		{
			IsMatchRules = false;
			break;
		}
		// ����Ѿ��������ڵ�ͬ��Ӫ�������������
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

	// �����ǰ��������Ϊ���ĵ���Է��µ�ǰ�Ƕȵ�ƴͼ�����������߼�
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
