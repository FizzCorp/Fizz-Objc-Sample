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

@property (readonly) long created;
@property (readonly) long messageId;
@property (strong, nonatomic, readonly) NSString *to;
@property (strong, nonatomic, readonly) NSString *body;
@property (strong, nonatomic, readonly) NSString *nick;
@property (strong, nonatomic, readonly) NSString *from;
@property (strong, nonatomic, readonly) NSDictionary<NSString *, NSString *> *data;
@property (strong, nonatomic, readonly) NSDictionary<NSString *, NSString *> *translations;

@end

NS_ASSUME_NONNULL_END
