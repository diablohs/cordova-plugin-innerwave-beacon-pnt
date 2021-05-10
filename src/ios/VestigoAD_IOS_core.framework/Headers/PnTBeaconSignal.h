//
//  BeaconSignal.h
//  VestigoAD_IOS_core
//
//  Created by SungKue.Jeon on 2020/12/30.
//

#import <Foundation/Foundation.h>
#import "PnTLogger.h"
NS_ASSUME_NONNULL_BEGIN

@interface PnTBeaconSignal : NSObject

@property NSString *uuid;
@property NSInteger major;
@property NSInteger minor;
@property NSInteger lastRssi;
@property NSInteger averageRssi;


- (instancetype)initWithUUID:(NSString *)uuid major:(NSInteger)major minor: (NSInteger)minor rssi:(NSInteger)rssi;
- (void)updateRssi: (NSInteger)newRssi;
- (NSString *)toBeaconId;
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
