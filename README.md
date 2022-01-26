# Unreal Engine 4 - Sentry
Unreal Engine 4 integration of [Sentry](https://sentry.io/) monitoring

Plugin utilizes Sentry HTTP API to send Events data to your DSN.

Plugin was build and tested on 4.27.* version of engine.
Generaly it should work fine with most of engine versions and all platforms, since its utilizes HTTP and Json modules that well supported and do not change much.

## Supported Event parts
* [x] Send Exceptions (stands for generals errors) [more info](https://develop.sentry.dev/sdk/event-payloads/types/#exception)
* [x] Send Log Entry (log message for sentry) [more info](https://develop.sentry.dev/sdk/event-payloads/types/#logentry)
* [x] Dist, Env, Release, ServerName - can be applied to each event
* [X] Tags
* [X] User [more info](https://develop.sentry.dev/sdk/event-payloads/types/#user)
* [X] Geo [more info](https://develop.sentry.dev/sdk/event-payloads/types/#geo)
* [ ] Breadcrumbs [more info](https://develop.sentry.dev/sdk/event-payloads/types/#typedef-Breadcrumbs)
* [ ] Partial or full BP support 

## Support
Checkout [wiki](https://github.com/GloryOfNight/UE4_Sentry/wiki) section for documentation and API examples. 

If you found this plugin useful, please consider givind it a star (stars, yay!). 

If you encounter problems or have questions, please use Issues or Discussions section of this repo.

Feel free to submit your own work via Pull Requests.

Have a nice day!
