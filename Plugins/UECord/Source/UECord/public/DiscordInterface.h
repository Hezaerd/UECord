// Copyright (c) 2024 hezaerd.com

#pragma once

#include "CoreMinimal.h"

/** forward references
*/
namespace discord
{
	class Core;
}

// This class does not need to be modified.
class UECORD_API IDiscordInterface : public IInterface
{
public:
	virtual void Create(class UDiscordCore* DiscordCore)
	{
		Core = DiscordCore;
	}

	virtual bool IsValid() const
	{
		return Core != nullptr;
	}

	virtual discord::Core* GetCore() const;

protected:
	UDiscordCore* Core = nullptr;
};