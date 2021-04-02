//
//  APIManager.h
//  RestkitTest
//
//  Created by SungKue.Jeon on 2020/12/21.
//  Copyright © 2020 pnt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PnTLogger.h"
#import "APIAuthentication.h"
#import "UserDefaults.h"
#import "Util.h"

NS_ASSUME_NONNULL_BEGIN

@protocol APIManagerDelegate <NSObject>
@optional
- (void) onGetAPITokenResultWith: (BOOL) success newApiToken: (NSString *)token newScope: (NSString *)scope;
@optional
- (void) onGetBeaconSpecWith: (BOOL) success uuid: (NSString *)uuid major: (NSInteger)major minor: (NSInteger)minor;
@optional
- (void) onUploadPositionResultWith: (BOOL) success;
@optional
- (void) onGetCompanyInfoResultWith: (BOOL) success lat: (double)lat lng: (double)lng;
@end



@interface APIManager : NSObject

+ (APIManager *)sharedInstance;

/**
 처음 APImanager 인스턴스 생성시 생성자 with
  @oAuthDomain: oAuth 서버 주소
  @apiDomain : api 서버 주소
 */
+ (APIManager *)initInstanceWith: (NSString *)oAuthDomain apiDomain: (NSString *)apiDomain;

@property BOOL readyForAPIs;
@property NSString *oAuthDomain;
@property NSString *apiDomain;
@property id<APIManagerDelegate> delegate;

- (void) getAPITokenWith: (NSString *)client_id client_secret: (NSString *)client_secret scope:(NSString *) uuidForScope;
- (void) getAdBeaconSpecWith: (NSString *)scopeUUID targetId: (NSString *)targetId targetName: (NSString *)targetName;
- (void) getAdBeaconSpecWith: (NSString *)scopeUUID targetId: (NSString *)targetId targetName: (NSString *)targetName externalDic: (NSDictionary *)externalDic;
- (void) getCompanyInfoWith: (NSString *)scopeUUID;
- (void) uploadPositionInfoWith: (NSString *)myBeaconSpecId hostBeaconSpecId: (NSString *)hostBeaconSpecId;
- (void) requestTagUnMapping: (NSString *) targetId;

- (void) HTTPGetJSON: (NSString *)url reqId: (NSInteger)reqId;
- (void) HTTPPostJSONWithURL: (NSString *)url jsonObj:(NSObject *)jsonObj reqId: (NSInteger)reqId;













@end




NS_ASSUME_NONNULL_END
