Kontagent ANE
=================

Usage
-----
Set KTAPIKey and KTMode (production/test) in Info.plist.

Call API methods on the AS3 Kontagent class:

        // Methods
        Kontagent.init(key, userId, testServer = false)
        Kontagent.trackEvent(name, params = null)
        Kontagent.trackApplicationAdded(params = null)
        Kontagent.trackGoalCount(params = null)
        Kontagent.trackInviteSent(ids, tag, params = null)
        Kontagent.trackInviteResponse(tag, params = null)
        Kontagent.trackPageRequest(params = null)
        Kontagent.trackRevenue(value, params = null)
        Kontagent.trackStreamPost(tag, type, params = null)
        Kontagent.trackStreamPostResponse(tag, type, params = null)
        Kontagent.trackThirdPartyCommClick(type, params = null)
        Kontagent.trackNotificationEmailSent(ids, tag, params = null)
        Kontagent.trackNotificationEmailResponse(trag, params = null)
        Kontagent.trackUserInformation(params = null)
        Kontagent.sendDeviceInformation(params = null)
        Kontagent.genUniqueTrackingTag()
        Kontagent.genShortUniqueTrackingTag()
        Kontagent.enableDebug()
        Kontagent.disableDebug()

        // Properties (read-only)
        Kontagent.isSupported
        Kontagent.libraryVersion
        Kontagent.debugEnabled
        Kontagent.userId

Mobile notes
============
A null user may be given to init(). Kontagent will use a randomly-generated
userId in all requests, or a previously non-null user if one was ever provided
to Kontagent in previous runs of the application.

Web notes
=========
sendDeviceInformation(), enableDebug() & disableDebug() are ignored
in web mode.
