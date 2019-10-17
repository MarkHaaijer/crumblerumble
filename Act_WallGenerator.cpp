// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_WallGenerator.h"
#include "Engine.h"
#include "Act_Wall.h"
#include "Act_Light.h"

// Sets default values
AAct_WallGenerator::AAct_WallGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

uint32 AAct_WallGenerator::GetLength()
{
	return m_Length;
}

void AAct_WallGenerator::SpawnWall(FVector SpawnLocation, FRotator SpawnRotation)
{
	if(m_WallToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			
			world->SpawnActor<AAct_Wall>(m_WallToSpawn, SpawnLocation, SpawnRotation, spawnParams);
		}
	}
}

void AAct_WallGenerator::SpawnLight(FVector SpawnLocation, FRotator SpawnRotation)
{
	if(m_LightToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			
			world->SpawnActor<AAct_Light>(m_LightToSpawn, SpawnLocation, SpawnRotation, spawnParams);
		}
	}
}

// Called when the game starts or when spawned
void AAct_WallGenerator::BeginPlay()
{
	Super::BeginPlay();

	// Spawn 2 columns of walls
	for(uint32 x = 0; x < m_Length; ++x)
	{
		SpawnWall(FVector(x*280.f, -100.f-75.f,0), FRotator(0,90,0)); // 75 is the offset from the edge of the wall 100 is size of tile
		SpawnWall(FVector(x*280.f, m_Width*100.f+75.f,0), FRotator(0,-90,0)); //280 = wall length, 100 is tile size
		if (x < m_Length*0.125f) // only need half of quarter the amount of lights
		{
			SpawnLight(FVector(200 + x*2240.f, 0.f-75.f,0.f), FRotator(0,90,0)); // 2240 = every 8 walls
			SpawnLight(FVector(70 + x*2240.f, m_Width*100.f-25.f,0.f), FRotator(0,-90,0)); // 2240 = every 8 walls
		}
	}
}

bool AAct_WallGenerator::GetIsActive() const
{
	return m_IsActive;
}

void AAct_WallGenerator::SetActive(bool b)
{
	m_IsActive = b;
}

