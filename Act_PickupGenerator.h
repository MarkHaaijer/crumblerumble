// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Act_TileGenerator.h"
#include "characters/char_BaseCharacter.h"
#include "Act_PickupGenerator.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_PickupGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_PickupGenerator();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnPickup();
	void Spawn(FVector SpawnLocation);
	float GetFrontRunnerXPos();

	void SetActive(bool b);


	UPROPERTY(editanywhere)
	TSubclassOf<class AAct_PickupSpawner> m_ToSpawn;

	UPROPERTY(editanywhere)
	float m_SpawnDistBehindAvg = 5;

	UPROPERTY(editanywhere)
	float m_SpawnDistAheadAvg = 5;

	UPROPERTY(editanywhere)
	float m_DelaySeconds = 2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool m_IsActive = false;
	AAct_TileGenerator* m_pTileGeneratorActor;
	TArray<AActor*> m_SpawnPoints;
	TArray<Achar_BaseCharacter*> m_Characters;
	float m_Timer = 0.f;
};