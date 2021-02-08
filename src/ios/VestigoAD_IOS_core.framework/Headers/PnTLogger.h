//
//  NSLogger.h
//  PnTMonitoringFramework
//
//  Created by pnt on 2020/11/20.
//

#import <Foundation/Foundation.h>
#import "PnTDelegate.h"

@interface PnTLogger : NSObject

+(void)setDelegate:(id<PnTVestigoLogDelegate>)delegate;

+(BOOL)DEBUG_ENABLE_NOTI;
+(void)setDEBUG_ENABLE_NOTI:(BOOL)isEnable;

+(BOOL)DEBUG_MONITORING;
+(void)setDEBUG_MONITORING:(BOOL)isEnable;

+(NSInteger)DEBUG_CODE;
+(NSInteger)INFO_CODE;
+(NSInteger)WARN_CODE;
+(NSInteger)ERROR_CODE;
+(NSInteger)FATAL_CODE;

+(void)log:(NSInteger)code msg:(NSString *)msg;

@end

