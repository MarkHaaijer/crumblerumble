// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_ObstacleGenerator.h"
#include "Components/StaticMeshComponent.h"
#include "Act_BaseObstacle.h"
#include "Engine.h"
#include "interfaces/Interface_DamageAble.h"

// Sets default values
AAct_ObstacleGenerator::AAct_ObstacleGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_DelayTime = FMath::RandRange(m_MinDelay, m_MaxDelay);

	m_pExplosionCollision = CreateDefaultSubobject<USphereComponent>("ExplosionSphere");
	RootComponent = m_pExplosionCollision;
}

// Called when the game starts or when spawned
void AAct_ObstacleGenerator::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAct_PickupGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pPickupGeneratorActor = *ActorItr;
	}
	for (TActorIterator<AAct_TileGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pTileGeneratorActor = *ActorItr;
	}

	m_pExplosionCollision->SetSphereRadius(FMath::RandRange(50, 400));
}

// Called every frame
void AAct_ObstacleGenerator::Tick(float DeltaTime)
{
	if (m_IsActive)
	{
		Super::Tick(DeltaTime);
		m_ElapsedTime += DeltaTime;

		if (m_ElapsedTime >= m_DelayTime)
		{
			SpawnObstacle();
			m_DelayTime = FMath::RandRange(m_MinDelay, m_MaxDelay);
			m_ElapsedTime = 0.f;
		}
	}
}

void AAct_ObstacleGenerator::SpawnObstacle()
{
	float frontX = m_pPickupGeneratorActor->GetFrontRunnerXPos();

	float m_SpawnY = FMath::RandRange(0, m_pTileGeneratorActor->GetWidth() * 100);

	float number = rand() % 101; // Number between 0 and 100

	if (number > m_HoleChancePercent)
	{
		// Spawn obstacle
		auto distance  = FMath::RandRange(m_ObstacleDistance, m_ObstacleDistance*2.f);
		Spawn(FVector(frontX + distance, m_SpawnY, 30));
	}
	else
	{
		// Create hole
		auto radius = FMath::RandRange(m_MinHoleSize, m_MaxHoleSize);
		m_pExplosionCollision->SetSphereRadius(radius);
		auto distance  = FMath::RandRange(m_MinHoleDistance, m_MaxHoleDistance);
		m_pExplosionCollision->SetAllPhysicsPosition(FVector(frontX + (radius*0.5f) + distance, m_SpawnY, 30));

		TArray<AActor*> pActors;
		GetOverlappingActors(pActors);

		for (AActor* actor : pActors)
		{
			IInterface_DamageAble* castedActor = Cast<IInterface_DamageAble>(actor);

			if (castedActor)
				castedActor->Execute_TakeDamage(actor, m_HoleDamage); // Always call execute, never call directly
		}
	}
}

void AAct_ObstacleGenerator::Spawn(FVector SpawnLocation)
{
	if(m_ToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			
			world->SpawnActor<AAct_BaseObstacle>(m_ToSpawn, SpawnLocation, FRotator::ZeroRotator, spawnParams);
		}
	}
}

void AAct_ObstacleGenerator::SetActive(bool b)
{
	m_IsActive = b;
}
