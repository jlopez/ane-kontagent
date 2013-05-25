//
//  KontagentLib.mm
//  KontagentLib
//
//  Created by Jesus Lopez on 05/07/2012
//  Copyright (c) 2012 JLA. All rights reserved.
//
#import "Kontagent.h"
#import "NativeLibrary.h"
#import <CommonCrypto/CommonDigest.h>

@interface KontagentLib : NativeLibrary {
@private
  BOOL sessionStarted;
  NSString *apiKey;
}

@end

@interface KTParamMap (NLAdditions)

+ (KTParamMap *)ktParamMapFromDictionary:(NSDictionary *)dict;

@end

@implementation KontagentLib

FN_BEGIN(KontagentLib)
  FN(libraryVersion, libraryVersion)
  FN(initialize, initializeWithApiKey:userId:useTestServer:)
  FN(trackApplicationAdded, applicationAdded:)
  FN(trackEvent, customEvent:optionalParams:)
  FN(trackGoalCount, goalCount:value:)
  FN(trackInviteSent, inviteSent:trackingId:optionalParams:)
  FN(trackInviteResponse, inviteResponse:trackingId:optionalParams:)
  FN(trackPageRequest, pageRequest:)
  FN(trackRevenue, revenueTracking:optionalParams:)
  FN(trackStreamPost, streamPost:trackingId:optionalParams:)
  FN(trackStreamPostResponse, streamPostResponse:type:trackingId:optionalParams:)
  FN(trackThirdPartyCommClick, undirectedCommunicationClick:type:optionalParams:)
  FN(trackThirdPartyCommClickTag, undirectedCommunicationClick:type:trackingTag:optionalParams:)
  FN(trackNotificationEmailSent, emailSent:trackingId:optionalParams:)
  FN(trackNotificationEmailResponse, emailResponse:trackingId:optionalParams:)
  FN(trackUserInformation, userInformation:)
  FN(sendDeviceInformation, sendDeviceInformation:)
  FN(genUniqueTrackingTag, generateUniqueTrackingTag)
  FN(enableDebug, enableDebug)
  FN(disableDebug, disableDebug)
  FN(debugEnabled, debugEnabled)
  FN(senderId, senderId)

  FN(resumeSession, resumeSession)
  FN(pauseSession, pauseSession)
  FN(stopSession, stopSession)
FN_END

- (void)dealloc {
  [apiKey release];
  [super dealloc];
}

static NSString *md5_hash(NSString *s) {
  // Create pointer to the string as UTF8
  const char *ptr = [s UTF8String];

  // Create byte array of unsigned chars
  unsigned char md5Buffer[CC_MD5_DIGEST_LENGTH];

  // Create 16 byte MD5 hash value, store in buffer
  CC_MD5(ptr, strlen(ptr), md5Buffer);

  // Convert MD5 value in the buffer to NSString of hex values
  NSMutableString *output = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
  for(int i = 0; i < CC_MD5_DIGEST_LENGTH; i++)
    [output appendFormat:@"%02x",md5Buffer[i]];

  return output;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  NSBundle *bundle = [NSBundle mainBundle];
  apiKey = [[bundle objectForInfoDictionaryKey:@"KTAPIKey"] copy];
  if (apiKey) {
    BOOL isTest = [[bundle objectForInfoDictionaryKey:@"KTTestMode"] boolValue];
    ANELog(@"Auto-initializing Kontagent(%@,%@)", apiKey, isTest ? @"Test" : @"Production");
    [Kontagent startSession:apiKey
                   senderId:nil
                       mode:isTest ? kKontagentSDKMode_TEST : kKontagentSDKMode_PRODUCTION
shouldSendApplicationAddedAutomatically:YES];
  }
  if ([[bundle objectForInfoDictionaryKey:@"KTDebug"] boolValue])
    [Kontagent enableDebug];
  return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
  if (apiKey) {
    [Kontagent stopSession];
    [apiKey release];
    apiKey = nil;
  }
}

- (void)initializeWithApiKey:(NSString *)apiKey_ userId:(NSString *)userId useTestServer:(BOOL)useTestServer {
  if (apiKey) {
    //  Ignoring as this will crash Kontagent 1.2.1 after 30s
    NSLog(@"KontagentLib: Session already initialized. Ignoring.");
    return;
  }
  NSUInteger mode = useTestServer ? kKontagentSDKMode_TEST : kKontagentSDKMode_PRODUCTION;
  apiKey = [apiKey_ copy];
  [Kontagent startSession:apiKey senderId:userId mode:mode shouldSendApplicationAddedAutomatically:NO];
}

- (void)resumeSession {}
- (void)pauseSession {}
- (void)stopSession {}

- (NSString *)libraryVersion {
  return [Kontagent libraryVersion];
}

- (void)applicationAdded:(NSDictionary *)params {
  [Kontagent applicationAdded:[KTParamMap ktParamMapFromDictionary:params]];
}

- (void)customEvent:(NSString *)event optionalParams:(NSDictionary *)params {
  [Kontagent customEvent:event optionalParams:[KTParamMap ktParamMapFromDictionary:params]];
}

- (void)goalCount:(NSInteger)aGoalCountId value:(NSInteger)aValue {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)inviteSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(NSDictionary*)anOptionalParams {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)inviteResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(NSDictionary*)anOptionalParams  {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)pageRequest:(NSDictionary *)anOptionalParams {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)revenueTracking:(NSInteger)aValue optionalParams:(NSDictionary *)anOptionalParams {
  [Kontagent revenueTracking:aValue optionalParams:[KTParamMap ktParamMapFromDictionary:anOptionalParams]];
}

- (void)streamPost:(NSString*)aType trackingId:(NSString*)anUniqueTrackingTag optionalParams:(NSDictionary *)anOptionalParams {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)streamPostResponse:(BOOL)anApplicationInstalled type:(NSString*)aType
                trackingId:(NSString*)anUniqueTrackingTag optionalParams:(NSDictionary *)anOptionalParams {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType optionalParams:(NSDictionary *)anOptionalParams {
  [Kontagent undirectedCommunicationClick:anApplicationInstalled type:aType optionalParams:[KTParamMap ktParamMapFromDictionary:anOptionalParams]];
}

- (void)undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType trackingTag:(NSString*)aTrackingTag optionalParams:(NSDictionary*)anOptionalParams {
  [Kontagent undirectedCommunicationClick:anApplicationInstalled type:aType trackingTag:aTrackingTag optionalParams:[KTParamMap ktParamMapFromDictionary:anOptionalParams]];
}

- (void)emailSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(NSDictionary *)anOptionalParams {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)emailResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(NSDictionary *)anOptionalParams  {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)userInformation:(NSDictionary *)anOptionalParams {
  ANELog(@"%s: Unimplemented", __PRETTY_FUNCTION__);
}

- (void)sendDeviceInformation:(NSDictionary *)anOptionalParams {
  [Kontagent sendDeviceInformation:[KTParamMap ktParamMapFromDictionary:anOptionalParams]];
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
  return [Kontagent getSenderId:apiKey];
}

@end

@implementation KTParamMap (NLAdditions)

+ (KTParamMap *)ktParamMapFromDictionary:(NSDictionary *)dict {
  KTParamMap *rv = [KTParamMap new];
  for (NSString *key in dict) {
    id obj = [dict objectForKey:key];
    [rv.parameters setObject:[obj description] forKey:key];
  }
  return [rv autorelease];
}

@end
