//
//  ViewController.swift
//  apiaccess-ios
//
//

import UIKit
import JWT
class ViewController: UIViewController {

    
    @IBOutlet weak var textView: UITextView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        let endpoint = "user/active-sessions"
        let input:[String : Any] = ["request": true]
        let payload:[String : Any] = [:]
        let obj = apiaccess(api_key: key, api_secret: secret)
        obj.send(path: endpoint, input: input, payload: payload) { (response, error) in
            self.textView.text = response?.rawString()
        }
       
    }


}

