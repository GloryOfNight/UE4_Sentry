#pragma once
#include <Interfaces/IHttpRequest.h>
#include <Interfaces/IHttpResponse.h>
#include <UObject/Object.h>

#include "Event/Exception.h"
#include "Event/LogEntry.h"
#include "Event/SentryCommon.h"
#include "Json/SentryJson.h"
#include "Types/ApplicationInfo.h"

#include "SentryManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSentryManager, Display, All);

UCLASS()
class SENTRY_API USentryManager : public UObject
{
	GENERATED_BODY()
public:
	USentryManager();

public:
	static USentryManager* Get();

	FSentryApplicationInfo& ApplicationInfo();

	void SendException(ESentryLevel Level, const FSentryException& Value);

	void SendLogEntry(ESentryLevel Level, const FString Message, TArray<FString>&& Params);

	void SendLogEntry(ESentryLevel Level, const FSentryLogEntry& Value);

	void SendEventJson(const FSentryEvent_Json& Value);
	void SendEventJson(FSentryEvent_Json&& Value);

	void SendJson(FString&& Json);

	bool LoadDNS(const FString& DNS, bool Reset);

protected:
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

private:
	FString Url{};
	FString Key{};
};