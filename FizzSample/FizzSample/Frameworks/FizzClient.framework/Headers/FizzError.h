//
//  FizzError.h
//  FizzClientObjc
//
//  Created by Faizan on 16/09/2019.
//

#import "FizzEnums.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class FizzError;

/** FizzErrorAck serves as a block param in async calls to inform users of errors if any.*/
typedef void (^FizzErrorAck)(FizzError *error);

@interface FizzError : NSObject {
@protected
    NSString *_errorDescription;
    enum FizzErrorCode _errorCode;
}

/** errorCode specifies the unique code for the error condition.*/
@property (readonly) enum FizzErrorCode errorCode;

/** errorDescription provides with a brief description of error.*/
@property (strong, nonatomic, readonly) NSString *errorDescription;

@end

NS_ASSUME_NONNULL_END
