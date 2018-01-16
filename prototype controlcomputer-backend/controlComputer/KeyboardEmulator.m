//
//  KeyboardEmulator.m
//  controlComputer
//
//  Created by Adam Li on 3/30/16.
//  Copyright © 2016 Adam Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KeyboardEmulator.h"

@implementation KeyboardEmulator : NSObject

// Function to press key based on passed in key code value
- (void) keyPress:(double)code {
    CGKeyCode keyCode;
    keyCode = (CGKeyCode)code;
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    
    // create events for pressing up and down the key
    CGEventRef eventDown = CGEventCreateKeyboardEvent(source, keyCode, YES);
    CGEventRef eventUp = CGEventCreateKeyboardEvent(source, keyCode, NO);
    
    // press key down
    CGEventPost(kCGSessionEventTap, eventDown);
    
    // Keep it down for a bit
//    sleep(1);
    
    // release the key
    CGEventPost(kCGSessionEventTap, eventUp);
    
    // release unneeded events
    CFRelease(eventUp);
    CFRelease(eventDown);
    CFRelease(source);
}

- (CGKeyCode) convertNumToKey:(int)keyNum {
    return (CGKeyCode)keyNum;
}

// Function to convert string to keyboard stroke number
- (double) convertStringToKey:(NSString *)keyString {
    
    if ([keyString isEqual: @"a"]) {return 0.0;}
    if ([keyString isEqual: @"s"]) {return 1.0;}
    if ([keyString isEqual: @"d"]) {return 2.0;}
    if ([keyString isEqual: @"f"]) {return 3.0;}
    if ([keyString isEqual: @"h"]) {return 4.0;}
    if ([keyString isEqual: @"g"]) {return 5.0;}
    if ([keyString isEqual: @"z"]) {return 6.0;}
    if ([keyString isEqual: @"x"]) {return 7.0;}
    if ([keyString isEqual: @"c"]) {return 8.0;}
    if ([keyString isEqual: @"v"]) {return 9.0;}
    // what is 10?
    if ([keyString isEqual: @"b"]) {return 11.0;}
    if ([keyString isEqual: @"q"]) {return 12.0;}
    if ([keyString isEqual: @"w"]) {return 13.0;}
    if ([keyString isEqual: @"e"]) {return 14.0;}
    if ([keyString isEqual: @"r"]) {return 15.0;}
    if ([keyString isEqual: @"y"]) {return 16.0;}
    if ([keyString isEqual: @"t"]) {return 17.0;}
    if ([keyString isEqual: @"1"]) {return 18.0;}
    if ([keyString isEqual: @"2"]) {return 19.0;}
    if ([keyString isEqual: @"3"]) {return 20.0;}
    if ([keyString isEqual: @"4"]) {return 21.0;}
    if ([keyString isEqual: @"6"]) {return 22.0;}
    if ([keyString isEqual: @"5"]) {return 23.0;}
    if ([keyString isEqual: @"="]) {return 24.0;}
    if ([keyString isEqual: @"9"]) {return 25.0;}
    if ([keyString isEqual: @"7"]) {return 26.0;}
    if ([keyString isEqual: @"-"]) {return 27.0;}
    if ([keyString isEqual: @"8"]) {return 28.0;}
    if ([keyString isEqual: @"0"]) {return 29.0;}
    if ([keyString isEqual: @"]"]) {return 30.0;}
    if ([keyString isEqual: @"o"]) {return 31.0;}
    if ([keyString isEqual: @"u"]) {return 32.0;}
    if ([keyString isEqual: @"["]) {return 33.0;}
    if ([keyString isEqual: @"i"]) {return 34.0;}
    if ([keyString isEqual: @"p"]) {return 35.0;}
    if ([keyString isEqual: @"RETURN"]) {return 36.0;}
    if ([keyString isEqual: @"l"]) {return 37.0;}
    if ([keyString isEqual: @"j"]) {return 38.0;}
    if ([keyString isEqual: @"'"]) {return 39.0;}
    if ([keyString isEqual: @"k"]) {return 40.0;}
    if ([keyString isEqual: @";"]) {return 41.0;}
    if ([keyString isEqual: @"\\"]) {return 42.0;}
    if ([keyString isEqual: @","]) {return 43.0;}
    if ([keyString isEqual: @"/"]) {return 44.0;}
    if ([keyString isEqual: @"n"]) {return 45.0;}
    if ([keyString isEqual: @"m"]) {return 46.0;}
    if ([keyString isEqual: @"."]) {return 47.0;}
    if ([keyString isEqual: @"TAB"]) {return 48.0;}
    if ([keyString isEqual: @"SPACE"]) {return 49.0;}
    if ([keyString isEqual: @"`"]) {return 50.0;}
    if ([keyString isEqual: @"DELETE"]) {return 51.0;}
    if ([keyString isEqual: @"ENTER"]) {return 52.0;}
    if ([keyString isEqual: @"ESCAPE"]) {return 53.0;}
    
    if ([keyString isEqual: @"."]) {return 65.0;}
    
    
    if ([keyString isEqual: @"0"]) {return 82.0;}
    if ([keyString isEqual: @"1"]) {return 83.0;}
    if ([keyString isEqual: @"2"]) {return 84.0;}
    if ([keyString isEqual: @"3"]) {return 85.0;}
    if ([keyString isEqual: @"4"]) {return 86.0;}
    if ([keyString isEqual: @"5"]) {return 87.0;}
    if ([keyString isEqual: @"6"]) {return 88.0;}
    if ([keyString isEqual: @"7"]) {return 89.0;}
    
    if ([keyString isEqual: @"8"]) {return 91.0;}
    if ([keyString isEqual: @"9"]) {return 92.0;}
    
    if ([keyString isEqual: @"LEFT"]) {return 123.0;}
    if ([keyString isEqual: @"RIGHT"]) {return 124.0;}
    if ([keyString isEqual: @"DOWN"]) {return 125.0;}
    if ([keyString isEqual: @"UP"]) {return 126.0;}
    
//    NSLog([keyString isEqualToString:@"a"]);
//    NSLog(@"%@", NSStringFromClass([keyString class]));
//    NSLog(@"%@", NSStringFromClass([@"a" class]));
    NSLog(keyString);
    NSLog(@"keyString %@ Not Found. Aborting...\n", keyString);
    exit(EXIT_FAILURE);
}


@end
