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
/** setBuildNo.
 @param buildNo the application's build number for which analytics events are needed.
 @return error if any otherwise nil.
*/
-(FizzError *)setBuildNo:(NSString *)buildNo;

/** setCustomParams01.
 @param str01 the 1 of 3 custom strings available to user for recording analytics events.
 @return error if any otherwise nil.
*/
-(FizzError *)setCustomParams01:(NSString *)str01;

/** setCustomParams02.
 @param str02 the 2nd of 3 custom strings available to user for recording analytics events.
 @return error if any otherwise nil.
*/
-(FizzError *)setCustomParams02:(NSString *)str02;

/** setCustomParams03.
 @param str03 the 3rd of 3 custom strings available to user for recording analytics events.
 @return error if any otherwise nil.
*/
-(FizzError *)setCustomParams03:(NSString *)str03;

/** setPlatform.
 @param platform the application's platform for which analytics events are needed.
 @return error if any otherwise nil.
*/
-(FizzError *)setPlatform:(enum FizzPlatform)platform;

#pragma mark - instance methods - post events
/** textMessageSentToChannel - records the message data for analytics.
 @param channelId the id of the channel the message was sent to.
 @param content the body of the message.
 @param senderNick the nick of sender.
 @return error if any otherwise nil.
*/
-(FizzError *)textMessageSentToChannel:(NSString *)channelId withContent:(NSString *)content bySender:(NSString *)senderNick;

/** productPurchasedWithId - records the inApp related data for analytics.
 @param productId the id of the product purchased.
 @param amount the amount of the product purchased.
 @param currency the currency in which the amount was paid.
 @param receipt the string representation of product receipt.
 @return error if any otherwise nil.
*/
-(FizzError *)productPurchasedWithId:(NSString *)productId amount:(double)amount currency:(NSString *)currency andReceipt:(NSString *)receipt;

@end

NS_ASSUME_NONNULL_END
