// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sentry/Sentry.h"

#define LOCTEXT_NAMESPACE "FSentryModule"

void FSentryModule::StartupModule()
{
	if(!Manager)
	{
		Manager = NewObject<USentryManager>();
	}

#if WITH_EDITOR
#include <ISettingsModule.h>
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if(SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Sentry",
			LOCTEXT("SentrySettingsName", "Sentry"),
			LOCTEXT("SentrySettingsDescription", "Configure Sentry plugin"),
			GetMutableDefault<USentrySettings>());
	}
#endif
}

void FSentryModule::ShutdownModule()
{
	// Manager var will be deleted by unreal cleaning of unreachable objects on exit
}

USentryManager* FSentryModule::GetManager()
{
	static FSentryModule* Module = nullptr;
	if(!Module)
	{
		Module = FModuleManager::GetModulePtr<FSentryModule>(TEXT("Sentry"));
	}
	return Module ? Module->Manager : nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSentryModule, Sentry)