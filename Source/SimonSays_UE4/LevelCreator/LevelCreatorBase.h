// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ColorCube.h"
#include "../CenterCube.h"

class SIMONSAYS_UE4_API LevelCreatorBase
{
public:
	LevelCreatorBase(TArray<AColorCube*> _cubes);
	~LevelCreatorBase();

	virtual void Execute()=0 ;
	FORCEINLINE TypeOfCube Type() { return ownColor; }

protected:
	TArray<AColorCube*> cubesInScene;

private:
	TEnumAsByte<TypeOfCube> ownColor;
};
