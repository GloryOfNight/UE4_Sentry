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

FSentryApplicationInfo& FSentryApplicationInfo::SetPlatform(const FString& Value)
{
	Platform = Value;
	return *this;
}

FSentryApplicationInfo& FSentryApplicationInfo::SetPlatform(FString&& Value)
{
	Platform = std::move(Value);
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
