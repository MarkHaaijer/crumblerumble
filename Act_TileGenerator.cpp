// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_TileGenerator.h"
#include "Act_Tile.h"

// Sets default values
AAct_TileGenerator::AAct_TileGenerator() {}

// Called when the game starts or when spawned
void AAct_TileGenerator::BeginPlay()
{
	Super::BeginPlay();
	// Spawn grid of tiles
	for(uint32 x = 0; x < m_Length; ++x)
		for(uint32 y = 0; y < m_Width; ++y)
			Spawn(FVector(x*100.f, y*100.f,0));
}

void AAct_TileGenerator::Spawn(FVector SpawnLocation)
{
	if(m_ToSpawn)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			
			world->SpawnActor<AAct_Tile>(m_ToSpawn,SpawnLocation,FRotator::ZeroRotator, spawnParams);
		}
	}
}

uint32 AAct_TileGenerator::GetWidthPos()
{
	return m_WidthPos;
}

uint32 AAct_TileGenerator::GetWidth()
{
	return m_Width;
}

uint32 AAct_TileGenerator::GetLength()
{
	return m_Length;
}

void AAct_TileGenerator::AdaptWidthPos()
{
	++m_WidthPos;
	m_WidthPos = m_WidthPos%m_Width;

	if (m_WidthPos%m_Width == 0)
		++m_Length;
}

bool AAct_TileGenerator::GetIsActive() const
{
	return m_IsActive;
}

void AAct_TileGenerator::SetActive(bool b)
{
	m_IsActive = b;
}
