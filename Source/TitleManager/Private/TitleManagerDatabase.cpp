/**
称号マネージャー
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#include "TitleManagerDatabase.h"
#include <Engine/World.h>

UTitleManagerDatabase::UTitleManagerDatabase(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
}

const FExperienceCategoryData* UTitleManagerDatabase::FindExperienceCategoryData(const FString& categoryName) const
{
	return ExperienceCategoryData.Find(categoryName);
}
