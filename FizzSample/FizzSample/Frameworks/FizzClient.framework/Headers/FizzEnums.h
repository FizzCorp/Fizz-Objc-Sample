//
//  FizzEnums.h
//  FizzClientDemo
//
//  Created by Zeeshan Safder on 4/12/19.
//  Copyright © 2019 Fizz. All rights reserved.
//

#ifndef FizzEnums_h
#define FizzEnums_h

enum FizzErrorCode {
    ErrorCodeUnknown = 0,
    ErrorCodeInvalidParam = 1,
    ErrorCodeInvalidOperation = 2,
    ErrorCodeBadArgument = 3,
    ErrorCodeServerRequestFailed = 4,
    ErrorCodeAuthFailed = 5,
};

enum FizzPlatform {
    PlatformUndefined = 0,
    PlaformIOS = 1,
    PlaformAndroid = 2,
    PlaformWindows = 3,
    PlaformWindowsPhone = 4,
    PlaformMacOSX = 5,
    PlaformWebPlayer = 6
};

enum FizzEventType {
    SessionStart,
    SessionEnd,
    TextMessageSent,
    InAppPurchase
};

enum FizzClientState {
    Closed,
    Opened
};

enum FizzServices {
    Chat =      1 << 0,
    Analytics = 1 << 1,
    All = Chat | Analytics
};

#endif /* FizzEnums_h */
