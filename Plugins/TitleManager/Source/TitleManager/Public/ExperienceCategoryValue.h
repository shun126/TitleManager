/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

#pragma once
#include "ProficiencyValue.h"
#include "ExperienceCategoryData.h"
#include "ExperienceCategoryValue.generated.h"

/**
 * Experience Point
 * 経験値
 */
USTRUCT(Blueprintable, BlueprintType)
struct TITLEMANAGER_API FExperienceCategoryValue
{
	GENERATED_BODY()

	/**
	 * Experience Point
	 * 経験値
	 */
	UPROPERTY(BlueprintReadWrite, Category = "TitleManager")
	int32 Experience;

	/**
	 * Item Proficiency
	 * アイテムの熟練度
	 */
	UPROPERTY(BlueprintReadWrite, Category = "TitleManager")
	TMap<FString, FProficiencyValue> Proficiency;

private:
	/**
	 * Reference to the corresponding FExperienceCategoryData
	 * 対応するFExperienceCategoryDataへの参照
	 */
	const FExperienceCategoryData* ExperienceCategoryData = nullptr;

	friend class UTitleManagerComponent;
};

