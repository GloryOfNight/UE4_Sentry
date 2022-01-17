#pragma once
#include <Containers/UnrealString.h>

#include "ApplicationInfo.generated.h"

USTRUCT()
struct SENTRY_API FSentryApplicationInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Distribution{};

	UPROPERTY()
	FString Environment{};

	UPROPERTY()
	FString Platform{};

	UPROPERTY()
	FString Release{};

	UPROPERTY()
	FString ServerName{};

	FSentryApplicationInfo& SetDistribution(const FString& Value);
	FSentryApplicationInfo& SetDistribution(FString&& Value);

	FSentryApplicationInfo& SetEnvironment(const FString& Value);
	FSentryApplicationInfo& SetEnvironment(FString&& Value);

	FSentryApplicationInfo& SetPlatform(const FString& Value);
	FSentryApplicationInfo& SetPlatform(FString&& Value);

	FSentryApplicationInfo& SetRelease(const FString& Value);
	FSentryApplicationInfo& SetRelease(FString&& Value);

	FSentryApplicationInfo& SetServerName(const FString& Value);
	FSentryApplicationInfo& SetServerName(FString&& Value);
};