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
typedef void (^FizzErrorAck)(FizzError *error);

@interface FizzError : NSObject {
@protected
    NSString *_errorDescription;
    enum FizzErrorCode _errorCode;
}

@property (readonly) enum FizzErrorCode errorCode;
@property (strong, nonatomic, readonly) NSString *errorDescription;

@end

NS_ASSUME_NONNULL_END
