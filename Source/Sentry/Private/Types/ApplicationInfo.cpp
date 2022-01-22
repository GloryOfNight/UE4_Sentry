#include "Sentry/Types/ApplicationInfo.h"

FSentryApplicationInfo& FSentryApplicationInfo::SetDistribution(const FString& Value)
{
	Distribution = Value;
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetDistribution(FString&& Value)
{
	Distribution = std::move(Value);
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetEnvironment(const FString& Value)
{
	Environment = Value;
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetEnvironment(FString&& Value)
{
	Environment = std::move(Value);
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetRelease(const FString& Value)
{
	Release = Value;
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetRelease(FString&& Value)
{
	Release = std::move(Value);
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetServerName(const FString& Value)
{
	ServerName = Value;
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetServerName(FString&& Value)
{
	ServerName = std::move(Value);
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetTags(const TMap<FString, FString>& Value)
{
	Tags = Value;
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetTags(TMap<FString, FString>&& Value)
{
	Tags = std::move(Value);
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::AddTag(const FString& Key, const FString& Value)
{
	Tags.Add(Key, Value);
	return *this;
}
