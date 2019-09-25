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
/** QueryMessagesAck serves as a block param in async calls to provide response of the channel messages query.*/
typedef void (^QueryMessagesAck)(NSArray<FizzChannelMessage *> *messages, FizzError *error);

#pragma mark -
@interface FizzChatClient : NSObject

#pragma mark - instance methods - listener operations
/** removeListenerforKey.
 @param key the unique Id to remove the listener binded.
*/
-(void)removeListenerforKey:(NSString *)key;

/** addListener.
 @param listener weak reference of the listener that observes FizzChannelMessageListener delegate methods.
 @param key the unique Id to add and bind the listener.
*/
-(void)addListener:(NSObject<FizzChannelMessageListener> *)listener forKey:(NSString *)key;

#pragma mark - instance methods - channel operations
/** subscribeChannel - subscribes the channel on Fizz.
 @param channelId the id of channel for which live messages are to be received.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful subscription.
 @note the live messages are received in onMessagePublishedEventReceived method of the binded listener.
*/
-(void)subscribeChannel:(NSString *)channelId withErrorAck:(nonnull FizzErrorAck)ack;

/** unsubscribeChannel - subscribes the channel on Fizz.
 @param channelId the id of channel for which live messages are no longer needed.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful unsubscribe.
*/
-(void)unsubscribeChannel:(NSString *)channelId withErrorAck:(nonnull FizzErrorAck)ack;

#pragma mark - instance methods - message history
/** queryLatestMessagesInChannel1.
 @param channelId the id of channel for which live messages query is made.
 @param count number of messages to be retrieved.
 @param ack identifies a block which provides the response for messages query.
*/
-(void)queryLatestMessagesInChannel:(NSString *)channelId withCount:(int)count andQueryAck:(nonnull QueryMessagesAck)ack;

/** queryLatestMessagesInChannel2.
 @param channelId the id of channel for which live messages query is made.
 @param count number of messages to be retrieved.
 @param beforeId the messageId before which messages are to be retrieved.
 @param ack identifies a block which provides the response for messages query.
*/
-(void)queryLatestMessagesInChannel:(NSString *)channelId withCount:(int)count beforeId:(long)beforeId andQueryAck:(nonnull QueryMessagesAck)ack;

#pragma mark - instance methods - message operations
/** deleteMessageFromChannel.
 @param channelId the id of channel for which message is to be deleted.
 @param messageId the id of the message to be deleted.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful deletion.
 @note the  deleted message is received in onMessageDeletedEventReceived method of the binded listener.
*/
-(void)deleteMessageFromChannel:(NSString *)channelId withMessageId:(long)messageId andErrorAck:(nonnull FizzErrorAck)ack;

/** publishMessageToChannel.
 @param channelId the id of channel for which message is to be published.
 @param nick the nick of sender.
 @param body content of the message.
 @param data custom data that the sender wishes to send with the message.
 @param translate boolean flag to turn translation on/off.
 @param persist boolean flag to tell server whether or not the message should be saved.
 @param filter boolean flag to turn profanity filter on/off.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful publish.
 @note the  published message is received in onMessagePublishedEventReceived method of the binded listener.
*/
-(void)publishMessageToChannel:(NSString *)channelId withNick:(NSString *)nick body:(NSString *)body data:(NSDictionary<NSString *, NSString *> *)data translate:(BOOL)translate persist:(BOOL)persist filter:(BOOL)filter andErrorAck:(nonnull FizzErrorAck)ack;

/** updateMessageInChannel.
 @param channelId the id of channel for which message is to be updated.
 @param messageId the id of the message to be updated.
 @param nick the nick of sender.
 @param body content of the message.
 @param data custom data that the sender wishes to send with the message.
 @param translate boolean flag to turn translation on/off.
 @param persist boolean flag to tell server whether or not the message should be saved.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful publish.
 @note the  updated message is received in onMessageUpdatedEventReceived method of the binded listener.
*/
-(void)updateMessageInChannel:(NSString *)channelId withMessageId:(long)messageId nick:(NSString *)nick body:(NSString *)body data:(NSDictionary<NSString *, NSString *> *)data translate:(BOOL)translate persist:(BOOL)persist andErrorAck:(nonnull FizzErrorAck)ack;

@end

NS_ASSUME_NONNULL_END
