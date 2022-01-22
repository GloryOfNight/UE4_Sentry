#pragma once
#include <Containers/UnrealString.h>

#include "ApplicationInfo.generated.h"

USTRUCT()
struct SENTRY_API FSentryApplicationInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Distribution;

	UPROPERTY()
	FString Environment;

	UPROPERTY()
	FString Release;

	UPROPERTY()
	FString ServerName;

	UPROPERTY()
	TMap<FString, FString> Tags;

	FSentryApplicationInfo& SetDistribution(const FString& Value);
	FSentryApplicationInfo& SetDistribution(FString&& Value);

	FSentryApplicationInfo& SetEnvironment(const FString& Value);
	FSentryApplicationInfo& SetEnvironment(FString&& Value);

	FSentryApplicationInfo& SetRelease(const FString& Value);
	FSentryApplicationInfo& SetRelease(FString&& Value);

	FSentryApplicationInfo& SetServerName(const FString& Value);
	FSentryApplicationInfo& SetServerName(FString&& Value);

	FSentryApplicationInfo& SetTags(const TMap<FString, FString>& Value);
	FSentryApplicationInfo& SetTags(TMap<FString, FString>&& Value);

	FSentryApplicationInfo& AddTag(const FString& Key, const FString& Value = {});
};