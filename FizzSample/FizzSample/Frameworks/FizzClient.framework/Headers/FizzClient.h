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

/** chat client for inetracting with chat service.*/
@property (strong, nonatomic, readonly) FizzChatClient *chat;

/** ingestion client for inetracting with ingestion service to post analytics data.*/
@property (strong, nonatomic, readonly) FizzIngestionClient *ingestion;

#pragma mark - static methods - instance creation
/** instance -  Fizz client's shared instance.
 @return the shared instance for FizzClient.
*/
+(instancetype)instance;

#pragma mark - instance methods - initialization
/** initialize1 -  initializes Fizz.
 @param appId the application's Id that is provided by Fizz.
 @param appSecret the application's secret that is provided by Fizz.
 @return error,  nil in the case of a successful initialization.
*/
-(FizzError *)initializeWithAppId:(NSString *)appId andSecret:(NSString *)appSecret;

/** initialize2 -  initializes Fizz.
 @param appId the application's Id that is provided by Fizz.
 @param appSecret the application's secret that is provided by Fizz.
 @param updateTick the refresh rate for Fizz's Event Queue Processing. Default value 1.5 (2 updates every 3 seconds)  is used in initialize1.
 @return error,  nil in the case of a successful initialization.
*/
-(FizzError *)initializeWithAppId:(NSString *)appId secret:(NSString *)appSecret andUpdateTick:(NSTimeInterval)updateTick;

#pragma mark - instance methods - lifecycle
/** state -  Fizz's client state.
 @return the current state of Fizz i-e; Opened or Closed.
*/
-(enum FizzClientState)state;

/** close - closes connection with Fizz.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful close.
 
 @code
 #import <FizzClient/FizzClient.h>
 
 FizzClient *sharedClient = [FizzClient instance];
 ...
 [sharedClient initializeWithAppId:@"YourAppId", andSecret:@"YourAppSecret"];
 ...
 [sharedClient close:^(FizzError *error) {
    if (error) {
        NSLog(@"Error Closing Fizz: %@", error.errorDescription);
    }
 }];
 @endcode
*/
-(void)close:(nonnull FizzErrorAck)ack;

/** open - opens connection with Fizz.
 @param userId the id of user for which session is to be created.
 @param locale the language for which user will be sending messages in.
 @param services the purpose for creating the session i-e Chat, Ingestion or Both.
 @param ack identifies a block which is executed on successfull or unsuccessfull  request. Might be nil. error is nil in the case of a successful connection.
 
 @code
 #import <FizzClient/FizzClient.h>
 
 FizzClient *sharedClient = [FizzClient instance];
 ...
 [sharedClient initializeWithAppId:@"YourAppId", andSecret:@"YourAppSecret"];
 ...
 [sharedClient openWithUser:@"YouUserID" locale:English services:All andErrorAck:^(FizzError *error) {
    if (error) {
        NSLog(@"Error Opening Fizz: %@", error.errorDescription);
    }
 }];
 @endcode
*/
-(void)openWithUser:(NSString *)userId locale:(enum FizzLanguageCodes)locale services:(enum FizzServices)services andErrorAck:(nonnull FizzErrorAck)ack;

#pragma mark - instance methods - misc
/** version -  FizzSDK version.
 @return the SDK version for Fizz.
*/
-(NSString *)version;

@end

NS_ASSUME_NONNULL_END
