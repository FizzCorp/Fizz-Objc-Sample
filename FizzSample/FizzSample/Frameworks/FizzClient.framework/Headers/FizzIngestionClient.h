//
//  FizzIngestionClient.h
//  FizzClientObjc
//
//  Created by Faizan on 16/09/2019.
//

#import "FizzEnums.h"
#import "FizzError.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FizzIngestionClient : NSObject

#pragma mark - instance methods - params update
-(FizzError *)setBuildNo:(NSString *)buildNo;
-(FizzError *)setCustomParams01:(NSString *)str01;
-(FizzError *)setCustomParams02:(NSString *)str02;
-(FizzError *)setCustomParams03:(NSString *)str03;
-(FizzError *)setPlatform:(enum FizzPlatform)platform;

#pragma mark - instance methods - post events
-(FizzError *)textMessageSentToChannel:(NSString *)channelId withContent:(NSString *)content bySender:(NSString *)senderNick;
-(FizzError *)productPurchasedWithId:(NSString *)productId amount:(double)amount currency:(NSString *)currency andReceipt:(NSString *)receipt;

@end

NS_ASSUME_NONNULL_END
