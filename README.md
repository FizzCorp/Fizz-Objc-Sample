# Fizz-iOS-Framework
**FizzClient.framework** is compatible with iOS **8.0** and above. Follow the steps below for [Installation](#installation) and [Integration](#integration-guide).

----------------
### Installation
----------------
#### Framework
Download **FizzClient.Framework.zip** from [Latest Release](https://github.com/FizzCorp/Fizz-iOS-Framework/releases/tag/v1.0).

#### Dependent Frameworks
**FizzClient.framework** requires [MQTTClient.framework](https://github.com/novastone-media/MQTT-Client-Framework) and [SocketRocket.framework](https://github.com/facebook/SocketRocket/releases/tag/0.4.2). For your convenience the dependent frameworks are generated from their respective code repositories and are made part of the releases. Simply download **dependencies.zip** from [Latest Release](https://github.com/FizzCorp/Fizz-iOS-Framework/releases/tag/v1.0).

#### Embed To Your Xcode Project
Once you have downloaded and extracted all 3 frameworks i-e; **FizzClient.Framework**, **MQTTClient.framework** and **SocketRocket.framework**. Follow these steps to add the frameworks to your Xcode project.
1. Copy the frameworks in your project's frameworks folder

![](https://user-images.githubusercontent.com/18396012/65511374-82d49d00-def0-11e9-83cc-121d60d8adf8.png)

2. Add the frameworks to your project by right clicking the framework folder within Xcode and selecting **Add Files to "Your Project Name"**

![](https://user-images.githubusercontent.com/18396012/65511375-836d3380-def0-11e9-9fb4-eb1c3a916b6a.png)

3. Embed the frameworks to your project from project settings ```General > Embeded Frameworks``` section

![](https://user-images.githubusercontent.com/18396012/65749209-260af980-e11f-11e9-86ea-19fad96ba4e6.png)

---------------------
### Integration Guide
---------------------
#### Threading Model
The FizzClient uses multiple threads internally to run I/O in the background. However all callbacks and events are posted to the main thread so that the UI can be updated in a safe manner. Also please note that all Fizz client APIs should also be called from the main thread. This simplifies the process of integrating Fizz into iOS applications.

#### Setup Event Listener
1. Make your class inherit FizzChannelMessageListener and implement its delegate methods that you want to observe.
```objc
#import <FizzClient/FizzClient.h>

@interface MyClass : NSObject<FizzChannelMessageListener>

-(void)onMessagePublishedEventReceived:(FizzChannelMessage *)message;

@end

@implementation MyClass

-(void)onMessagePublishedEventReceived:(FizzChannelMessage *)message {
    // messages sent / received will be notified here
}

@end

```
2. register your class' weak reference with Fizz chatClient as a channel message listener (Fizz should be initialized before registering any listeners).
```objc
FizzClient *sharedClient = [FizzClient instance];

// initialize fizz
FizzError *initError = [sharedClient initializeWithAppId:AppId andSecret:AppSecret];
BOOL initSuccess = !initError;
if(initSuccess) {
    __weak MyClass *wself = self;// add listener
    [sharedClient.chat addListener:wself forKey:@"MyUniquerKeyForListener"];
}
else {
    NSLog(@"fizz:: initError: %@", initError.errorDescription);
}
```
#### Subscribe to Channel
In order to receive live messages sent in a channel you must subscribe to that channel using the channel's Id.
```objc
// assuming Fizz is initialized and listener is registered
[[FizzClient instance].chat subscribeChannel:@"YourChannelId" withErrorAck:^(FizzError *joinError) {
    if(joinError) {
        NSLog(@"fizz:: joinError: %@", joinError.errorDescription);
    }
    else {
        // the live messages will now be notified in onMessagePublishedEventReceived method of your listener
    }
}];
```
#### Publish Message
In order to publish a message in a channel, refer to the following code snippet.
```objc
// assuming Fizz is initialized and listener is registered
NSDictionary *myCustomData = @{
    @"image1Url": @"https://abc.def.ghi",
    @"myCustomJsonString": @"{'foo':'bar'}"
};// custom data to be used by developer for a message

[[FizzClient instance].chat publishMessageToChannel:@"YourChannelId" withNick:@"YourNick" body:@"YourMessageText"
    data:myCustomData translate:YES persist:YES filter:YES andErrorAck:^(FizzError *publishError) {
        if(publishError) {
            NSLog(@"fizz:: publishError: %@", publishError.errorDescription);
        }
        else {
            // this sent message will be notified in onMessagePublishedEventReceived method of your listener
        }
    }];
```
#### Fetch Messages
In order to fetch historic messages in a channel, refer to the following code snippet.
```objc
// assuming Fizz is initialized and listener is registered
[[FizzClient instance].chat queryLatestMessagesInChannel:@"YourChannelId" withCount:15
    andQueryAck:^(NSArray<FizzChannelMessage *> *messages, FizzError *fetchError) {
        if(fetchError) {
            NSLog(@"fizz:: fetchError: %@", fetchError.errorDescription);
        }
        else {
            // your code here to deal with historic messages
        }
    }];
```
---------
### Notes
---------
#### MQTT Logs
**MQTTClient.framework** prints too many logs on the console related to its events. To tune the log settings as per your requirement, refer to the following code snippet.
```objc
#import <MQTTClient/MQTTLog.h>

// log settings for MQTT
[MQTTLog setLogLevel:DDLogLevelOff];
```