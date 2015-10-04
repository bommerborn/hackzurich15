//
//  GlanceController.swift
//  WatchApp Extension
//
//  Created by Benno Ommerborn on 03.10.15.
//  Copyright © 2015 bommerborn. All rights reserved.
//

import WatchKit
import Foundation
import Alamofire

class GlanceController: WKInterfaceController {

    @IBOutlet weak var mainLabel: WKInterfaceLabel?
    
    override func awakeWithContext(context: AnyObject?) {
        super.awakeWithContext(context)
        
        // Configure interface objects here.
    }

    override func willActivate() {
        // This method is called when watch view controller is about to be visible to user
        super.willActivate()
        
        Alamofire.request(.GET, "http://172.27.3.49:5000/get_info", parameters: ["token" : "TEVPTi5CRVJOQVJEQEFYSU9NQy5DT006YXhpb20="])
            .responseJSON { request, response, result in
                print(response)
                print(result)   // result of response serialization
                
                if let JSON = result.value,
                    let balance = JSON["balance"] as? NSNumber {
                    self.mainLabel?.setText(String(format: "%.2f", Float(balance)) + "€")
                }
        }
    }

    override func didDeactivate() {
        // This method is called when watch view controller is no longer visible
        super.didDeactivate()
    }

}
