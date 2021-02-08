//
//  LocationManager.h
//  PnTMonitoringFramework
//
//  Created by pnt on 2020/11/12.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "PnTDelegate.h"
#import "PnTLogger.h"
#import "APIManager.h"
#import "APIAuthentication.h"
#import "UserIdentity.h"
#import "VestigoSettings.h"
#import "UserDefaults.h"
#import "Util.h"
#import "SignalManager.h"

@class PnTVestigoManager;

@interface PnTVestigoManager : NSObject <APIManagerDelegate>

+ (instancetype)sharedInstance;
/**
 SDK state
 */
typedef NS_ENUM(NSInteger, VESTIGO_STATE) {
    STATE_NONE, // none
    STATE_SET_PARAM,    // params set
    STATE_AUTHENTICATING, // App called start SDK
    STATE_GETTING_SPEC,    // got the api token from API server
    STATE_GOT_SPEC, // got the ibeacon spec
    STATE_REGISTER_AUTO,  // registered for auto start / stop
    STATE_MONITORING,   // vestigo monitoring started (all to go)
};

@property (strong, nonatomic) CLLocationManager *locationManager;


// 현재 Vestigo SDK state
@property (nonatomic) VESTIGO_STATE currentState;
// 현 단말의 구분자 파라미터
@property (nonatomic) UserIdentity *userIdentity;
// 추가적인 파라미터 맵
@property (nonatomic, strong) NSDictionary *externalParamsDic;
// api 인증 파라미터
@property (nonatomic) APIAuthentication *apiAuthentication;
// Settings
@property (nonatomic) VestigoSettings *settings;

// Vestigo SDK 동작 피드백를 받을 delegate
@property (nonatomic, strong) id<PnTVestigoDelegate> pntVestigoDelegate;

//@property (nonatomic, strong) id<PnTADResultScanBeaconDelegate> pntADResultScanBeaconDelegate;

/**
* Vestigo ios SDK 를 사용하기 전에 필수 파라미터 들을 set 합니다.
* @param apiAuthentication : 인증에 필요한 파라미터셋
* @param userIdentity : 사용자/단말의 구분자
*/
- (void)setParameterInfoWith: (APIAuthentication *)apiAuthentication userIdentity: (UserIdentity *)userIdentity;
/**
 추가적인 파라미터들을 add 합니다.
 @param paramsDic : 추가적인 파라미터들.
 */
- (void)addExternalParameters: (NSDictionary * __nonnull)paramsDic;
/**
 추가적인 세팅사항들을 설정합니다.
 @param settings : 추가적인 세팅사항들.
 */
- (void) addSettings: (VestigoSettings * __nonnull)settings;
/**
* Vestigo ios SDK 서비스를 시작합니다. (결과 및 피드백은 PnTVestigoDelegate 로 전해집니다.)
*/
- (void) startVestigoService;

/**
* Vestigo monitoring service 를 종료합니다.
*/
- (void) stopVestigoService;
/**
* Vestigo monitoring service 가 이미 등록되어 있는지 여부를 검사합니다.
*/
- (BOOL) isPntVestigoServiceRegistered;
/**
* Vestigo Framework 내부에서 출력하는 로그를 enable/disable합니다.
*/
- (void)setDebugEnable:(BOOL)enable;

/**
* Vestigo Monitoring 서비스를 앱 포그라운드 에서도 동작할지 여부를 결정합니다.
*/
- (void)setVestigoForegroundEnable:(BOOL)enable;
/**
* Vestigo SDK 서비스의 결과 및 피드백을 받을 Delegate 를 등록합니다.
*/
- (void)setVestigoLogDelegate:(id<PnTVestigoLogDelegate>) pntADLogDelegate;

- (void)terminateApplication;
//    - (void)setResultScanBeaconDelegate:(id<PntResultScanBeaconDelegate>) pntResultScanBeaconDelegate;
//    - (void)setMonitoringUUIDs:(NSArray *)uuids;

@end
