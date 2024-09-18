// Copyright (c) 2024 hezaerd.com

#pragma once

#include "CoreMinimal.h"
#include "UECord/discord-cpp/types.h"
#include "DiscordTypes.generated.h"

USTRUCT(BlueprintType)
struct FDiscordActivity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString State; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString Details; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") int64 StartTimestamp = 0; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") int64 EndTimestamp = 0; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString LargeImageKey; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString LargeImageText; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString SmallImageKey; 
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString SmallImageText;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString PartyID;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") int32 CurrentSize = 1;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") int32 MaxSize = 1;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString MatchSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString JoinSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") FString SpectateSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord|Activity") bool Instance = false;
};