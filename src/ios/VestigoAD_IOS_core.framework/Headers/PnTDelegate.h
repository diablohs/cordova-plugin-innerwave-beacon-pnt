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
 * Vestigo ios SDK 에서 구동 결과에 대해 피드백이 전달됩니다.
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
