// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"




// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));	
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	// VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	// VR_Gun->bCastDynamicShadow = false;
	// VR_Gun->CastShadow = false;
	// VR_Gun->SetupAttachment(R_MotionController);
	// VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	// VR_MuzzleLocation->SetupAttachment(VR_Gun);
	// VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	// VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	// if (bUsingMotionControllers)
	// {
	// VR_Gun->SetHiddenInGame(false, true);
	// Mesh1P->SetHiddenInGame(true, true);
	// }
	// else
	// {
	// VR_Gun->SetHiddenInGame(true, true);
	// Mesh1P->SetHiddenInGame(false, true);
	// }
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
		//	if (bUsingMotionControllers)
		//	{
		//		const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
		//		const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
		//		World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		//	}
			//else
		//	{
			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			//}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{

		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}