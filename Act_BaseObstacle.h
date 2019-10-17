// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Act_BaseObstacle.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_BaseObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_BaseObstacle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(editanywhere)
		class UStaticMeshComponent* m_pMesh;
private:
	float m_ElapsedTime; // Make it destroy itself after some time
};
