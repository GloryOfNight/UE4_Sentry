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
		FString DNS;
		GConfig->GetString(TEXT("Sentry"), TEXT("DNS"), DNS, GEngineIni);
		if(!DNS.IsEmpty())
		{
			if(LoadDNS(DNS))
			{
				UE_LOG(LogSentryManager, Display, TEXT("DNS load - ok"));
			}
			else
			{
				UE_LOG(LogSentryManager, Error, TEXT("DNS load - failed"));
			}
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

void USentryManager::SendEventJson(FSentryEvent_Json&& Value)
{
	SendJson(Value.ToJson());
}

void USentryManager::SendJson(FString&& Json)
{
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

bool USentryManager::LoadDNS(const FString& DNS)
{
	// 012345678.............................40....may vary.........
	// https://00112233445566778899aabbccddff00@sentry.companyname/0
	constexpr uint8 KeyBegin = 8;
	constexpr uint8 KeyLen = 32;
	constexpr uint8 KeyEnd = KeyBegin + KeyLen;

	int32 LastSlashIndex = INDEX_NONE;
	const bool IsValidDNS = DNS.Len() > 32 && DNS.FindLastChar('/', LastSlashIndex) && LastSlashIndex > KeyEnd;

	if(IsValidDNS)
	{
		Key.Append(&DNS[KeyBegin], KeyLen);

		const FString Domain = FString(LastSlashIndex - (KeyEnd + 1), &DNS[KeyEnd + 1]);
		const FString Project = FString(&DNS[LastSlashIndex], DNS.Len() - LastSlashIndex);
		Url = TEXT("https://") + Domain + TEXT("/api") + Project + TEXT("/store/");
	}

	return IsValidDNS;
}

void USentryManager::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
}