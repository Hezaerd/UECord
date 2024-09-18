// Copyright (c) 2024 hezaerd.com

#pragma once

#include "CoreMinimal.h"
#include "DiscordInterface.h"
#include "DiscordTypes.h"
#include "UObject/Object.h"
#include "DiscordActivityManager.generated.h"

/** forward references
*/
namespace discord
{
	class ActivityManager;
}

/**
 * 
 */
UCLASS(Blueprintable)
class UECORD_API UDiscordActivityManager : public UObject, public IDiscordInterface
{
	GENERATED_BODY()

public:
	virtual void Create(UDiscordCore* DiscordCore) override;


	UFUNCTION(BlueprintCallable, Category = "Discord|Activity")
		void UpdateActivity(const FDiscordActivity& Activity);
};
