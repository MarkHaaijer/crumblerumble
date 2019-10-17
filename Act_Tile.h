// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generators/Act_TileGenerator.h"
#include "Generators/Act_PickupGenerator.h"
#include "Components/BoxComponent.h"
#include "interfaces/Interface_DamageAble.h"
#include "Act_Tile.generated.h"

UCLASS()
class CRUMBLERUMBLE_API AAct_Tile : public AActor, public IInterface_DamageAble
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAct_Tile();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem *m_FallParticle1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem *m_FallParticle2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem *m_FallParticle3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh *m_pTileMesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh *m_pTileMesh2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh *m_pTileMesh3;

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Interface")
		 bool TakeDamage(float health); // This tells your class that you can both call and override this function in blueprints. You need this part as well if you want to be able to override C++ functionality within BP
	virtual bool TakeDamage_Implementation(float health) override; //This line tells your class that it has a function of this name and signature to inherit from the interface, which is how calls to the interface functions are able to interact with this class.

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UStaticMeshComponent* m_pMesh;

	int m_MinHealth = 35;
	int m_MaxHealth = 50;
	uint32 m_TileSize = 100;
	uint32 m_FallRate = 400; //100 = 100% = 1 row a second

	float m_Health = FMath::RandRange(m_MinHealth,m_MaxHealth);
	float m_DamageXPos = 300.f;
	float m_StartHealthDrain = 20.f;
	float m_HealthDrain = 20.f;
	float m_NewHealthDrain = 50.0f;
	float m_ElapsedTime = 0.f;

    UBoxComponent* m_pBoxComp; // Collider
	AAct_TileGenerator* m_pTileGeneratorActor;
	AAct_PickupGenerator* m_pPickupGeneratorActor;
	FVector m_BoxExtent;

	bool m_Draining = false;

	class UNiagaraComponent* m_pParticle;
};