// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelCreatorBase.h"
#include "../CenterCube.h"
#include "../ColorCube.h"
/**
 * 
 */
class SIMONSAYS_UE4_API TextBasedLevelCreator : public LevelCreatorBase
{
public:
	TextBasedLevelCreator(ACenterCube *_centerCube, TArray<AColorCube*> _cubes);
	~TextBasedLevelCreator();

	void Execute() override;

private:
	ACenterCube* centerCube;
	FColor GetFakeColor();
};
