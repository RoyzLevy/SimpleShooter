// Fill out your copyright notice in the Description page of Project Settings.

#include "Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkinnedMeshComponent.h"
#include "GameFramework/Character.h"

void ARifle::PullTrigger()
{
    Super::PullTrigger();

    if (CurrentAmmo <= 0)
    {
        return;
    }
    FHitResult OutHit;
    FVector ShotDirection;
    bool DidHit = GunTrace(OutHit, ShotDirection);
    if (DidHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Shot hit!"));
        //DrawDebugPoint(GetWorld(), OutHit.Location, 20, FColor::Red, true);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.Location, ShotDirection.Rotation());
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, OutHit.Location, ShotDirection.Rotation());

        // Send damage
        AActor *HittedActor = OutHit.GetActor();
        if (HittedActor)
        {
            float ModifiedDamage = Damage;
            ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
            UE_LOG(LogTemp, Warning, TEXT("Bone is %s"), *OutHit.BoneName.ToString());
            if (OwnerCharacter && OwnerCharacter->GetMesh()->BoneIsChildOf(OutHit.BoneName, TEXT("head")))
            {
                ModifiedDamage = ModifiedDamage * 10;
            }
            FPointDamageEvent DamageEvent(ModifiedDamage, OutHit, ShotDirection, nullptr);
            AController *OwnerController = GetOwnerController();
            HittedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
        }
    }
}
