//
//  PntDelegate.h
//  PnTMonitoringFramework
//
//  Created by pnt on 2020/11/25.
//

#import <CoreLocation/CoreLocation.h>
#import "VestigoResult.h"

/**
 PnTVestigoDelegate : PnTVestigo 서비스의 결과를 전달하는 Delegate
 */
@protocol PnTVestigoDelegate <NSObject>

/**
 * Vestigo ios SDK 를 사용하기 전에 필수 파라미터 들을 set 합니다.
 * @param result : VestigoResult.
 */
@optional
 -(void)onVestigoResult:(VestigoResult *)result;

///**
//@optional
//-(void)onDidEnterSite;
///**
//@optional
//-(void)onDidExitSite;

@end

@protocol PnTVestigoLogDelegate <NSObject>
@optional
 -(void)log:(NSInteger)code message:(NSString *)message;
@end

//@protocol PnTADResultScanBeaconDelegate <NSObject>
//@optional
// -(void)scanBeacon:(CLBeacon*)clBeacon;
//@end
