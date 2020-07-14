# Executium Trending News - SWIFT
All files can be adapted for any iOS application where required.

## Requirements

- iOS 13.0+
- Xcode 11

## Installation
Open the project root folder in terminal and then run the command `pod install` 

``` r
1: cd ./apiaccess-ios 
2: pod install
```

## Example
ViewController.swift

``` r
import UIKit
import JWT
class ViewController: UIViewController {
    @IBOutlet weak var textView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let endpoint = "public/trending-news-data"
        let input:[String : Any] = ["request": "2020-07-14"]
        let payload:[String : Any] = [:]
        let obj = apiaccess(api_key: key, api_secret: secret)
        obj.send(path: endpoint, input: input, payload: payload) { (response, error) in
            self.textView.text = response?.rawString()
        }  
    }
}
```
config.swift

``` r

import Foundation
var key=""
var secret="";
```

## References
- Alamofire https://github.com/Alamofire/Alamofire
- SwiftyJSON https://github.com/SwiftyJSON/SwiftyJSON
- JWT https://github.com/yourkarma/JWT
