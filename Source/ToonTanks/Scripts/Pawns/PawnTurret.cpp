// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();

	
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
		return;

	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	RotateTurret(PlayerLocation);
	
}

void APawnTurret::CheckFireCondition()
{
	if(!PlayerPawn)
		return;

	if(ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
		UE_LOG(LogTemp, Warning, TEXT("Enemy Turret Fire!!!"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Fire Condition Checked!!!"));
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if(!PlayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
