// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ColorCube.generated.h"

UENUM(Blueprintable)
enum TypeOfCube {
	Red,
	Blue,
	Yellow,Green
};


UCLASS()
class SIMONSAYS_UE4_API AColorCube : public AActor
{
	GENERATED_BODY()
	
public:	
	AColorCube();
	virtual void Tick(float DeltaTime) override;
	void SetType(TypeOfCube _type);
	FORCEINLINE TypeOfCube Type() { return type; }
	void Blink();
protected:
	virtual void BeginPlay() override;

private:	
	UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere)

	TEnumAsByte<TypeOfCube> type;
	UPROPERTY(VisibleAnywhere)
	UMaterial* material; // keeps original material
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* materialInstance;
	FTimerHandle timerHandle;
	float blinkDuration = 0.05; // Blink duration as second
	void SetInitialColors();
	void BlinkLoopAnimation();
	void BlinkOff();
	bool bCubeShining = false;
	float brightnessValue = 0;


};