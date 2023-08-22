// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "LevelCreatorBase.h"
/**
 * 
 */
class SIMONSAYS_UE4_API ArrowBasedLevelCreator : public LevelCreatorBase
{
public:
	ArrowBasedLevelCreator(ACenterCube *_centerCube,TArray<AColorCube*> _cubes);

	~ArrowBasedLevelCreator();
	void Execute() override;
private:
	AColorCube* GetFakeCube(); // Creates color different from ownColor
	ACenterCube* centerCube;
};
