// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_Light.h"
#include "ConstructorHelpers.h"
#include "Engine.h"

// Sets default values
AAct_Light::AAct_Light()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAct_Light::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAct_PickupGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pPickupGeneratorActor = *ActorItr;
	}
	
	for (TActorIterator<AAct_WallGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pWallGeneratorActor = *ActorItr;
	}
	m_TotalLightLength = m_pWallGeneratorActor->GetLength();
}

// Called every frame
void AAct_Light::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pWallGeneratorActor->GetIsActive())
	{
		float frontX = m_pPickupGeneratorActor->GetFrontRunnerXPos();
		float curX = GetActorLocation().X;
		if (frontX > curX + 2000) // Teleport wall to front if too far away from frontrunner (20 tiles in this case)
			SetActorLocation(FVector(GetActorLocation().X + m_TotalLightLength * m_LightLength,GetActorLocation().Y,0));
	}
}