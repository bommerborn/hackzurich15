//
//  AppDelegate.swift
//  Notification
//
//  Created by Benno Ommerborn on 03.10.15.
//  Copyright © 2015 bommerborn. All rights reserved.
//

import UIKit
import Alamofire


@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        NSUserDefaults.standardUserDefaults().setObject(NSString(UTF8String: "LEON.BERNARD@AXIOMC.COM"), forKey: "username")
        NSUserDefaults.standardUserDefaults().setObject(NSString(UTF8String: "axiom"), forKey: "password")
        NSUserDefaults.standardUserDefaults().synchronize()
        
        if let token = NSUserDefaults.standardUserDefaults().objectForKey("auth_token") as? NSString {
            print("Auth token stored: \(token)")
        }
        
        let settings = UIUserNotificationSettings(forTypes: [.Alert, .Badge, .Sound], categories: nil)
        UIApplication.sharedApplication().registerUserNotificationSettings(settings)
        UIApplication.sharedApplication().registerForRemoteNotifications()

        return true
    }
    
    func application(application: UIApplication, didReceiveRemoteNotification userInfo: [NSObject : AnyObject], fetchCompletionHandler completionHandler: (UIBackgroundFetchResult) -> Void) {
        print("Recvd not \(userInfo)")
        
        if let auth_token = NSUserDefaults.standardUserDefaults().objectForKey("auth_token") as? NSString {
            Alamofire.request(.POST, getURL() + "/dispatch_push", parameters: ["token" : auth_token, "user_info" : userInfo])
                    .responseJSON { request, response, result in
                        print(response)

                        completionHandler(UIBackgroundFetchResult.NewData)
                        print("Called completion handler....")
                }
        }
        else {
            completionHandler(UIBackgroundFetchResult.NoData)
            print("Called completion handler (no auth)....")
        }

    }

    func applicationWillResignActive(application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(application: UIApplication) {
        // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }
    
    func getURL() ->String{
        return "http://172.27.3.49:5000"
    }
    
    func application(application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: NSData) {
        print("Got token data\(deviceToken)")
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if let username = defaults.objectForKey("username") as? NSString,
            password = defaults.objectForKey("password") as? NSString {
                Alamofire.request(.POST, getURL() + "/authenticate", parameters: ["username" : username, "password" : password, "push_token" : deviceToken.hexString()])
                    .responseJSON { request, response, result in
                        print(request)  // original URL request
                        print(response) // URL response
                        print(result)   // result of response serialization
                        
                        if let JSON = result.value {
                            print("JSON: \(JSON)")
                            NSUserDefaults.standardUserDefaults().setObject(JSON["token"], forKey: "auth_token")
                            NSUserDefaults.standardUserDefaults().synchronize()
                        }
                }
        }
    }
    
    func application(application: UIApplication, didFailToRegisterForRemoteNotificationsWithError error: NSError) {
        print("Couldn't register: \(error)")
    }


}

extension NSData {
    func hexString() -> String {
        // "Array" of all bytes:
        let bytes = UnsafeBufferPointer<UInt8>(start: UnsafePointer(self.bytes), count:self.length)
        // Array of hex strings, one for each byte:
        let hexBytes = bytes.map { String(format: "%02hhx", $0) }
        // Concatenate all hex strings:
        return hexBytes.joinWithSeparator("")
    }
}
