//
//  SignalManager.h
//  VestigoAD_IOS_core
//
//  Created by SungKue.Jeon on 2020/12/30.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PnTBeaconSignal.h"
#import "PnTLogger.h"

NS_ASSUME_NONNULL_BEGIN

@interface PnTSignalManager : NSObject

@property (strong, nonatomic) NSMutableDictionary *averageDicById;


- (void) addCLBeaconSignal: (CLBeacon *)beacon;
- (PnTBeaconSignal *) getStrongestBeacon;
- (BOOL) isEmpty;
- (void) clearAll;

@end

NS_ASSUME_NONNULL_END
