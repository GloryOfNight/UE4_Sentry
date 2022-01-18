#pragma once

#include <UObject/Object.h>

#include "SentrySettings.generated.h"

UCLASS(Config = Engine)
class SENTRY_API USentrySettings : public UObject
{
	GENERATED_BODY()
public:
	static USentrySettings* Get();

public:
	/** DNS of Sentry project */
	UPROPERTY(Config, EditAnywhere, Category = "Sentry")
	FString DNS;

#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};