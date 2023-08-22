// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCreatorBase.h"


LevelCreatorBase::LevelCreatorBase(TArray<AColorCube*> _cubes)
{

	cubesInScene = _cubes;

	ownColor = (TEnumAsByte<TypeOfCube>)FMath::RandRange(0, 3);

}

LevelCreatorBase::~LevelCreatorBase()
{
}


