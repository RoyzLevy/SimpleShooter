// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUDScreenWidgetPtr = CreateWidget(this, HUDClass);
    if (HUDScreenWidgetPtr)
    {
        HUDScreenWidgetPtr->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUDScreenWidgetPtr->RemoveFromViewport();
    if (bIsWinner)
    {
        UE_LOG(LogTemp, Warning, TEXT("You Won!"));
        // win screen
        UUserWidget *WinScreenWidget = CreateWidget(this, WinScreenClass);
        if (WinScreenWidget)
        {
            WinScreenWidget->AddToViewport();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You Lost..."));
        // lose screen
        UUserWidget *LoseScreenWidget = CreateWidget(this, LoseScreenClass);
        if (LoseScreenWidget)
        {
            LoseScreenWidget->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
