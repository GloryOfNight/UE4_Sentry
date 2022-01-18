#include "Sentry/SentryManager.h"

#include <Containers/UnrealString.h>
#include <Http.h>

#include "Sentry/Sentry.h"

DEFINE_LOG_CATEGORY(LogSentryManager);

static FSentryApplicationInfo AppInfo;

USentryManager::USentryManager()
	: UObject()
{
	if(!HasAllFlags(EObjectFlags::RF_ClassDefaultObject))
	{
		const FString& DNS = USentrySettings::Get()->DNS;
		if(!DNS.IsEmpty())
		{
			LoadDNS(DNS, false);
		}
		else
		{
			UE_LOG(LogSentryManager, Display, TEXT("No DNS provided, service will not work"));
		}
	}
}

USentryManager* USentryManager::Get()
{
	return FSentryModule::GetManager();
}

FSentryApplicationInfo& USentryManager::ApplicationInfo()
{
	return AppInfo;
}

void USentryManager::SendException(ESentryLevel Level, const FSentryException& Value)
{
	FSentryEvent_Json Event = FSentryEvent_Json()
								  .SetApplicationInfo(AppInfo)
								  .SetLevel(Level)
								  .SetException({Value});
	SendEventJson(std::move(Event));
}

void USentryManager::SendLogEntry(ESentryLevel Level, const FString Message, TArray<FString>&& Params)
{
	SendLogEntry(Level, {Message, std::move(Params)});
}

void USentryManager::SendLogEntry(ESentryLevel Level, const FSentryLogEntry& Value)
{
	FSentryEvent_Json Event = FSentryEvent_Json()
								  .SetApplicationInfo(AppInfo)
								  .SetLevel(Level)
								  .SetLogEntry(Value);
	SendEventJson(std::move(Event));
}

void USentryManager::SendEventJson(const FSentryEvent_Json& Value)
{
	SendJson(Value.ToJson());
}

void USentryManager::SendEventJson(FSentryEvent_Json&& Value)
{
	SendJson(Value.ToJson());
}

void USentryManager::SendJson(FString&& Json)
{
	if(!Url.IsEmpty() && !Key.IsEmpty())
	{
		UE_LOG(LogSentryManager, Error, TEXT("Cannot send, DNS not properly configured."))
		return;
	}
	FHttpModule* HttpModule = &FHttpModule::Get();
	FHttpRequestRef Request = HttpModule->CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("Accept", "application/json");

	const FString Auth = FString::Printf(TEXT("Sentry sentry_version=7, sentry_timestamp=%lld, sentry_key=%s"), FDateTime::UtcNow().ToUnixTimestamp(), *Key);
	Request->SetHeader("X-Sentry-Auth", Auth);
	Request->SetContentAsString(Json);

	Request->OnProcessRequestComplete().BindUObject(this, &USentryManager::OnProcessRequestComplete);
	Request->ProcessRequest();
}

bool USentryManager::LoadDNS(const FString& DNS, bool Reset)
{
	if(Reset)
	{
		Url = FString();
		Key = FString();
	}

	// 012345678.............................40....may vary.........
	// https://00112233445566778899aabbccddff00@sentry.companyname/0
	constexpr uint8 KeyLen = 32;
	constexpr uint8 KeyBegin = 8;
	constexpr uint8 KeyEnd = KeyBegin + KeyLen;

	int32 SlashIndex = INDEX_NONE;
	int32 AtIndex = INDEX_NONE;
	const bool IsValidDNS = DNS.Len() > 32 && DNS.FindLastChar('/', SlashIndex) && SlashIndex > KeyEnd &&
							DNS.FindLastChar('@', AtIndex) && AtIndex - KeyLen >= KeyBegin;

	if(IsValidDNS)
	{
		Key.Append(&DNS[KeyBegin], KeyLen);

		const FString Domain = FString(SlashIndex - (KeyEnd + 1), &DNS[KeyEnd + 1]);
		const FString Project = FString(&DNS[SlashIndex], DNS.Len() - SlashIndex);
		Url = TEXT("https://") + Domain + TEXT("/api") + Project + TEXT("/store/");

		UE_LOG(LogSentryManager, Display, TEXT("DNS load - ok"));
	}
	else
	{
		UE_LOG(LogSentryManager, Error, TEXT("DNS load - failed"));
	}

	return IsValidDNS;
}

void USentryManager::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
}