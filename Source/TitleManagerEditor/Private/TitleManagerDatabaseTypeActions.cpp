/**
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#include "TitleManagerDatabaseTypeActions.h"
#include "TitleManagerDatabase.h"

FTitleManagerDatabaseTypeActions::FTitleManagerDatabaseTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: mAssetCategory(InAssetCategory)
{
}

FText FTitleManagerDatabaseTypeActions::GetName() const
{
	return FText::FromName(TEXT("Title manager database"));
}

UClass* FTitleManagerDatabaseTypeActions::GetSupportedClass() const
{
	return UTitleManagerDatabase::StaticClass();
}

uint32 FTitleManagerDatabaseTypeActions::GetCategories()
{
	return mAssetCategory;
}
