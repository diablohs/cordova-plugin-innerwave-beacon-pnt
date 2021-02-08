//
//  VestigoSettings.h
//  VestigoAD_IOS_core
//
//  Created by SungKue.Jeon on 2021/01/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VestigoSettings : NSObject

// 지점 일정 이상 거리 안으로 들어오면 자동 실행/등록 여부.
@property BOOL autoStartWhenEnter;

// 지점에서 일정 거리 이상 멀어지면 자동 종료/해지 여부.
@property BOOL autoStopWhenExit;

// 구분할 경계 반지름 (단위 : m)
@property double boundaryRadius;
@end

NS_ASSUME_NONNULL_END
