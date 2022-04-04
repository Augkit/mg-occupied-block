// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ModalWidget.h"

void UModalWidget::Close()
{
	RemoveFromParent();
	OnCloseModal.Broadcast();
}
