// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_PickupGenerator.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/act_PickupSpawner.h"
#include "Engine.h"

// Sets default values
AAct_PickupGenerator::AAct_PickupGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAct_PickupGenerator::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(),m_SpawnPoints);
	for(int i = 0; i < m_SpawnPoints.Num(); ++i)
	{
		m_Characters.Add(dynamic_cast<Achar_BaseCharacter*>(UGameplayStatics::GetPlayerCharacter(this,i)));
	}

	for (TActorIterator<AAct_TileGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pTileGeneratorActor = *ActorItr;
	}
}

// Called every frame
void AAct_PickupGenerator::Tick(float DeltaTime)
{
	if (m_IsActive)
	{
		Super::Tick(DeltaTime);
		m_Timer += DeltaTime;

		//default every 2 seconds with 4 players, 
		if (m_Timer >= int(4/m_SpawnPoints.Num()*m_DelaySeconds))
		{
			SpawnPickup();
			m_Timer = 0;
		} 
	}
}

void AAct_PickupGenerator::SpawnPickup()
{
	float m_SpawnXTotal = 0.f;
	UINT playerAmount = 0;
	for(int i = 0; i < m_SpawnPoints.Num(); ++i)
	{
		if (!m_Characters[i]->GetIsDead())
		{
			m_SpawnXTotal += m_Characters[i]->GetActorLocation().X;
			++playerAmount;
		}
	}

	float m_AverageX = m_SpawnXTotal / playerAmount;

	float m_SpawnX = FMath::RandRange(m_AverageX - m_SpawnDistBehindAvg*100, m_AverageX + m_SpawnDistAheadAvg*100);
	float m_SpawnY = FMath::RandRange(-50, m_pTileGeneratorActor->GetWidth() * 100);

	Spawn(FVector(m_SpawnX, m_SpawnY, 55));
}

void AAct_PickupGenerator::Spawn(FVector SpawnLocation)
{
	if(m_ToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			
			world->SpawnActor<AAct_PickupSpawner>(m_ToSpawn, SpawnLocation, FRotator::ZeroRotator, spawnParams);
		}
	}
}

float AAct_PickupGenerator::GetFrontRunnerXPos()
{
	float frontX = 0.f;
	for (auto player : m_Characters)
	{
		float playerX = player->GetTransform().GetLocation().X;
		if (playerX > frontX)
			frontX = playerX;
	}

	return frontX;
}

void AAct_PickupGenerator::SetActive(bool b)
{
	m_IsActive = b;
}
