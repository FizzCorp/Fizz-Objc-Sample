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

enum FizzLanguageCodes {
    Afrikaans, Arabic, Bangla, BosnianLatin, Bulgarian,
    CantoneseTraditional, Catalan, ChineseSimplified, ChineseTraditional, Croatian,
    Czech, Danish, Dutch, English, Estonian, Fijian, Filipino, Finnish, French, German,
    Greek, HaitianCreole, Hebrew, Hindi, HmongDaw, Hungarian, Icelandic, Indonesian, Italian,
    Japanese, Kiswahili, Klingon, KlingonPlqaD, Korean, Latvian, Lithuanian, Malagasy, Malay,
    Maltese, Norwegian, Persian, Polish, Portuguese, QueretaroOtomi, Romanian, Russian, Samoan,
    SerbianCyrillic, SerbianLatin, Slovak, Slovenian, Spanish, Swedish, Tahitian, Tamil, Telugu,
    Thai, Tongan, Turkish, Ukrainian, Urdu, Vietnamese, Welsh, YucatecMaya
};

#endif /* FizzEnums_h */
