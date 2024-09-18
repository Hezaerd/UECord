// Copyright (c) 2024 hezaerd.com


#include "DiscordActivityManager.h"
#include "UECord.h"
#include "UECord/discord-cpp/core.h"


void UDiscordActivityManager::Create(UDiscordCore* DiscordCore)
{
	IDiscordInterface::Create(DiscordCore);
}

void UDiscordActivityManager::UpdateActivity(const FDiscordActivity& NewActivity)
{
	if(!GetCore())
	{
		UE_LOG(LogUECord, Error, TEXT("DiscordCore is not initialized!"));
		return;
	}

	auto newActivity = discord::Activity();
	newActivity.SetState(TCHAR_TO_UTF8(*NewActivity.State));
	newActivity.SetDetails(TCHAR_TO_UTF8(*NewActivity.Details));
	newActivity.GetTimestamps().SetStart(NewActivity.StartTimestamp);
	newActivity.GetTimestamps().SetEnd(NewActivity.EndTimestamp);
	newActivity.GetAssets().SetLargeImage(TCHAR_TO_UTF8(*NewActivity.LargeImageKey));
	newActivity.GetAssets().SetLargeText(TCHAR_TO_UTF8(*NewActivity.LargeImageText));
	newActivity.GetAssets().SetSmallImage(TCHAR_TO_UTF8(*NewActivity.SmallImageKey));
	newActivity.GetAssets().SetSmallText(TCHAR_TO_UTF8(*NewActivity.SmallImageText));
	newActivity.GetParty().SetId(TCHAR_TO_UTF8(*NewActivity.PartyID));
	newActivity.GetParty().GetSize().SetCurrentSize(NewActivity.CurrentSize);
	newActivity.GetParty().GetSize().SetMaxSize(NewActivity.MaxSize);
	newActivity.GetSecrets().SetMatch(TCHAR_TO_UTF8(*NewActivity.MatchSecret));
	newActivity.GetSecrets().SetJoin(TCHAR_TO_UTF8(*NewActivity.JoinSecret));
	newActivity.GetSecrets().SetSpectate(TCHAR_TO_UTF8(*NewActivity.SpectateSecret));
	newActivity.SetInstance(NewActivity.Instance);
	
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

	GetCore()->ActivityManager().UpdateActivity(newActivity, UpdateActivityHandler);
}