/**
称号マネージャー
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include "ExperienceCategoryData.h"
#include "TitleManagerDatabase.generated.h"

/**
Title Manager Database.
称号マネージャデータベース
*/
UCLASS(ClassGroup = "TitleManager")
class TITLEMANAGER_API UTitleManagerDatabase : public UObject
{
	GENERATED_BODY()

public:
	explicit UTitleManagerDatabase(const FObjectInitializer& objectInitializer);
	virtual ~UTitleManagerDatabase() override = default;

	/**
	 * Search for the experience points category data.
	 * 経験値のカテゴリデータを検索します
	 * @param categoryName カテゴリ名
	 * @return nullptrなら検索失敗
	 */
	const FExperienceCategoryData* FindExperienceCategoryData(const FString& categoryName) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager")
	TMap<FString, FExperienceCategoryData> ExperienceCategoryData;

private:
	friend class UTitleManagerComponent;
};
