// Fill out your copyright notice in the Description page of Project Settings.

#include "Launcher.h"
#include "Kismet/GameplayStatics.h"

void ALauncher::PullTrigger()
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
            FPointDamageEvent DamageEvent(Damage, OutHit, ShotDirection, nullptr);
            AController *OwnerController = GetOwnerController();
            HittedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
        }
    }
}
