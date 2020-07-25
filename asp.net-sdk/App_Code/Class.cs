using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Security.Cryptography;
using System.Web;
using System.Xml;


/// <summary>
/// Summary description for Class
/// </summary>
public class Class
{
    private string api_key = "";
	private string api_secret = "";

    /**
       * @param string api_key       Your API key obtained from executium.com
       * @param string api_secret    Your API secret obtained from example.com
    */
    public string version="2";
	public string domain="https://trendingnews.executium.com";
	public string useragent="API v2 (ASP.net)";
	public string path="";
	public string url="";
    public string[] endpoints;
	public Int32 timeout=3000;
    public string[] payload;

    public double total_time = 0;
    public string primary_ip;
    public string local_ip;
    public Int64 utc_server_time_difference_sec;

    public Class( )
	{
        //Reading Config.xml file to get api &  secret
        XmlDocument doc = new XmlDocument();
        doc.Load(AppDomain.CurrentDomain.BaseDirectory+ "\\App_Code\\Config.xml");
        XmlNode node = doc.SelectSingleNode("/Settings");
        this.api_key = node.SelectSingleNode("key").InnerText;
        this.api_secret = node.SelectSingleNode("secret").InnerText;
        utc_server_time_difference_sec = Convert.ToInt64(node.SelectSingleNode("utc_server_time_difference_sec").InnerText);
        
	}

    public string get_api_url(string path)
    {
        return this.domain + "/api/v" + this.version + "/" + path;
    }

    public void set_path( string path)
    {
        this.path = path;
    }

    public string[] get_endpoints()
    {
        return this.endpoints;
    }


    public string nonce()
    {

        //This function is used to calculate nonce through UnixTimeStamp
       float tstamp=0;
        DateTime timeNow  = DateTime.Now ;
        DateTime baseTime = new DateTime(1970,1,1,0,0,0);
        TimeSpan tSpan = timeNow.Subtract(baseTime);
        tstamp = (tSpan.Days * 86400) + (tSpan.Hours * 3600) + (tSpan.Minutes * 60) + tSpan.Seconds ;

        //If Your server's UTC Time not matching with end point server then adjust second adding or subtracting difference in second
        tstamp = (tstamp + (tSpan.Milliseconds / 1000)) + this.utc_server_time_difference_sec;

        return String.Format("{0:n0}", Math.Round(tstamp*10000000)).Replace(",","");

    }

    public string auth()
    {
        string payload,b1,b01,b02,b03;
        payload= "{\"nonce\":\""+this.nonce()+"\"}";
        b1= "{\"typ\":\"JWT\",\"alg\":\"HS256\"}";
        b01 =  System.Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(b1)).Replace('+','-').Replace('/','_').Replace("=","");
        b02 =  System.Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(payload)).Replace('+','-').Replace('/','_').Replace("=","");

        //Calculating Signature
        var secret = System.Text.Encoding.UTF8.GetBytes(this.api_secret);
        var hmac = new HMACSHA256(secret);
        var sig = hmac.ComputeHash(System.Text.Encoding.UTF8.GetBytes(b01+'.'+b02));
        b03 =  System.Convert.ToBase64String(sig).Replace('+','-').Replace('/','_').Replace("=","");

        return b01+'.'+b02+'.'+b03;
    }


    public string send(string path, string input)
    {
        this.set_path(path);
        return this.post(input);
    }

    public string post(string input)
    {
        
        this.url = this.domain + "/api/v" + this.version + '/' + this.path;
        Int32 success = 0;
        string returned = "";
        string network_info = "";
        string json = "";
        
        HttpWebRequest request = (HttpWebRequest)WebRequest.Create(this.url);

        if(request!=null)
        {
       
            request.ContentType = "application/x-www-form-urlencoded";
            request.Timeout = this.timeout;
            request.UserAgent = this.useragent;
            request.Headers["Key"] = this.api_key;
            request.Headers["Authorization"] = this.auth();
            request.Method ="POST";

           if (input != null & input.Length>0)
           {
               request.ContentLength = input.Length;
               using (var dataStream = request.GetRequestStream())
               {
                   dataStream.Write(System.Text.Encoding.UTF8.GetBytes(input), 0, input.Length);
               }
           }

           try
           {

               System.Diagnostics.Stopwatch timer = new Stopwatch();
               timer.Start();
               HttpWebResponse response = request.GetResponse() as HttpWebResponse;

               timer.Stop();

               this.total_time = Convert.ToDouble ( timer.ElapsedMilliseconds) / 1000.00; //seconds

               string result = "";

               using (Stream responseStream = response.GetResponseStream())
               {
                   StreamReader reader = new StreamReader(responseStream, System.Text.Encoding.UTF8);
                   result += reader.ReadToEnd();

               }

               if (result == null || result == String.Empty)
               {
                   success = 0;
                   returned = result;
                   network_info = this.get_network_info(response, request);
               }
               else
               {
                   success = 1;
                   returned = result;
                   network_info = this.get_network_info(response, request);
               }

               json += "{";
               json += "\"success\":" + success + ",";
               json += "\"returned\":" + returned + ",";
               json += "\"network_info\":" + network_info + "";
               json += "}";
           }
           catch (Exception e)
           {
               json = "{\"code\":100,\"error\":\""+e.Message+"\"}";
           }
        }
        else
        {
            json = "\"code\":100,\"error\":\"Asp.Net HttpWebRequest not enabled\"";
        }

        return json;
    }

    public string get_network_info(HttpWebResponse response, HttpWebRequest request)
    {
        string info="{";
        info += "\"url\":\"" + response.ResponseUri + "\",";
        info += "\"content_type\":\"" + response.ContentType + "\",";
       
        info += "\"http_code\":" + Convert.ToInt32(response.StatusCode) + ",";

        //getting request Header Size
        Double RequestHeaderSize = 0;
        foreach (string key in request.Headers.AllKeys)
        {
            RequestHeaderSize += request.Headers[key].Length;
        }

        //getting response header size
        Double HeaderSize = 0;
        foreach (string key in response.Headers.AllKeys)
       {
           HeaderSize+= response.Headers[key].Length;
       }

      
        //getting remote ip of end point server
        string hostname = response.ResponseUri.Host;
        IPHostEntry host;
        host = Dns.GetHostEntry(hostname);
        this.primary_ip="";
        foreach (IPAddress ip in host.AddressList)
        {
            this.primary_ip = ip.ToString();
            break;
        }

        info += "\"header_size\":" + HeaderSize + ",";
        info += "\"request_size\":" + (request.ContentLength + RequestHeaderSize) + ",";
        info += "\"filetime\":-1,";
        info += "\"ssl_verify_result\":0,";
        info += "\"redirect_count\":0,";
        info += "\"total_time\":"+this.total_time+",";
        info += "\"namelookup_time\":\"\",";
        info += "\"connect_time\":\"\",";
        info += "\"pretransfer_time\":\"\",";
        info += "\"size_upload\":" + request.ContentLength + ",";
        info += "\"size_download\":"+response.ContentLength+",";
        info += "\"speed_download\":\"\",";
        info += "\"speed_upload\":\"\",";

         info += "\"download_content_length\":"+(response.ContentLength+HeaderSize)+",";
         info += "\"upload_content_length\":"+request.ContentLength+",";
         info += "\"starttransfer_time\":\"\",";
         info += "\"redirect_time\":\"\",";
         info += "\"redirect_url\":\"\",";

         info += "\"primary_ip\":\"" + this.primary_ip + "\",";
         info += "\"certinfo\":[{}],";
         info += "\"primary_port\":" + response.ResponseUri.Port + ",";
         info += "\"local_ip\":\"" + this.GetLocalIPAddress() + "\",";
         info += "\"local_port\":\"" + HttpContext.Current.Request.ServerVariables["SERVER_PORT"] + "\"";
        

        info += "}";
        return info;
    }

    public string GetLocalIPAddress()
    {
        //This function is used to get local ip address.

        IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName()); // `Dns.Resolve()` method is deprecated.
        IPAddress ipAddress = ipHostInfo.AddressList[0];

        return ipAddress.ToString();
    }

}