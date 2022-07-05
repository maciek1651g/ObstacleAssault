// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += PlatformVelocity * DeltaTime;
	SetActorLocation(CurrentLocation);
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	
	if (DistanceMoved > MaxDistance)
	{
		FVector PlatformDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + PlatformDirection * MaxDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity *= -1;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += DeltaTime * RotationSpeed;
	SetActorRotation(CurrentRotation);
}