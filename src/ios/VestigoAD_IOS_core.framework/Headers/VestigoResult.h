//
//  VestigoResult.h
//  VestigoAD_IOS_core
//
//  Created by SungKue.Jeon on 2021/01/28.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VestigoResultType) {
  VestigoResultTypeStart = 8001,
  VestigoResultTypeStop = 8002,
}NS_SWIFT_NAME(VestigoResultType);

@interface VestigoResult : NSObject

@property VestigoResultType resultType;

@property BOOL success;

@property NSInteger state;

@property NSString *message;

@end

NS_ASSUME_NONNULL_END
