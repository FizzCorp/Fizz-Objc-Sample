//
//  FizzClient.h
//  FizzClientObjc
//
//  Created by Faizan on 16/09/2019.
//

#import "FizzError.h"
#import "FizzEnums.h"
#import "FizzChatClient.h"
#import "FizzIngestionClient.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FizzClient : NSObject

#pragma mark - properties - client handlers
@property (strong, nonatomic, readonly) FizzChatClient *chat;
@property (strong, nonatomic, readonly) FizzIngestionClient *ingestion;

#pragma mark - static methods - instance creation
+(instancetype)instance;

#pragma mark - instance methods - initialization
-(FizzError *)initializeWithAppId:(NSString *)appId andSecret:(NSString *)appSecret;

#pragma mark - instance methods - lifecycle
-(void)update;
-(enum FizzClientState)state;
-(void)close:(nonnull FizzErrorAck)ack;
-(void)openWithUser:(NSString *)userId locale:(NSString *)locale services:(enum FizzServices)services andErrorAck:(nonnull FizzErrorAck)ack;

#pragma mark - instance methods - misc
-(NSString *)version;

@end

NS_ASSUME_NONNULL_END
