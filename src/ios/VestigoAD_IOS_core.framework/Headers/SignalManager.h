//
//  SignalManager.h
//  VestigoAD_IOS_core
//
//  Created by SungKue.Jeon on 2020/12/30.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "BeaconSignal.h"
#import "PnTLogger.h"

NS_ASSUME_NONNULL_BEGIN

@interface SignalManager : NSObject

@property (strong, nonatomic) NSMutableDictionary *averageDicById;


- (void) addCLBeaconSignal: (CLBeacon *)beacon;
- (BeaconSignal *) getStrongestBeacon;
- (BOOL) isEmpty;
- (void) clearAll;

@end

NS_ASSUME_NONNULL_END
