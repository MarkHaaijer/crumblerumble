// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Act_WallGenerator.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_WallGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_WallGenerator();

	UPROPERTY(editanywhere)
	TSubclassOf<class AAct_Wall> m_WallToSpawn;
	UPROPERTY(editanywhere)
	TSubclassOf<class AAct_Light> m_LightToSpawn;

	UPROPERTY(editanywhere)
	uint32 m_Length = 40; // Starting length

	UPROPERTY(editanywhere)
	uint32 m_Width = 10; // Starting length

	void SpawnWall(FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnLight(FVector SpawnLocation, FRotator SpawnRotation);

	uint32 GetLength();

	bool GetIsActive() const;

	void SetActive(bool b);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool m_IsActive = false;

};
