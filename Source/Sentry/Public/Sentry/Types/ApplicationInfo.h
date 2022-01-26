#pragma once
#include <Containers/UnrealString.h>

#include "SentryMacroUtils.hxx"

#include "ApplicationInfo.generated.h"

// https://develop.sentry.dev/sdk/event-payloads/types/#geo
USTRUCT()
struct SENTRY_API FSentryUserGeoInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Region;

	UPROPERTY()
	FString CountryCode;

	UPROPERTY()
	FString City;

	SENTRY_SETTER(FSentryUserGeoInfo, FString, Region);
	SENTRY_SETTER(FSentryUserGeoInfo, FString, CountryCode);
	SENTRY_SETTER(FSentryUserGeoInfo, FString, City);
};

// https://develop.sentry.dev/sdk/event-payloads/types/#user
USTRUCT()
struct SENTRY_API FSentryUserInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Username;

	UPROPERTY()
	FString Segment;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString IpAddress;

	UPROPERTY()
	FString Id;

	UPROPERTY()
	FSentryUserGeoInfo Geo;

	UPROPERTY()
	FString Email;

	UPROPERTY()
	TMap<FString, FString> Data;

	SENTRY_SETTER(FSentryUserInfo, FString, Username);
	SENTRY_SETTER(FSentryUserInfo, FString, Segment);
	SENTRY_SETTER(FSentryUserInfo, FString, Name);
	SENTRY_SETTER(FSentryUserInfo, FString, IpAddress);
	SENTRY_SETTER(FSentryUserInfo, FString, Id);
	SENTRY_SETTER(FSentryUserInfo, FSentryUserGeoInfo, Geo);
	SENTRY_SETTER(FSentryUserInfo, FString, Email);
	SENTRY_SETTER_MAP(FSentryUserInfo, FString, FString, Data);
};

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
	FSentryUserInfo User;

	UPROPERTY()
	TMap<FString, FString> Tags;

	SENTRY_SETTER(FSentryApplicationInfo, FString, Distribution);
	SENTRY_SETTER(FSentryApplicationInfo, FString, Environment);
	SENTRY_SETTER(FSentryApplicationInfo, FString, Release);
	SENTRY_SETTER(FSentryApplicationInfo, FString, ServerName);
	SENTRY_SETTER(FSentryApplicationInfo, FSentryUserInfo, User);
	SENTRY_SETTER_MAP(FSentryApplicationInfo, FString, FString, Tags);
};