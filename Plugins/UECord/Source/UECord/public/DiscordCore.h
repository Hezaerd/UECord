// Copyright (c) 2024 hezaerd.com

#pragma once

#include "CoreMinimal.h"
#include "DiscordTypes.h"
#include "DiscordCore.generated.h"

/** forward references
*/
namespace discord
{
	class Core;
}

/**
 * 
 */
UCLASS(Blueprintable)
class UECORD_API UDiscordCore : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UECord|Core")
		static UDiscordCore* CreateDiscordCore(const bool bIsDiscordRequired, const int64 ClientID, const int ReconnectLimit, const float ReconnectDelay);

	virtual void BeginDestroy() override;
	
	FORCEINLINE discord::Core* GetCore() const { return Core; }

	//* TickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	//*/

	UFUNCTION(BlueprintCallable, Category = "UECord|Activity")
		void UpdateActivity(FDiscordActivity NewActivity);
	
private:
	void Initialize(bool bIsDiscordRequiered, int64 ClientID, int ReconnectLimit, float ReconnectDelay);
	
private: // properties
	discord::Core* Core = nullptr;
	
	int ReconnectCount = 0;
};
