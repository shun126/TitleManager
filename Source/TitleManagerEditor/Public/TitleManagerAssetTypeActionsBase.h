/**
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include <CoreMinimal.h>
#include <AssetTypeActions_Base.h>

class TITLEMANAGEREDITOR_API FTitleManagerAssetTypeActionsBase : public FAssetTypeActions_Base
{
public:
    explicit FTitleManagerAssetTypeActionsBase() = default;
	virtual ~FTitleManagerAssetTypeActionsBase() override = default;

	// FAssetTypeActions_Base overrides
	virtual FColor GetTypeColor() const override
    {
        static constexpr FColor Color(56, 156, 156);
        return Color;
    }

    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override
    {
        FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
    }
};
