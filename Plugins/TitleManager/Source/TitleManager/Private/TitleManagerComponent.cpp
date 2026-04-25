/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

#include "TitleManagerComponent.h"
#include "TitleManagerLog.h"
#include "ExperienceCategoryValue.h"

UTitleManagerComponent::UTitleManagerComponent(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	bWantsInitializeComponent = true;
}

void UTitleManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();
	InitializeExperienceCategoryValue();
}

bool UTitleManagerComponent::InitializeExperienceCategoryValue()
{
	if (IsValid(TitleManagerDatabase) == false)
		return false;

	for (const auto& pair : TitleManagerDatabase->ExperienceCategoryData)
	{
		// 経験値を初期化
		FExperienceCategoryValue* value = ExperienceCategoryValue.Find(pair.Key);
		if (value == nullptr)
		{
			value = &ExperienceCategoryValue.Add(pair.Key);
			value->Experience = pair.Value.ExperienceRange.Min;
		}
		else
		{
			if (value->Experience < pair.Value.ExperienceRange.Min)
				value->Experience = pair.Value.ExperienceRange.Min;
			else if (value->Experience > pair.Value.ExperienceRange.Max)
				value->Experience = pair.Value.ExperienceRange.Max;
		}

		// ExperienceCategoryDataへのキャッシュ
		value->ExperienceCategoryData = &pair.Value;

		// 各アイテムの熟練度を初期化
		for (const auto& name : pair.Value.ProficiencyName)
		{
			auto proficiency = value->Proficiency.Find(name);
			if (proficiency == nullptr)
			{
				proficiency = &value->Proficiency.Add(name);
				proficiency->Proficiency = pair.Value.ProficiencyRange.Min;
			}
			else
			{
				if (proficiency->Proficiency < pair.Value.ProficiencyRange.Min)
					proficiency->Proficiency = pair.Value.ProficiencyRange.Min;
				else if (proficiency->Proficiency > pair.Value.ProficiencyRange.Max)
					proficiency->Proficiency = pair.Value.ProficiencyRange.Max;
			}
		}
	}

	return true;
}

bool UTitleManagerComponent::Load(const FTitleManagerSerializeData& titleManagerSerializeData)
{
	ExperienceCategoryValue = titleManagerSerializeData.ExperienceCategoryValue;
	return InitializeExperienceCategoryValue();
}

FTitleManagerSerializeData UTitleManagerComponent::Save() const
{
	FTitleManagerSerializeData titleManagerSerializeData;
	titleManagerSerializeData.ExperienceCategoryValue = ExperienceCategoryValue;
	return titleManagerSerializeData;
}

const FExperienceCategoryData* UTitleManagerComponent::FindExperienceCategoryData(const FString& categoryName) const
{
	if (IsValid(TitleManagerDatabase) == false)
		return nullptr;

	return TitleManagerDatabase->FindExperienceCategoryData(categoryName);
}

int32 UTitleManagerComponent::GetExperience(const FString& categoryName)
{
	if (const FExperienceCategoryValue* value = ExperienceCategoryValue.Find(categoryName))
		return value->Experience;

	TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
	return 0;
}

int32 UTitleManagerComponent::SetExperience(const FString& categoryName, int32 experience)
{
	FExperienceCategoryValue* value = ExperienceCategoryValue.Find(categoryName);
	if (value == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	if (value->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category 'A' under ExperienceCategoryData 'B'.")
			, *categoryName
			, *databaseName
		);
		return 0;
	}

	if (experience < value->ExperienceCategoryData->ExperienceRange.Min)
		experience = value->ExperienceCategoryData->ExperienceRange.Min;
	else if (experience > value->ExperienceCategoryData->ExperienceRange.Max)
		experience = value->ExperienceCategoryData->ExperienceRange.Max;

	value->Experience = experience;
	return experience;
}

int32 UTitleManagerComponent::AddExperience(const FString& categoryName, const int32 experience)
{
	FExperienceCategoryValue* value = ExperienceCategoryValue.Find(categoryName);
	if (value == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	int32 newExperience = value->Experience + experience;
	if (value->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category 'A' under ExperienceCategoryData 'B'.")
			, *categoryName
			, *databaseName
		);
		return 0;
	}

	if (newExperience < value->ExperienceCategoryData->ExperienceRange.Min)
		newExperience = value->ExperienceCategoryData->ExperienceRange.Min;
	else if (newExperience > value->ExperienceCategoryData->ExperienceRange.Max)
		newExperience = value->ExperienceCategoryData->ExperienceRange.Max;

	value->Experience = newExperience;
	return newExperience;
}

float UTitleManagerComponent::GetExperienceRatio(const FString& categoryName)
{
	FExperienceCategoryValue* value = ExperienceCategoryValue.Find(categoryName);
	if (value == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0.f;
	}

	if (value->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category 'A' under ExperienceCategoryData 'B'.")
			, *categoryName
			, *databaseName
		);
		return 0.f;
	}

	const int32 minValue = value->ExperienceCategoryData->ExperienceRange.Min;
	const int32 maxValue = value->ExperienceCategoryData->ExperienceRange.Max;
	const float range = static_cast<float>(maxValue - minValue);
	if (range == 0.f)
		return 0.f;

	const float current = static_cast<float>(value->Experience - minValue);
	return current / range;
}


int32 UTitleManagerComponent::GetProficiency(const FString& categoryName, const FString& itemName)
{
	const FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	const FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return 0;
	}

	return proficiencyValue->Proficiency;
}

int32 UTitleManagerComponent::SetProficiency(const FString& categoryName, const FString& itemName, int32 proficiency)
{
	FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	if (experienceValue->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category 'A' under ExperienceCategoryData 'B'.")
			, *categoryName
			, *databaseName
		);
		return 0;
	}

	if (proficiency < experienceValue->ExperienceCategoryData->ProficiencyRange.Min)
		proficiency = experienceValue->ExperienceCategoryData->ProficiencyRange.Min;
	else if (proficiency > experienceValue->ExperienceCategoryData->ProficiencyRange.Max)
		proficiency = experienceValue->ExperienceCategoryData->ProficiencyRange.Max;

	FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return 0;
	}

	proficiencyValue->Proficiency = proficiency;
	return proficiency;
}

int32 UTitleManagerComponent::AddProficiency(const FString& categoryName, const FString& itemName, const int32 proficiency)
{
	FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return 0;
	}

	proficiencyValue->Proficiency += proficiency;

	if (experienceValue->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category 'A' under ExperienceCategoryData 'B'.")
			, *categoryName
			, *databaseName
		);
		return 0;
	}

	if (proficiencyValue->Proficiency < experienceValue->ExperienceCategoryData->ProficiencyRange.Min)
		proficiencyValue->Proficiency = experienceValue->ExperienceCategoryData->ProficiencyRange.Min;
	else if (proficiencyValue->Proficiency > experienceValue->ExperienceCategoryData->ProficiencyRange.Max)
		proficiencyValue->Proficiency = experienceValue->ExperienceCategoryData->ProficiencyRange.Max;

	return proficiencyValue->Proficiency;
}

float UTitleManagerComponent::GetProficiencyRatio(const FString& categoryName, const FString& itemName)
{
	const FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	if (experienceValue->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category '%s' under ExperienceCategoryData '%s'.")
			, *categoryName
			, *databaseName
		);
		return 0.f;
	}

	const FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return 0;
	}

	const int32 minValue = experienceValue->ExperienceCategoryData->ProficiencyRange.Min;
	const int32 maxValue = experienceValue->ExperienceCategoryData->ProficiencyRange.Max;
	const float range = static_cast<float>(maxValue - minValue);
	if (range == 0.f)
		return 0.f;

	const float current = static_cast<float>(proficiencyValue->Proficiency - minValue);
	return current / range;
}

uint8 UTitleManagerComponent::GetQuantity(const FString& categoryName, const FString& itemName)
{
	const FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	const FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return 0;
	}

	return proficiencyValue->Quantity;
}

void UTitleManagerComponent::SetQuantity(const FString& categoryName, const FString& itemName, const uint8 quantity)
{
	FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return;
	}

	FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return;
	}

	proficiencyValue->Quantity = quantity;
}

uint8 UTitleManagerComponent::AddQuantity(const FString& categoryName, const FString& itemName, const int32 quantity)
{
	FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return 0;
	}

	FProficiencyValue* proficiencyValue = experienceValue->Proficiency.Find(itemName);
	if (proficiencyValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The item name '%s' is not defined."), *itemName);
		return 0;
	}

	int32 value = static_cast<int32>(proficiencyValue->Quantity) + quantity;
	if (value < std::numeric_limits<uint8>::min())
		value = std::numeric_limits<uint8>::min();
	else if (value > std::numeric_limits<uint8>::max())
		value = std::numeric_limits<uint8>::max();
	proficiencyValue->Quantity = value;

	return proficiencyValue->Quantity;
}

FString UTitleManagerComponent::FindMaxExperienceTitle() const
{
	FString hightestValueKey;
	int32 hightestExperience = std::numeric_limits<int32>::min();
	for (const auto& pair : ExperienceCategoryValue)
	{
		if (hightestExperience < pair.Value.Experience)
		{
			hightestExperience = pair.Value.Experience;
			hightestValueKey = pair.Key;
		}
	}
	return FindCategoryTitle(hightestValueKey);
}

FString UTitleManagerComponent::FindCategoryTitle(const FString& categoryName) const
{
	const FExperienceCategoryValue* experienceValue = ExperienceCategoryValue.Find(categoryName);
	if (experienceValue == nullptr)
	{
		TITLE_MANAGER_ERROR(TEXT("The category name '%s' is not defined."), *categoryName);
		return FString();
	}

	if (experienceValue->ExperienceCategoryData == nullptr)
	{
		FString databaseName;
		if (TitleManagerDatabase)
			databaseName = TitleManagerDatabase->GetName();
		TITLE_MANAGER_ERROR(TEXT("Unable to register Category '%s' under ExperienceCategoryData '%s'.")
			, *categoryName
			, *databaseName
		);
		return FString();
	}

	FString titleName;
	int32 hightestExperience = std::numeric_limits<int32>::min();
	for (const FTitleData& titleData : experienceValue->ExperienceCategoryData->Title)
	{
		// 現在の経験値よりも称号の経験値が低い？
		if (experienceValue->Experience >= titleData.TitleAchievementExperience)
		{
			// 最も高い称号？
			if (hightestExperience < titleData.TitleAchievementExperience)
			{
				hightestExperience = titleData.TitleAchievementExperience;
				titleName = titleData.TitleName;
			}
		}
	}

	return titleName;
}

const UTitleManagerDatabase* UTitleManagerComponent::GetTitleManagerDatabase() const noexcept
{
	return TitleManagerDatabase;
}

const TMap<FString, FExperienceCategoryValue>& UTitleManagerComponent::GetExperienceCategoryValue() const noexcept
{
	return ExperienceCategoryValue;
}
