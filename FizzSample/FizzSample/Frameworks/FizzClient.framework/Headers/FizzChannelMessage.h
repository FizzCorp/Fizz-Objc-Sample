//
//  FizzChannelMessage.h
//  FizzClientObjc
//
//  Created by Faizan on 17/09/2019.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FizzChannelMessage : NSObject {
@protected
    long _created;
    long _messageId;
    
    NSString *_to;
    NSString *_from;
    NSString *_nick;
    NSString *_body;
    
    NSDictionary<NSString *, NSString *> *_data;
    NSDictionary<NSString *, NSString *> *_translations;
}

/** created is a long value representing server timestamp for message creation.*/
@property (readonly) long created;

/** messageId is a long value representing a unique id of a message in a channel.
 @note id is unique in a channel the uniqueness constraint does not hold across channels.*/
@property (readonly) long messageId;

/** to specifies the channelId the message is sent to.*/
@property (strong, nonatomic, readonly) NSString *to;

/** body string that represents message body.*/
@property (strong, nonatomic, readonly) NSString *body;

/** nick name of the user that sent the message.*/
@property (strong, nonatomic, readonly) NSString *nick;

/** from is userId of the sender.*/
@property (strong, nonatomic, readonly) NSString *from;

/** data holds any custom data that the sender wishes to send with a message.*/
@property (strong, nonatomic, readonly) NSDictionary<NSString *, NSString *> *data;

/** translations of the message in all the languages registered in the channel.*/
@property (strong, nonatomic, readonly) NSDictionary<NSString *, NSString *> *translations;

@end

NS_ASSUME_NONNULL_END
