//
//  Util.h
//  VestigoAD_IOS_core
//
//  Created by SungKue.Jeon on 2020/12/23.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
NS_ASSUME_NONNULL_BEGIN

@interface PnTUtil : NSObject
+ (CLBeaconRegion *) buildBeaconRegionWith: (NSString *) uuid;
+ (NSMutableArray *)buildReplacementUUIDsWith: (NSString *)orgBeaconUUID;
+ (void) showLocalNotificationWith: (NSString *)title msg: (NSString *)msg;
@end

NS_ASSUME_NONNULL_END
