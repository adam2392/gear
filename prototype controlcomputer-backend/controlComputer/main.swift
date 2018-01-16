//
//  main.swift
//  controlComputer
//
//  Created by Adam Li on 3/28/16.
//  Copyright © 2016 Adam Li. All rights reserved.
//

import Foundation
import ORSSerial
import IOKit
import IOKit.serial

class SerialHandler : NSObject, ORSSerialPortDelegate {
    let standardInputFileHandle = NSFileHandle.fileHandleWithStandardInput()
    var serialPort: ORSSerialPort?
    
    func runProcessingInput(pathFromUser: String) {
        setbuf(stdout, nil)
        
        standardInputFileHandle.readabilityHandler = { (fileHandle: NSFileHandle!) in
            let data = fileHandle.availableData
            dispatch_async(dispatch_get_main_queue(), { () -> Void in
                self.handleUserInput(data)
            })
        }
        
        self.serialPort = ORSSerialPort(path: pathFromUser) // please adjust to your handle
        self.serialPort?.baudRate = 9600
        self.serialPort?.delegate = self
        serialPort?.open()
        
        NSRunLoop.currentRunLoop().run() // loop
    }
    
    // MAIN FUNCTION TO READ IN SERIAL PRINTING FROM INTEL EDISON
    func handleUserInput(dataFromUser: NSData) {
        
        
        if let string = NSString(data: dataFromUser, encoding: NSUTF8StringEncoding) as? String {
            
            if string.lowercaseString.hasPrefix("exit") ||
                string.lowercaseString.hasPrefix("quit") {
                print("Quitting...")
                exit(EXIT_SUCCESS)
            }
            print("This is our data");
            
            self.serialPort?.sendData(dataFromUser)
        }
    }
    
    func serialPort(serialPort: ORSSerialPort, didReceiveData data: NSData) {
        let myKeyboard = KeyboardEmulator(); // initialize keyboard emulator
        var key = 0.0;
        var keyCode = "";
        if let string = String(data: data, encoding: NSUTF8StringEncoding) {
            // further encode the string as ASCII
            let encoding = NSASCIIStringEncoding
            
            // grab only the first character in the ASCII Encoding
            if let test = string.dataUsingEncoding(encoding)
            {
                let buff = String(data: test, encoding: encoding)
                keyCode = buff![0...1]
//                print("The KeyCode we got is")
//                print(keyCode)
            }
            
//            print(String(string.dynamicType).componentsSeparatedByString("__").last!)
//            print(String(test.dynamicType).componentsSeparatedByString("__").last!)
//            print(String("a".dynamicType).componentsSeparatedByString("__").last!)
            key = myKeyboard.convertStringToKey(keyCode);

            myKeyboard.keyPress(key);
        }
    }
    
    func serialPortWasRemovedFromSystem(serialPort: ORSSerialPort) {
        self.serialPort = nil
    }
    
    func serialPort(serialPort: ORSSerialPort, didEncounterError error: NSError) {
        print("Serial port (\(serialPort)) encountered error: \(error)")
    }
    
    func serialPortWasOpened(serialPort: ORSSerialPort) {
        print("Serial port \(serialPort) was opened")
    }
    
    /*************** Functions For Handling Finding Serial Devices For User ****************/
    // FUNCTION for finding Serial Devices
    func findSerialDevices(deviceType: String, inout serialPortIterator: io_iterator_t ) -> kern_return_t {
        // initialize results, dictionary for classes of devices
        var result: kern_return_t = KERN_FAILURE
        let classesToMatch = IOServiceMatching(kIOSerialBSDServiceValue)
        var classesToMatchDict = (classesToMatch as NSDictionary)
            as! Dictionary<String, AnyObject>
        
        // assign all keys as a certain device type
        classesToMatchDict[kIOSerialBSDTypeKey] = deviceType
        let classesToMatchCFDictRef = (classesToMatchDict as NSDictionary) as CFDictionaryRef
        
        // look at master port and find all matching devices and create an iterator for all devices
        // -> return success/failure
        result = IOServiceGetMatchingServices(kIOMasterPortDefault, classesToMatchCFDictRef, &serialPortIterator);
        return result 
    }
    
    // FUNCTION to print the different serial paths that exist
    func printSerialPaths(portIterator: io_iterator_t) -> Dictionary<Double, String> {
        var serialService: io_object_t
        var paths = [Double: String]()    // initialize empty list to store all paths
        
        var index = 0.0
        repeat {
            serialService = IOIteratorNext(portIterator)
            if (serialService != 0) {
                let key: CFString! = "IOCalloutDevice"
                let bsdPathAsCFtring: AnyObject? =
                    IORegistryEntryCreateCFProperty(serialService, key, kCFAllocatorDefault, 0).takeUnretainedValue()
                let bsdPath = bsdPathAsCFtring as! String?
                if let path = bsdPath {
                    print(path)
                    paths[index] = path
                    index += 1
                }
            }
        } while serialService != 0;
        
        return paths
    }
}

class Utility{
    func classNameAsString(obj: Any) -> String {
        return String(obj.dynamicType).componentsSeparatedByString("__").last!
    }
}

// FUNCTION to get input from user
func input() -> String {
    let keyboard = NSFileHandle.fileHandleWithStandardInput()
    let inputData = keyboard.availableData
    
    return NSString(data: inputData, encoding: NSUTF8StringEncoding) as! String
}


extension String { // create an extension for String to be cast to a double
    var doubleValue: Double {
        return (self as NSString).doubleValue
    }
}
extension String { // string extension to allow access of substrings
    /**
     Subscript to allow for quick String substrings ["Hello"][0...1] = "He"
     */
    subscript (r: Range<Int>) -> String {
        get {
            let start = self.startIndex.advancedBy(r.startIndex)
            let end = self.startIndex.advancedBy(r.endIndex - 1)
            return self.substringWithRange(start..<end)
        }
    }
}
//extension NSData    //
//{
//    var byteBuffer : UnsafeBufferPointer<UInt8> { get { return UnsafeBufferPointer<UInt8>(start: UnsafeMutablePointer<UInt8>(self.bytes), count: self.length) }}
//}
//extension String // extension to get the number of
//{
//    init?(data : NSData, encoding : NSStringEncoding)
//    {
//        self.init(bytes: data.byteBuffer, encoding: encoding)
//    }
//}

// main function that is run
print("Starting serial test program")
print("To quit type: 'exit' or 'quit'")

// initialize port iterator and determine all the available serial ports
var portIterator: io_iterator_t = 0
let kernResult = SerialHandler().findSerialDevices(kIOSerialBSDAllTypes, serialPortIterator: &portIterator)
var paths = SerialHandler().printSerialPaths(portIterator)

// allow user to select which serial port to connect to
print("\n\nThese are the paths: ", paths)
print("\nPlease enter which serial port to connect to...")
let theInput = input()
print("\nYou selected: ", (theInput.doubleValue))

//if theInput.doubleValue == -1 {
//    // initialize port iterator and determine all the available serial ports
//    var portIterator: io_iterator_t = 0
//    let kernResult = SerialHandler().findSerialDevices(kIOSerialBSDAllTypes, serialPortIterator: &portIterator)
//    var paths = SerialHandler().printSerialPaths(portIterator)
//}

let path = paths[theInput.doubleValue]
if path != nil {
    SerialHandler().runProcessingInput(path!)
}




