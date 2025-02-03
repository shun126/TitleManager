/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

#pragma once
#include "TitleData.h"
#include <limits>
#include "ExperienceCategoryData.generated.h"

/**
 * Experience Categories
 * 経験値のカテゴリ
 */
USTRUCT(Blueprintable, BlueprintType)
struct TITLEMANAGER_API FExperienceCategoryData
{
	GENERATED_BODY()

	/**
	 * Proficiency Range
	 * 熟練度の範囲
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager|Proficiency")
	FInt32Interval ProficiencyRange = { 0, 100 };

	/**
	 * Experience Range
	 * 経験値の範囲
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager|Experience")
	FInt32Interval ExperienceRange = { 0, std::numeric_limits<int32>::max() };

	/**
	 * Name of the item (record the proficiency level for each item)
	 * アイテムの名前（アイテム毎に熟練度を記録します）
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager|Proficiency", DisplayName="Item Name")
	TArray<FString> ProficiencyName;

	/**
	 * Title
	 * 称号
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager|Experience")
	TArray<FTitleData> Title;
};
