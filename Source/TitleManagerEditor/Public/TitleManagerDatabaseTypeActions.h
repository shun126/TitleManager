/**
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include "TitleManagerAssetTypeActionsBase.h"

class TITLEMANAGEREDITOR_API FTitleManagerDatabaseTypeActions : public FTitleManagerAssetTypeActionsBase
{
public:
	explicit FTitleManagerDatabaseTypeActions(EAssetTypeCategories::Type InAssetCategory);
	virtual ~FTitleManagerDatabaseTypeActions() override = default;

	// IAssetTypeActions Implementation
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type mAssetCategory;
};
