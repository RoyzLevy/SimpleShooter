// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *Mesh;

public:
	// Sets default values for this actor's properties
	AGun();

	virtual void PullTrigger();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Ammo")
	int32 GetMaxAmmo() const;
	UFUNCTION(BlueprintPure, Category = "Ammo")
	int32 GetCurrentAmmo() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool GunTrace(FHitResult &OutHit, FVector ShotDirection);

	AController *GetOwnerController() const;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo = 100;
	UPROPERTY(VisibleAnywhere, Category = "Ammo")
	int32 CurrentAmmo = 30;

	/////// Particles and Sounds

	// Particles
	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;
	UPROPERTY(EditAnywhere)
	UParticleSystem *ImpactEffect;

	// Sounds
	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSound;
	UPROPERTY(EditAnywhere)
	USoundBase *NoAmmoLeftSound;
};
