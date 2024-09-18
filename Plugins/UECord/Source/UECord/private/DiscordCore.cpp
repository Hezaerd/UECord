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

void UDiscordCore::UpdateActivity(FDiscordActivity NewActivity)
{
	if(!GetCore())
	{
		UE_LOG(LogUECord, Error, TEXT("DiscordCore is not initialized!"));
		return;
	}

	auto activity = discord::Activity();
	activity.SetState(TCHAR_TO_UTF8(*NewActivity.State));
	activity.SetDetails(TCHAR_TO_UTF8(*NewActivity.Details));
	activity.GetTimestamps().SetStart(NewActivity.StartTimestamp);
	activity.GetTimestamps().SetEnd(NewActivity.EndTimestamp);
	activity.GetAssets().SetLargeImage(TCHAR_TO_UTF8(*NewActivity.LargeImageKey));
	activity.GetAssets().SetLargeText(TCHAR_TO_UTF8(*NewActivity.LargeImageText));
	activity.GetAssets().SetSmallImage(TCHAR_TO_UTF8(*NewActivity.SmallImageKey));
	activity.GetAssets().SetSmallText(TCHAR_TO_UTF8(*NewActivity.SmallImageText));
	activity.GetParty().SetId(TCHAR_TO_UTF8(*NewActivity.PartyID));
	activity.GetParty().GetSize().SetCurrentSize(NewActivity.CurrentSize);
	activity.GetParty().GetSize().SetMaxSize(NewActivity.MaxSize);
	activity.GetSecrets().SetMatch(TCHAR_TO_UTF8(*NewActivity.MatchSecret));
	activity.GetSecrets().SetJoin(TCHAR_TO_UTF8(*NewActivity.JoinSecret));
	activity.GetSecrets().SetSpectate(TCHAR_TO_UTF8(*NewActivity.SpectateSecret));
	activity.SetInstance(NewActivity.Instance);

	auto UpdateActivityHandler = [&](discord::Result Result)
	{
		if (Result == discord::Result::Ok)
		{
			UE_LOG(LogUECord, Log, TEXT("%s Success!"), *FString(__FUNCTION__))
		}
		else
		{
			UE_LOG(LogUECord, Error, TEXT("%s Failed! Error Code: %d"), *FString(__FUNCTION__), static_cast<int32>(Result))
		}
	};

	GetCore()->ActivityManager().UpdateActivity(activity, UpdateActivityHandler);
}

