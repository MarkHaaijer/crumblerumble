// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generators/Act_PickupGenerator.h"
#include "Generators/Act_WallGenerator.h"
#include "Act_Wall.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_Wall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_Wall();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AAct_PickupGenerator* m_pPickupGeneratorActor;
	AAct_WallGenerator* m_pWallGeneratorActor;
	UStaticMeshComponent* m_pMesh;
	uint32 m_WallLength = 280, m_WallWidth = 580, m_TotalWallLength = 0;
};
