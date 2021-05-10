//
//  UserDefaults.h
//  RestkitTest
//
//  Created by SungKue.Jeon on 2020/12/22.
//  Copyright © 2020 pnt. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "APIAuthentication.h"
#import "UserIdentity.h"

NS_ASSUME_NONNULL_BEGIN

@interface PnTUserDefaults : NSObject
+ (NSString *)PREF_KEY_API_DOMAIN;
+ (NSString *)UD_KEY_API_TOKEN;
+ (NSString *)UD_KEY_SCOPE_UUID;
+ (NSString *)UD_KEY_B_UUID_SELF;
+ (NSString *)UD_KEY_B_MAJOR_SELF;
+ (NSString *)UD_KEY_B_MINOR_SELF;

+ (void) putOAuthUrl: (NSString *)oAuthUrl;
+ (NSString *) getOAuthUrl;
+ (void) putAPIDomain: (NSString *)apiDomain;
+ (NSString *) getAPIDomain;
+ (void) putAPIToken: (NSString *)apiToken;
+ (NSString *) getAPIToken;
+ (void) putScopeUUID: (NSString *)scopeUUID;
+ (NSString *) getScopeUUID;
+ (void) putBeaconUUIDSelf: (NSString *)uuid;
+ (NSString *) getBeaconUUIDSelf;
+ (void) putBeaconMajorSelf: (NSInteger)major;
+ (NSInteger) getBeaconMajorSelf;
+ (void) putBeaconMinorSelf: (NSInteger)minor;
+ (NSInteger) getBeaconMinorSelf;

// for VestigoSettings
+ (void) putAutoStopOnExit: (BOOL)enable;
+ (BOOL) getAutoStopOnExit;
+ (void) putAutoStartOnEnter: (BOOL)enable;
+ (BOOL) getAutoStartOnEnter;
+ (void) putCompanyLocationLat: (double)lat;
+ (double) getCompanyLocationLat;
+ (void) putCompanyLocationLng: (double)lng;
+ (double) getCompanyLocationLng;
+ (void) putBoundaryRadius: (double)lng;
+ (double) getBoundaryRadius;

// for APIAuthentication
+ (BOOL) storeAPIAuthentication: (APIAuthentication *)apiAuthentication;
+ (APIAuthentication *) restoreAPIAuthentication;

// for UserIdentity
+ (BOOL) storeUserIdentity: (UserIdentity *)userIdentity;
+ (UserIdentity *) restoreUserIdentity;

// for External Params dic
+ (BOOL) storeExternalParamsDic: (NSDictionary *)externalParamsdic;
+ (NSDictionary *) restoreExternalParamsDic;

#pragma : base function

+ (void)putWithKey:(NSString *)key strValue:(NSString * )strValue;
+ (NSString * _Nullable)getStrValueWith:(NSString *)key;
+ (void)putWithKey:(NSString *)key intValue:(NSInteger)value;
+ (NSInteger)getIntegerValueWith:(NSString *)key defaultValue:(int)defaultValue;


@end

NS_ASSUME_NONNULL_END
