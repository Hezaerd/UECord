// Copyright (c) 2024 hezaerd.com

#include "UECord.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

DEFINE_LOG_CATEGORY(UECordLog);

const FName FUECordModule::ModuleName = "UECord";

void FUECordModule::StartupModule()
{
	// Determine the path to the Discord GameSDK DLL to load for the current platform and environment
	const FString LibraryPath = GetPathToDLL();

	// Check if we get something valid
	if ensureAlwaysMsgf(!LibraryPath.IsEmpty(), TEXT("Expect to load DiscordSDK to path [%s]"), *LibraryPath)
	{
		// Load the Discord GameSDK DLL
		DiscordGameSDKHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
		if (DiscordGameSDKHandle)
		{
			UE_LOG(UECordLog, Log, TEXT("Discord GameSDK loaded successfully from [%s]"), *LibraryPath);
		}
		else
		{
			UE_LOG(UECordLog, Error, TEXT("Failed to load Discord GameSDK from [%s]"), *LibraryPath);
		}
	}
}

void FUECordModule::ShutdownModule()
{
	if (DiscordGameSDKHandle)
	{
		// Free the DLL handle
		FPlatformProcess::FreeDllHandle(DiscordGameSDKHandle);
		DiscordGameSDKHandle = nullptr;
	}
}

FString FUECordModule::GetPathToDLL() const
{
	// Add on the relative location of the third party dll and load it
	FString LibraryPath;

#if WITH_EDITOR && (PLATFORM_WINDOWS || PLATFORM_LINUX)

	// When compiling as Editor, the SDK files DO NOT get copied to the Binaries directory,
	// so we need to load them directly from the Source location.

	FString BaseDir = IPluginManager::Get().FindPlugin(ModuleName.ToString())->GetBaseDir();
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/DiscordGameSDK"));

#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("x86_64/discord_game_sdk.dll"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("x86_64/discord_game_sdk.so"));
#else
#error Unsupported platform
#endif

#else

	// When compiling as Game, the build process copies the SDK DLLs to the Binaries directory,
	// and from here they are packaged for distribution.
	//
	// Macs work a bit differently, they always package the DLLs in this way, even when
	// compiling as Editor.

	// Load DLLs from the distribution location.

	FString BaseDir = FPaths::ProjectDir();
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries"));

#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("Win64/discord_game_sdk.dll"));
#elif PLATFORM_MAC
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("Mac/discord_game_sdk.dylib"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("Linux/discord_game_sdk.so"));
#else
#error Unsupported platform
#endif

#endif

	const FString FullPath (FPaths::ConvertRelativePathToFull(*LibraryPath));
	return FullPath; 
}

IMPLEMENT_MODULE(FUECordModule, UECord);