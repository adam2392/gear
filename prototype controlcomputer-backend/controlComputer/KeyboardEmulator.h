//
//  KeyboardEmulator.h
//  controlComputer
//
//  Created by Adam Li on 3/30/16.
//  Copyright © 2016 Adam Li. All rights reserved.
//

#ifndef KeyboardEmulator_h
#define KeyboardEmulator_h

#import <Cocoa/Cocoa.h>

@interface KeyboardEmulator : NSObject
- (void) keyPress:(double)keyCode;
- (double) convertStringToKey:(NSString *)keyString;
- (CGKeyCode) convertNumToKey:(int)keyNum;
@end

#endif /* KeyboardEmulator_h */
