// Copyright (c) 2024 hezaerd.com


#include "DiscordCore.h"
#include "UECord.h"
#include "UECord/discord-cpp/core.h"

void UDiscordCore::Initialize(bool bIsDiscordRequired, int64 ClientID, int ReconnectLimit, float ReconnectDelay)
{
	// No need to initialize if we are running a dedicated server
	if (IsRunningDedicatedServer())
		return;

	if (ReconnectCount <= 0)
		UE_LOG(LogUECord, Log, TEXT("Trying to connect with Discord..."));

	discord::Result Result = discord::Result::InternalError;
	
	if (bIsDiscordRequired)
	{
		UE_LOG(LogUECord, Log, TEXT("Discord is required!"));
		
		Result = discord::Core::Create(
			ClientID,
			DiscordCreateFlags_Default,
			&Core
		);
	}
	else
	{
		Result = discord::Core::Create(
			ClientID,
			DiscordCreateFlags_Default,
			&Core
		);
	}
	
	if (Result == discord::Result::Ok && Core != nullptr)
	{
		UE_LOG(LogUECord, Log, TEXT("Connected with Discord!"));

		ReconnectCount = 0;
	}
	else
	{
		if (ReconnectCount < ReconnectLimit)
		{
			ReconnectCount++;

			FTimerHandle UnusedHandle;
			GetWorld()->GetTimerManager().SetTimer(
				UnusedHandle,
				FTimerDelegate::CreateUObject(this, &UDiscordCore::Initialize, bIsDiscordRequired, ClientID, ReconnectLimit, ReconnectDelay),
				ReconnectDelay,
				false
			);
		}
		else
		{
			UE_LOG(LogUECord, Error, TEXT("Failed to connect with Discord!"));

			MarkAsGarbage();
		}
	}
}

void UDiscordCore::BeginDestroy()
{
	Super::BeginDestroy();
	
	if (Core)
	{
		delete Core;
		Core = nullptr;
	}
}

UDiscordCore* UDiscordCore::CreateDiscordCore(const bool bIsDiscordRequired, const int64 ClientID, const int ReconnectLimit = 5, const float ReconnectDelay = 1.0f)
{
	UDiscordCore* DiscordCore = NewObject<UDiscordCore>();
	DiscordCore->Initialize(bIsDiscordRequired, ClientID, ReconnectLimit, ReconnectDelay);

	return DiscordCore;
}

void UDiscordCore::Tick(float DeltaTime)
{
	if (Core)
	{
		Core->RunCallbacks();
	}
}

bool UDiscordCore::IsTickable() const
{
	return Core != nullptr;
}

TStatId UDiscordCore::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UDiscordCore, STATGROUP_Tickables);
}
