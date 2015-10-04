//
//  ViewController.swift
//  Notification
//
//  Created by Benno Ommerborn on 03.10.15.
//  Copyright © 2015 bommerborn. All rights reserved.
//

import UIKit
import Alamofire

class ViewController: UIViewController {

    @IBAction func buttonPressed(sender: AnyObject) {
        print("test")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        if let auth_token = NSUserDefaults.standardUserDefaults().objectForKey("auth_token") as? NSString,
        let url = NSUserDefaults.standardUserDefaults().objectForKey("api_endpoint") as? NSString {
            Alamofire.request(.GET, (url as String) + "/get_info", parameters: ["token" : auth_token])
                .responseJSON { request, response, result in
                    print(response)
                    print(result)   // result of response serialization
                    
                    if let JSON = result.value {
                        print("JSON: \(JSON)")
                        let balance = JSON["balance"]
                    }
            }
        }
        else {
            print("No auth toklen avaiavle")
        }

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

