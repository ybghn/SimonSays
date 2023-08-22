// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "ColorCube.h"
#include "CenterCube.generated.h"

UCLASS()
class SIMONSAYS_UE4_API ACenterCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACenterCube();
	FORCEINLINE void SetOffTime(float _duration) { offTime = _duration; }
	void SetText(FString _text, FColor _color);
	void SetArrowEnable(TypeOfCube _correctColor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private :

	UMaterial* material;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> arrows;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* text;


	UPaperSpriteComponent*  redSprite;
	UPaperSpriteComponent* blueSprite;
	UPaperSpriteComponent* yellowSprite;
	UPaperSpriteComponent* greenSprite;

	float offTime=1.f;

	void SetOffEveryThing(); // set off arrows and text feature
};
