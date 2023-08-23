// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ColorCube.h"
#include "CenterCube.h"
#include "LevelCreator/LevelCreatorBase.h"
#include "LevelCreator/ArrowBasedLevelCreator.h"
#include "LevelCreator/ColorBaseLevelCreator.h"
#include "LevelCreator/TextBasedLevelCreator.h"
#include "PaperSprite.h"

#include "LevelManager.generated.h"

UCLASS(Blueprintable)
class SIMONSAYS_UE4_API ALevelManager : public APawn
{
	GENERATED_BODY()

public:

	ALevelManager();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetScore() { return score; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bPlayMode = false;
protected:

	virtual void BeginPlay() override;

private:	
	TArray<AColorCube*> cubes;
	TArray<LevelCreatorBase*> levels;
	AColorCube* current;
	ACenterCube* centerCube;

	UPROPERTY(VisibleAnywhere)
	TArray<TEnumAsByte<TypeOfCube>> listOfPointedCubes;

	
	int score{ 0 };
	float delayBetweenTurns = 2;
	float delayBtweenBlinks = 1.5f;
	FTimerHandle timerHandler;
	int turnCounter = 0;
	void StartGame();
	LevelCreatorBase* GetRandomLevel(); // Creates level according to score
	void CreateNewTurn();
	void StartTurnAnimation();
	void EvaulateResult();
	void GameOver();
	
	//Slots
	void OnLeftMousePressed();
};
