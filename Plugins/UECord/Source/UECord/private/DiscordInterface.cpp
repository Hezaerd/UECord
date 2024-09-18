// Copyright (c) 2024 hezaerd.com


#include "DiscordInterface.h"
#include "DiscordCore.h"
#include "UECord/discord-cpp/core.h"

discord::Core* IDiscordInterface::GetCore() const
{
	if (Core && Core->GetCore())
		return Core->GetCore();

	return nullptr;
}