// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelCreatorBase.h"
/**
 * 
 */
class SIMONSAYS_UE4_API ColorBaseLevelCreator : public LevelCreatorBase
{
public:
	ColorBaseLevelCreator(TArray<AColorCube*> _cubes);
	~ColorBaseLevelCreator();
	
	void Execute() override;
private:
	AColorCube* myCube	;

	

};
