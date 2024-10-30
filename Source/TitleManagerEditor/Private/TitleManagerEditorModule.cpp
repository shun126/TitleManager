/**
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#include "TitleManagerEditorModule.h"
#include "TitleManagerDatabaseTypeActions.h"

#include <AssetToolsModule.h>
#include <IAssetTools.h>
#include <ToolMenus.h>
#include <Misc/EngineVersionComparison.h>
#include <Misc/MessageDialog.h>
#include <UObject/UObjectGlobals.h>

#define LOCTEXT_NAMESPACE "FTitleManagerEditorModule"

DECLARE_LOG_CATEGORY_EXTERN(TitleManagerLogger, Log, All);
#define TITLE_MANAGER_ERROR(Format, ...)		UE_LOG(TitleManagerLogger, Error, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_WARNING(Format, ...)		UE_LOG(TitleManagerLogger, Warning, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_DISPLAY(Format, ...)		UE_LOG(TitleManagerLogger, Display, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_LOG(Format, ...)			UE_LOG(TitleManagerLogger, Log, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_VERBOSE(Format, ...)		UE_LOG(TitleManagerLogger, Verbose, Format, ##__VA_ARGS__)
DEFINE_LOG_CATEGORY(TitleManagerLogger);

void FTitleManagerEditorModule::StartupModule()
{
	// Get assetTools module
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("assetTools").Get();

	// Asset
	EAssetTypeCategories::Type gameAssetCategory = assetTools.RegisterAdvancedAssetCategory(
		FName(TEXT("TitleManagerAssets")),
		FText::FromName(TEXT("TitleManager"))
	);

	// Register FTitleManagerDatabaseTypeActions
	{
		TSharedPtr<IAssetTypeActions> actionType = MakeShareable(new FTitleManagerDatabaseTypeActions(gameAssetCategory));
		assetTools.RegisterAssetTypeActions(actionType.ToSharedRef());
	}
}

void FTitleManagerEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTitleManagerEditorModule, TitleManagerEditorModule)
