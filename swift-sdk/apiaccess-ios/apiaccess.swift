//
//  apiaccess.swift
//  apiaccess-ios
//

import Foundation
import JWT
import SwiftyJSON
import Alamofire

class apiaccess {
   static private var api_key = ""
   static private var api_secret = ""
   static public var version=2;
   static public var domain="https://trendingnews.executium.com"
   static public var useragent="API v2 (SWIFT)"
   static public var path=""
   static public var url=""
   static public var endpoints=Array<Any>()
    static public var timeout=3000.0
        init(api_key:String,api_secret:String,api_version:String = "v1") {
            apiaccess.self.api_key = api_key
            apiaccess.self.api_secret = api_secret
        }
    func get_api_url(path:String) -> String
    {
        return (apiaccess.self.domain + "/api/v" + "\(apiaccess.self.version)" + "/" + path)
    }
    
    func set_path(path:String)
    {
        apiaccess.self.path = path
    }
    func get_config()->apiaccess
    {
        return self;
    }
    func send(path:String,input:[String : Any],payload:[String : Any],completionBlock: @escaping(_ response:JSON?, _ error:String?)->Void)
    {
        set_path(path: path)
        apiaccess.post(input: input, payload: payload) { (response, error) in
            if error == nil {
                 completionBlock(response!,nil)
            }else{
                completionBlock(nil,error)
            }
           
        }
    }
    
    class func nonce()->String
    {
        let formater = NumberFormatter()
        formater.groupingSeparator = ""
        formater.numberStyle = .decimal
        let currentTime = getCurrentmicro()
        let formattedNumber = formater.string(from: NSNumber(value: currentTime))
        return formattedNumber!
    }
    
    class func getCurrentmicro()->Int64 {
        return Int64(Date().timeIntervalSince1970 * 10000000)
    }
    
    class func generateToken(forNonce nonce: String?, secret: String?) -> String? {
        let payload = [
            "nonce": nonce
        ]
        let secret = secret
        let algorithm = JWTAlgorithmFactory.algorithm(byName: "HS256")
        return JWT.encodePayload(payload as [AnyHashable : Any], withSecret: secret, algorithm: algorithm)
    }
    
    class func post(input:[String : Any],payload:[String : Any],completionBlock: @escaping(_ response:JSON?, _ error:String?)->Void){
        if let token =  apiaccess.generateToken(forNonce: apiaccess.nonce(), secret: secret) {
            let url = apiaccess.domain + "/api/v" + "\(apiaccess.version)" + "/" + apiaccess.path
            let headers: HTTPHeaders = [
                "Authorization": token,
                "Accept": "application/json",
                "Key" : api_key,
                "User-Agent": useragent
            ]
            let manager = Alamofire.SessionManager.default
            manager.session.configuration.timeoutIntervalForRequest = timeout/3
            manager.request(url,method:.post,parameters: input,headers: headers).responseJSON(completionHandler: { (response) in
                switch response.result {
                case .success(_):
                    if let data = response.data
                    {
                      let data = try! JSON(data: data)
                        completionBlock(data,nil)
                        
                    }
                    break
                case .failure(_):
                    if response.result.value != nil
                    {
                        completionBlock(nil,"error")
                    }
                }
            })
        }
    }
}
