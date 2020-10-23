// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    //////////////// Behavior could be implemented in C++, but we checked out the Behavior Trees and Black Boards for this.
    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // if (LineOfSightTo(PlayerPawn))
    // {
    //     MoveToActor(PlayerPawn, AcceptanceRadius);
    //     SetFocus(PlayerPawn);
    // }
    // else
    // {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter *ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ControlledCharacter)
    {
        return ControlledCharacter->IsDead();
    }
    else
    {
        return true;
    }
}
