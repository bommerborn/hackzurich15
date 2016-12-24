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
        
        self.mainLabel?.setText(String(format: "%.2f", Float(7.42)) + "€")
    }

    override func didDeactivate() {
        // This method is called when watch view controller is no longer visible
        super.didDeactivate()
    }

}
