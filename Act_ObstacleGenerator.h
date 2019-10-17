// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generators/Act_PickupGenerator.h"
#include "Act_ObstacleGenerator.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_ObstacleGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_ObstacleGenerator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnObstacle();
	void Spawn(FVector SpawnLocation);

	void SetActive(bool b);

	UPROPERTY(editanywhere)
	float m_MinDelay = 1.f;

	UPROPERTY(editanywhere)
	float m_MaxDelay = 2.f;

	UPROPERTY(editanywhere)
	float m_ObstacleDistance = 3000.f;

	UPROPERTY(editanywhere)
	float m_MinHoleDistance = 900.f;

	UPROPERTY(editanywhere)
	float m_MaxHoleDistance = 1200.f;

	UPROPERTY(editanywhere)
	float m_HoleDamage = 40.f;

	UPROPERTY(editanywhere)
	float m_MinHoleSize = 50.f;
	
	UPROPERTY(editanywhere)
	float m_MaxHoleSize = 400.f;

	UPROPERTY(editanywhere)
	float m_HoleChancePercent = 50.f;

	UPROPERTY(editanywhere)
	TSubclassOf<class AAct_BaseObstacle> m_ToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	AAct_PickupGenerator* m_pPickupGeneratorActor;
	AAct_TileGenerator* m_pTileGeneratorActor;
	bool m_IsActive = false;
	float m_ElapsedTime, m_DelayTime;

	UPROPERTY()
	class USphereComponent* m_pExplosionCollision;
};
