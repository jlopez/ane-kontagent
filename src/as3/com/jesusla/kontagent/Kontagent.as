package com.jesusla.kontagent {
  import flash.data.EncryptedLocalStore;
  import flash.events.StatusEvent;
  import flash.external.ExtensionContext;
  import flash.utils.ByteArray;
  import flash.utils.getQualifiedClassName;
  import com.kontagent.KontagentApi;
  import com.kontagent.libs.adobe.crypto.Base64Encoder;

  /**
   * Kontagent extension
   */
  public class Kontagent {
    //---------------------------------------------------------------------
    //
    // Constants
    //
    //---------------------------------------------------------------------
    private static const EXTENSION_ID:String = "com.jesusla.kontagent";

    //---------------------------------------------------------------------
    //
    // Private Properties.
    //
    //---------------------------------------------------------------------
    private static var context:ExtensionContext;
    private static var _instance:Kontagent;
    private static var ktApi:KontagentApi;
    private static var _userId:Number;
    private static var _installed:Boolean;

    //---------------------------------------------------------------------
    //
    // Public Methods.
    //
    //---------------------------------------------------------------------
    public function Kontagent() {
      if (_instance)
        throw new Error("Singleton");
      _instance = this;
    }

    public static function get isSupported():Boolean {
      // We always fallback to AS3 if necessary
      return true;
    }

    public static function init(apiKey:String, userId:Object = null, useTestServer:Boolean = false):void {
      _userId = Number(userId);
      if (context == null)
        ktApi = new KontagentApi(apiKey);
      else
        context.call("initialize", apiKey, userId ? String(userId) : null, useTestServer);
    }

    public static function get libraryVersion():String {
      if (context == null)
        return "as3";
      return context.call("libraryVersion") as String;
    }

    public static function trackEvent(eventName:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (context != null) {
        optionalParams = formatParams(optionalParams);
        context.call("trackEvent", eventName, optionalParams);
      }
      else
        ktApi.trackEvent(_userId, eventName, optionalParams);
    }

    public static function trackApplicationAdded(optionalParams:Object = null):void {
      ensureInitialized();
      if (context != null) {
        optionalParams = formatParams(optionalParams);
        context.call("trackApplicationAdded", optionalParams);
      }
      else
        ktApi.trackApplicationAdded(_userId, optionalParams);
    }

    public static function trackGoalCount(optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackGoalCount(_userId, optionalParams);
    }

    public static function trackInviteSent(recipientUserIds:String, uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackInviteSent(_userId, recipientUserIds, uniqueTrackingTag, optionalParams);
    }

    public static function trackInviteResponse(uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackInviteResponse(uniqueTrackingTag, optionalParams);
    }

    public static function trackPageRequest(optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackPageRequest(_userId, optionalParams);
    }

    public static function trackRevenue(value:int, optionalParams:Object = null):void {
      ensureInitialized();
      if (context) {
        optionalParams = formatParams(optionalParams);
        context.call("trackRevenue", value, optionalParams);
      }
      else
        ktApi.trackRevenue(_userId, value, optionalParams);
    }

    public static function trackStreamPost(uniqueTrackingTag:String, type:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackStreamPost(_userId, uniqueTrackingTag, type, optionalParams);
    }

    public static function trackStreamPostResponse(uniqueTrackingTag:String, type:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackStreamPostResponse(uniqueTrackingTag, type, optionalParams);
    }

    public static function trackThirdPartyCommClick(type:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (context) {
        optionalParams = formatParams(optionalParams);
        context.call("trackThirdPartyCommClick", _installed, type, optionalParams);
      }
      else
        ktApi.trackThirdPartyCommClick(type, optionalParams);
    }

    public static function trackNotificationEmailSent(recipientUserIds:String, uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackNotificationEmailSent(_userId, recipientUserIds, uniqueTrackingTag, optionalParams);
    }

    public static function trackNotificationEmailResponse(uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackNotificationEmailResponse(uniqueTrackingTag, optionalParams);
    }

    public static function trackUserInformation(optionalParams:Object = null):void {
      ensureInitialized();
      if (!context)
        ktApi.trackUserInformation(_userId, optionalParams);
    }

    public static function sendDeviceInformation(optionalParams:Object = null):void {
      if (!context)
        return
      optionalParams = formatParams(optionalParams);
      context.call("sendDeviceInformation", optionalParams);
    }

    public static function genUniqueTrackingTag():String {
      ensureInitialized();
      if (context)
        return context.call("genUniqueTrackingTag") as String;
      else
        return ktApi.genUniqueTrackingTag();
    }

    public static function genShortUniqueTrackingTag():String {
      ensureInitialized();
      return ktApi.genShortUniqueTrackingTag();
    }

    public static function enableDebug():void {
      if (context)
        context.call("enableDebug");
    }

    public static function disableDebug():void {
      if (context)
        context.call("disableDebug");
    }

    public static function get debugEnabled():Boolean {
      return context != null && context.call("debugEnabled");
    }

    public static function get userId():String {
      if (context != null)
        return context.call("senderId") as String;
      return String(_userId);
    }

    public function getQualifiedClassName(obj:Object):String {
      return flash.utils.getQualifiedClassName(obj);
    }

    public function enumerateObjectProperties(obj:Object):Array {
      var keys:Array = [];
      for (var key:String in obj)
        keys.push(key);
      return keys;
    }

    private static var _objectPool:Object = {};
    private static var _objectPoolId:int = 0;
    public function __retainObject(obj:Object):int {
      _objectPool[++_objectPoolId] = obj;
      return _objectPoolId;
    }

    public function __getObject(id:int):Object {
      return _objectPool[id];
    }

    //---------------------------------------------------------------------
    //
    // Internal (package level) Methods.
    //
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    //
    // Private Methods.
    //
    //---------------------------------------------------------------------
    private static function base64Encode(data:String):String {
      var b64:Base64Encoder = new Base64Encoder();
      b64.encode(data);
      return b64.toString();
    }

    private static function formatParams(optionalParams:Object):Object {
      if (optionalParams == null)
        return null;

      var params:Object = {}
      if (optionalParams.birthYear) { params.b = optionalParams.birthYear; }
      if (optionalParams.country) { params.lc = optionalParams.country.toUpperCase(); }
      if (optionalParams.data) { params.data = base64Encode(optionalParams.data); }
      if (optionalParams.friendCount) { params.f = optionalParams.friendCount; }
      if (optionalParams.gender) { params.g = optionalParams.gender; }
      if (optionalParams.goalCount1) { params.gc1 = optionalParams.goalCount1; }
      if (optionalParams.goalCount2) { params.gc2 = optionalParams.goalCount2; }
      if (optionalParams.goalCount3) { params.gc3 = optionalParams.goalCount3; }
      if (optionalParams.goalCount4) { params.gc4 = optionalParams.goalCount4; }
      if (optionalParams.ipAddress) { params.ip = optionalParams.ipAddress; }
      if (optionalParams.level != undefined) { params.l = optionalParams.level; }
      if (optionalParams.pageAddress) { params.u = optionalParams.pageAddress; }
      if (optionalParams.recipientUserId) { params.r = optionalParams.recipientUserId; }
      if (optionalParams.shortUniqueTrackingTag) { params.su = optionalParams.shortUniqueTrackingTag; }
      if (optionalParams.subtype1) { params.st1 = optionalParams.subtype1; }
      if (optionalParams.subtype1) { params.st1 = optionalParams.subtype1; }
      if (optionalParams.subtype2) { params.st2 = optionalParams.subtype2; }
      if (optionalParams.subtype3) { params.st3 = optionalParams.subtype3; }
      if (optionalParams.type) { params.tu = optionalParams.type; }
      if (optionalParams.uniqueTrackingTag) { params.u = optionalParams.uniqueTrackingTag; }
      if (optionalParams.userId) { params.s = optionalParams.userId; }
      if (optionalParams.value) { params.v = optionalParams.value; }
      return params;
    }

    private static function ensureInitialized():void {
      if (context == null && ktApi == null)
        throw new Error("Kontagent not initialized");
    }

    private static const ELS_KT_FIRST_RUN:String = "KT_FIRST_RUN";
    private static function isFirstRun():Boolean {
      // May only be called when run on a device
      if (!EncryptedLocalStore.isSupported)
        throw new Error("Unsupported");
      var ba:ByteArray = EncryptedLocalStore.getItem(ELS_KT_FIRST_RUN);
      var firstRun:Boolean = ba == null;
      if (firstRun) {
        ba = new ByteArray();
        ba.writeBoolean(true);
        EncryptedLocalStore.setItem(ELS_KT_FIRST_RUN, ba);
      }
      return firstRun;
    }

    private static function context_statusEventHandler(event:StatusEvent):void {
      if (event.level == "TICKET")
        context.call("claimTicket", event.code);
      else if (event.level == "RELEASE")
        delete _objectPool[int(event.code)];
    }

    {
      new Kontagent();
      context = ExtensionContext.createExtensionContext(EXTENSION_ID,
          EXTENSION_ID + ".KontagentLib");
      if (context) {
        try {
          context.addEventListener(StatusEvent.STATUS, context_statusEventHandler);
          context.call("setActionScriptThis", _instance);
          _installed = isFirstRun();
        } catch (e:ArgumentError) {
          context = null;
        }
      }
    }
  }
}
