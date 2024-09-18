// Copyright (c) 2024 hezaerd.com

#pragma once

#include "CoreMinimal.h"
#include "DiscordTypes.h"
#include "UObject/Object.h"
#include "Tickable.h"
#include "DiscordCore.generated.h"

/** forward references
*/
namespace discord
{
	class Core;
}

class UDiscordActivityManager;

/**
 * 
 */
UCLASS(Blueprintable)
class UECORD_API UDiscordCore : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Discord|Core")
	static UDiscordCore* CreateDiscordCore(bool bIsDiscordRequiered, int64 ClientID, int ReconnectLimit, float ReconnectDelay);
	
	virtual void BeginDestroy() override;

	//* TickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	//*/
	
	FORCEINLINE discord::Core* GetCore() const { return Core; }

	UFUNCTION(BlueprintCallable, Category = "Discord|Core|Manager")
	UDiscordActivityManager* GetActivityManager() const { return ActivityManager; }

private:
	void Initialize(bool bIsDiscordRequiered, int64 ClientID, int ReconnectLimit, float ReconnectDelay);
	void InitializeManagers();
	
private: // properties
	discord::Core* Core = nullptr;
	
	int ReconnectCount = 0;

	UPROPERTY()
	UDiscordActivityManager* ActivityManager = nullptr;
};
