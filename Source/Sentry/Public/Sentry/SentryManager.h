#pragma once
#include <Interfaces/IHttpRequest.h>
#include <Interfaces/IHttpResponse.h>
#include <UObject/Object.h>

#include "Event/Exception.h"
#include "Event/LogEntry.h"
#include "Event/SentryCommon.h"
#include "Json/SentryJson.h"
#include "Types/ApplicationInfo.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSentryManager, Display, All);

class SENTRY_API FSentryManager
{
public:
	FSentryManager();

public:
	static FSentryManager* Get();

	FSentryApplicationInfo& ApplicationInfo();

	void SendException(const ESentryLevel::Type Level, const FSentryException& Value);

	void SendLogEntry(const ESentryLevel::Type Level, const FString& Message, TArray<FString>&& Params);

	void SendLogEntry(const ESentryLevel::Type Level, const FSentryLogEntry& Value);

	void SendEventJson(const FSentryEvent_Json& Value);
	void SendEventJson(FSentryEvent_Json&& Value);

	void SendJson(FString&& Json);

	bool LoadDSN(const FString& DSN, const bool Reset);

protected:
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

private:
	FString Url;
	FString Key;
};