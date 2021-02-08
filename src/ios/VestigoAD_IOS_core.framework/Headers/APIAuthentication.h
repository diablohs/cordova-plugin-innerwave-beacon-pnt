//
//  APIAuthendication.h
//  RestkitTest
//
//  Created by SungKue.Jeon on 2020/12/21.
//  Copyright © 2020 pnt. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
 Vestigo Ad 사용을 위해 필요한 필수 파라미터 class
 */
@interface APIAuthentication : NSObject

// PnT Oauth domain
@property NSString *oAuthDomain;

// PnT API server domain
@property NSString *apiDomain;

// 사이트 scope / uuid
@property NSString *scope;

// PnT로부터 발급받은 client_id
@property NSString *client_id;

// PnT로부터 발급받은 client_secret
@property NSString *client_secret;

- (BOOL)isValid;

@end

NS_ASSUME_NONNULL_END
