//
//  UserIdentity.h
//  RestkitTest
//
//  Created by SungKue.Jeon on 2020/12/21.
//  Copyright © 2020 pnt. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Vestigo Ad 에서 User 를 구분 키 / 네임.
 */
@interface UserIdentity : NSObject
// 대상 id (ex : 환자번호, 대상번호) @unique
@property NSString *targetId;
// 대상 이름 (PnT 백엔드 시스템에서 보여질 이름)
@property NSString *targetName;

- (BOOL)isValid;

@end
NS_ASSUME_NONNULL_END
