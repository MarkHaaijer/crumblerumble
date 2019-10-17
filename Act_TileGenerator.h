// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Act_TileGenerator.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_TileGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_TileGenerator();

	bool m_IsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UClass *m_ToSpawn;

	UPROPERTY(EditAnywhere)
	uint32 m_Width = 8; // Total width
	
	UPROPERTY(EditAnywhere)
	uint32 m_Length = 20; // Starting length
	UPROPERTY(EditAnywhere)
	uint32 m_WidthPos = 0; // Check at what width position tile has to be spawned
	
	void Spawn(FVector SpawnLocation);

	uint32 GetWidthPos();
	uint32 GetWidth();
	uint32 GetLength();

	void AdaptWidthPos();

	bool GetIsActive() const;
	void SetActive(bool b);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
