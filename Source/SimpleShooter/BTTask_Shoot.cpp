// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController *AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter *ShooterCharacter = Cast<AShooterCharacter>(AIController->GetPawn());
    if (!ShooterCharacter)
    {
        return EBTNodeResult::Failed;
    }

    ShooterCharacter->Shoot();

    return EBTNodeResult::Succeeded;
}
