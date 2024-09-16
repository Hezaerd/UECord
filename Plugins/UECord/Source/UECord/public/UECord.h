// Copyright (c) 2024 hezaerd.com

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(UECordLog, Log, All);

class FUECordModule : public IModuleInterface
{
public:
	/** Name of the module */
	static const FName ModuleName;

	// return Pointer to FUECordModule, if it has been loaded into the Engine, else return nullptr 
	static FUECordModule* Get()
	{
		return static_cast<FUECordModule*>(FModuleManager::Get().GetModule(ModuleName));
	}

	// Check if the Discord GameSDK has been loaded
	FORCEINLINE bool IsDiscordSDKLoaded() const { return DiscordGameSDKHandle != nullptr; }

	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
protected:
	/**
	 * Get the path to the Discord GameSDK DLL for the current platform.
	 * @return Absolute path to the Discord GameSDK DLL we need to load
	 */
	FString GetPathToDLL() const;
	
private:
	/** Handle to the loaded Discord Game SDK */
	void* DiscordGameSDKHandle = nullptr;
};
