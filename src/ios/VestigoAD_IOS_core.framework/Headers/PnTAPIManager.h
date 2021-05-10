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
#import "PnTUserDefaults.h"
#import "PnTUtil.h"

NS_ASSUME_NONNULL_BEGIN

@protocol PnTAPIManagerDelegate <NSObject>
@optional
- (void) onGetAPITokenResultWith: (BOOL) success newApiToken: (NSString *)token newScope: (NSString *)scope;
@optional
- (void) onGetBeaconSpecWith: (BOOL) success uuid: (NSString *)uuid major: (NSInteger)major minor: (NSInteger)minor;
@optional
- (void) onUploadPositionResultWith: (BOOL) success;
@optional
- (void) onGetCompanyInfoResultWith: (BOOL) success lat: (double)lat lng: (double)lng;
@end



@interface PnTAPIManager : NSObject

+ (PnTAPIManager *)sharedInstance;

/**
 처음 APImanager 인스턴스 생성시 생성자 with
  @oAuthDomain: oAuth 서버 주소
  @apiDomain : api 서버 주소
 */
+ (PnTAPIManager *)initInstanceWith: (NSString *)oAuthDomain apiDomain: (NSString *)apiDomain;

@property BOOL readyForAPIs;
@property NSString *oAuthDomain;
@property NSString *apiDomain;
@property id<PnTAPIManagerDelegate> delegate;

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
