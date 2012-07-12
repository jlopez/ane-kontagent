//
//  KontagentLib.mm
//  KontagentLib
//
//  Created by Jesus Lopez on 05/07/2012
//  Copyright (c) 2012 JLA. All rights reserved.
//
#import "Kontagent.h"
#import "NativeLibrary.h"

@interface KontagentLib : NativeLibrary {
@private
  BOOL sessionStarted;
}

@end

@interface ASObject (KTAdditions)

- (KTParamMap *)ktParamMapWithKeys:(NSArray *)keys;

@end

@implementation KontagentLib

FN_BEGIN(KontagentLib)
  FN(libraryVersion, libraryVersion)
  FN(initialize, initializeWithApiKey:userId:useTestServer:)
  FN(trackApplicationAdded, applicationAdded:optionalParamsKeys:)
  FN(trackEvent, customEvent:optionalParams:optionalParamsKeys:)
  FN(trackGoalCount, goalCount:value:)
  FN(trackInviteSent, inviteSent:trackingId:optionalParams:optionalParamsKeys:)
  FN(trackInviteResponse, inviteResponse:trackingId:optionalParams:optionalParamsKeys:)
  FN(trackPageRequest, pageRequest:optionalParamsKeys:)
  FN(trackRevenue, revenueTracking:optionalParams:optionalParamsKeys:)
  FN(trackStreamPost, streamPost:trackingId:optionalParams:optionalParamsKeys:)
  FN(trackStreamPostResponse, streamPostResponse:type:trackingId:optionalParams:optionalParamsKeys:)
  FN(trackThirdPartyCommClick, undirectedCommunicationClick:type:optionalParams:optionalParamsKeys:)
  FN(trackThirdPartyCommClickTag, undirectedCommunicationClick:type:trackingTag:optionalParams:optionalParamsKeys:)
  FN(trackNotificationEmailSent, emailSent:trackingId:optionalParams:optionalParamsKeys:)
  FN(trackNotificationEmailResponse, emailResponse:trackingId:optionalParams:optionalParamsKeys:)
  FN(trackUserInformation, userInformation:optionalParamsKeys:)
  FN(sendDeviceInformation, sendDeviceInformation:optionalParamsKeys:)
  FN(genUniqueTrackingTag, generateUniqueTrackingTag)
  FN(enableDebug, enableDebug)
  FN(disableDebug, disableDebug)
  FN(debugEnabled, debugEnabled)
  FN(senderId, senderId)
FN_END

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  NSBundle *bundle = [NSBundle mainBundle];
  NSString *apiKey = [bundle objectForInfoDictionaryKey:@"KTAPIKey"];
  NSString *mode = [bundle objectForInfoDictionaryKey:@"KTMode"];
  if (apiKey || mode) {
    NSAssert(apiKey, @"Missing Kontagent API Key");
    NSAssert(mode, @"Missing Kontagent Mode (production/test)");
    BOOL isProduction = [mode caseInsensitiveCompare:@"production"] == NSOrderedSame;
    BOOL isTest = [mode caseInsensitiveCompare:@"test"] == NSOrderedSame;
    NSAssert1(isProduction || isTest, @"Invalid Kontagent Mode '%@'", mode);
    ANELog(@"Auto-initializing Kontagent(%@,%@)", apiKey, mode);
    [Kontagent startSession:apiKey
                   senderId:nil
                       mode:isProduction ? kKontagentSDKMode_PRODUCTION : kKontagentSDKMode_TEST
shouldSendApplicationAddedAutomatically:YES];
    sessionStarted = YES;
  }
  return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
  if (sessionStarted) {
    [Kontagent stopSession];
    sessionStarted = NO;
  }
}

- (void)initializeWithApiKey:(NSString *)apiKey userId:(NSString *)userId useTestServer:(BOOL)useTestServer {
  NSUInteger mode = useTestServer ? kKontagentSDKMode_TEST : kKontagentSDKMode_PRODUCTION;
  [Kontagent startSession:apiKey senderId:userId mode:mode shouldSendApplicationAddedAutomatically:NO];
  sessionStarted = YES;
}

- (NSString *)libraryVersion {
  return [Kontagent libraryVersion];
}

- (void)applicationAdded:(ASObject *)params optionalParamsKeys:(NSArray *)keys {
  [Kontagent applicationAdded:[params ktParamMapWithKeys:keys]];
}

- (void)customEvent:(NSString *)event optionalParams:(ASObject *)params optionalParamsKeys:(NSArray *)keys {
  [Kontagent customEvent:event optionalParams:[params ktParamMapWithKeys:keys]];
}

- (void)goalCount:(NSInteger)aGoalCountId value:(NSInteger)aValue {
  [Kontagent goalCount:aGoalCountId value:aValue];
}

- (void)inviteSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(ASObject*)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent inviteSent:aRecipientUIDs trackingId:anUniqueTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)inviteResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(ASObject*)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent inviteResponse:anApplicationInstalled trackingId:anUniqueTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)pageRequest:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent pageRequest:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)revenueTracking:(NSInteger)aValue optionalParams:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent revenueTracking:aValue optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)streamPost:(NSString*)aType trackingId:(NSString*)anUniqueTrackingTag optionalParams:(ASObject *)anOptionalParams  optionalParamsKeys:(NSArray *)keys {
  [Kontagent streamPost:aType trackingId:anUniqueTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)streamPostResponse:(BOOL)anApplicationInstalled type:(NSString*)aType 
                trackingId:(NSString*)anUniqueTrackingTag optionalParams:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent streamPostResponse:anApplicationInstalled type:aType trackingId:anUniqueTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType optionalParams:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent undirectedCommunicationClick:anApplicationInstalled type:aType optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType trackingTag:(NSString*)aTrackingTag optionalParams:(ASObject*)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent undirectedCommunicationClick:anApplicationInstalled type:aType trackingTag:aTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)emailSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent emailSent:aRecipientUIDs trackingId:anUniqueTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)emailResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent emailResponse:anApplicationInstalled trackingId:anUniqueTrackingTag optionalParams:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)userInformation:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent userInformation:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (void)sendDeviceInformation:(ASObject *)anOptionalParams optionalParamsKeys:(NSArray *)keys {
  [Kontagent sendDeviceInformation:[anOptionalParams ktParamMapWithKeys:keys]];
}

- (NSString*)generateUniqueTrackingTag {
  return [Kontagent generateUniqueTrackingTag];
}

- (void)enableDebug {
  [Kontagent enableDebug];
}

- (void) disableDebug {
  [Kontagent disableDebug];
}

- (BOOL)debugEnabled {
  return [Kontagent debugEnabled];
}

- (NSString*)senderId {
  NSBundle *bundle = [NSBundle mainBundle];
  NSString *apiKey = [bundle objectForInfoDictionaryKey:@"KTAPIKey"];
  return [Kontagent getSenderId:apiKey];
}

@end

@implementation ASObject (KTAdditions)

- (KTParamMap *)ktParamMapWithKeys:(NSArray *)keys {
  KTParamMap *rv = [KTParamMap new];
  rv.parameters = [self dictionaryWithProperties:keys, nil];
  return [rv autorelease];
}

@end
