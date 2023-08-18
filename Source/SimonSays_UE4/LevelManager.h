// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ColorCube.h"
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


protected:

	virtual void BeginPlay() override;

private:	
	TArray<AColorCube*> cubes;
	UPROPERTY(VisibleAnywhere)
	TArray<TEnumAsByte<TypeOfCube>> listOfCube;
	AColorCube* current;
	UPROPERTY(VisibleAnywhere)

	TArray<TEnumAsByte<TypeOfCube>> listOfPointedCubes;
	UPROPERTY(VisibleAnywhere)

	TArray<TEnumAsByte<TypeOfCube>> listOfTempCubes;
	int score{ 0 };
	float delayBetweenTurns = 2;
	float delayBtweenBlinks = 1.5f;
	FTimerHandle timerHandler;
	void SelectRandomColor();
	void CreateNewTurn();
	void StartGame();
	void EvaulateResult();
	void GameOver();
	UPROPERTY(VisibleAnywhere)

	bool bPlayMode = false;
	//Slots
	void OnLeftMousePressed();
};
