//
//  FizzChatClient.h
//  FizzClientObjc
//
//  Created by Faizan on 16/09/2019.
//

#import "FizzError.h"
#import "FizzChannelMessage.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - listener protocol

@protocol FizzChannelMessageListener<NSObject>
@optional

-(void)onDisconnectedEventReceived;
-(void)onMessageUpdatedEventReceived:(FizzChannelMessage *)message;
-(void)onMessageDeletedEventReceived:(FizzChannelMessage *)message;
-(void)onMessagePublishedEventReceived:(FizzChannelMessage *)message;
-(void)onConnectedEventReceived:(BOOL)status syncRequired:(BOOL)syncRequired;

@end

#pragma mark - query ack
typedef void (^QueryMessagesAck)(NSArray<FizzChannelMessage *> *messages, FizzError *error);

#pragma mark -
@interface FizzChatClient : NSObject

#pragma mark - instance methods - listener operations
-(void)removeListenerforKey:(NSString *)key;
-(void)addListener:(NSObject<FizzChannelMessageListener> *)listener forKey:(NSString *)key;

#pragma mark - instance methods - channel operations
-(void)subscribeChannel:(NSString *)channelId withErrorAck:(nonnull FizzErrorAck)ack;
-(void)unsubscribeChannel:(NSString *)channelId withErrorAck:(nonnull FizzErrorAck)ack;

#pragma mark - instance methods - message history
-(void)queryLatestMessagesInChannel:(NSString *)channelId withCount:(int)count andQueryAck:(nonnull QueryMessagesAck)ack;
-(void)queryLatestMessagesInChannel:(NSString *)channelId withCount:(int)count beforeId:(long)beforeId andQueryAck:(nonnull QueryMessagesAck)ack;

#pragma mark - instance methods - message operations
-(void)deleteMessageFromChannel:(NSString *)channelId withMessageId:(long)messageId andErrorAck:(nonnull FizzErrorAck)ack;
-(void)publishMessageToChannel:(NSString *)channelId withNick:(NSString *)nick body:(NSString *)body data:(NSDictionary<NSString *, NSString *> *)data translate:(BOOL)translate persist:(BOOL)persist filter:(BOOL)filter andErrorAck:(nonnull FizzErrorAck)ack;
-(void)updateMessageInChannel:(NSString *)channelId withMessageId:(long)messageId nick:(NSString *)nick body:(NSString *)body data:(NSDictionary<NSString *, NSString *> *)data translate:(BOOL)translate persist:(BOOL)persist andErrorAck:(nonnull FizzErrorAck)ack;

@end

NS_ASSUME_NONNULL_END
