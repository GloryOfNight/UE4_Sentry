#pragma once
#include "Sentry/Event/Exception.h"
#include "Sentry/Event/LogEntry.h"
#include "Sentry/Event/SentryCommon.h"
#include "Sentry/Types/ApplicationInfo.h"

#include "SentryJson.generated.h"

USTRUCT()
struct FSentryEvent_Exception_Json
{
	GENERATED_BODY()

	FSentryEvent_Exception_Json() = default;

	FSentryEvent_Exception_Json(const FSentryException& Value);
	FSentryEvent_Exception_Json(FSentryException&& Value);

	UPROPERTY()
	FString module;

	UPROPERTY()
	FString thread_id;

	UPROPERTY()
	FString type;

	UPROPERTY()
	FString value;
};

USTRUCT()
struct FSentryEvent_LogEntry_Json
{
	GENERATED_BODY()

	FSentryEvent_LogEntry_Json() = default;

	FSentryEvent_LogEntry_Json(const FSentryLogEntry& Value);
	FSentryEvent_LogEntry_Json(FSentryLogEntry&& Value);

	UPROPERTY()
	FString message;

	UPROPERTY()
	TArray<FString> params;
};

USTRUCT()
struct FSentryEvent_Json
{
	GENERATED_BODY()

	FSentryEvent_Json();

	UPROPERTY()
	FString dist;

	UPROPERTY()
	FString environment;

	UPROPERTY()
	FString event_id;

	UPROPERTY()
	TArray<FSentryEvent_Exception_Json> exception;

	UPROPERTY()
	FString fingerprint;

	UPROPERTY()
	FString level;

	UPROPERTY()
	FSentryEvent_LogEntry_Json logentry;

	UPROPERTY()
	FString platform;

	UPROPERTY()
	FString received;

	UPROPERTY()
	FString release;

	UPROPERTY()
	FString server_name;

	UPROPERTY()
	int64 timestamp;

public:
	FString ToJson();

public:
	FSentryEvent_Json& SetException(const TArray<FSentryException>& Values);
	FSentryEvent_Json& SetException(TArray<FSentryException>&& Values);

	FSentryEvent_Json& SetLogEntry(const FSentryLogEntry& Value);
	FSentryEvent_Json& SetLogEntry(FSentryLogEntry&& Value);

	FSentryEvent_Json& SetLevel(const ESentryLevel& Value);

	FSentryEvent_Json& SetApplicationInfo(const FSentryApplicationInfo& Value);
};