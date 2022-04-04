// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModalWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseModalDelegate);

//¶¯Ì¬
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(OnCloseModalDelegate, bool, Value);

/**
 *
 */
UCLASS()
class MG_OCCUPIEDBLOCK_API UModalWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = Event)
		FOnCloseModalDelegate OnCloseModal;

	UFUNCTION(BlueprintCallable)
	void Close();

};
