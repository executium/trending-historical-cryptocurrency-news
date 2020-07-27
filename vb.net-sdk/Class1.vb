Imports System.Net
Imports System.Xml
Imports System.Web
Imports System.Security.Cryptography
Imports System.IO

Public Class Class1
    Private api_key As String
    Private api_secret As String

    Private version As String = "2"
    Public domain As String = ""
    Public useragent As String = "API v2 (VB.net)"
    Public path As String = ""
    Public url As String = ""

    Public timeout As Integer = 60000
    Public payload As String

    Public total_time As Double = 0
    Public primary_ip As String
    Public local_ip As String
    Public utc_server_time_difference_sec As Integer

    Public Sub New()
        'This is constructor of class

        Dim doc As New XmlDocument
        doc.Load(AppDomain.CurrentDomain.BaseDirectory + "\\Config.xml")
        Dim node As XmlNode = doc.SelectSingleNode("/Settings")
        Me.api_key = node.SelectSingleNode("key").InnerText
        Me.api_secret = node.SelectSingleNode("secret").InnerText
        Me.domain = node.SelectSingleNode("domain").InnerText
        Me.path = node.SelectSingleNode("endpoint").InnerText
        Me.version = node.SelectSingleNode("version").InnerText
        Me.utc_server_time_difference_sec = Convert.ToInt64(node.SelectSingleNode("utc_server_time_difference_sec").InnerText)
        Console.WriteLine("Configuration file successfully loaded..")

    End Sub
   


    Public Function nonce() As String
        Dim tstamp As Single = 0
        Dim timeNow As DateTime = DateTime.UtcNow
        Dim baseTime As DateTime = New DateTime(1970, 1, 1, 0, 0, 0)
        Dim tSpan As TimeSpan = timeNow.Subtract(baseTime)
        tstamp = (tSpan.Days * 86400) + (tSpan.Hours * 3600) + (tSpan.Minutes * 60) + tSpan.Seconds
        tstamp = (tstamp + (tSpan.Milliseconds / 1000)) + Me.utc_server_time_difference_sec
        Console.WriteLine("nonce successfully created..")
        Return String.Format("{0:n0}", Math.Round(tstamp * 10000000)).Replace(",", "")

    End Function

    Public Function auth() As String
        Dim payload, b1, b01, b02, b03 As String
        payload = "{""nonce"":""" & Me.nonce() & """}"
        b1 = "{""typ"":""JWT"",""alg"":""HS256""}"
        b01 = System.Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(b1)).Replace("+"c, "-"c).Replace("/"c, "_"c).Replace("=", "")
        b02 = System.Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(payload)).Replace("+"c, "-"c).Replace("/"c, "_"c).Replace("=", "")
        Dim secret = System.Text.Encoding.UTF8.GetBytes(Me.api_secret)
        Dim hmac = New HMACSHA256(secret)
        Dim sig = hmac.ComputeHash(System.Text.Encoding.UTF8.GetBytes(b01 & "."c & b02))
        b03 = System.Convert.ToBase64String(sig).Replace("+"c, "-"c).Replace("/"c, "_"c).Replace("=", "")

        Console.WriteLine("auth string successfully created...")

        Return b01 & "."c & b02 & "."c & b03
    End Function
    Public Function send(ByVal input As String) As String
        Return Me.post(input)
    End Function

    Public Function post(ByVal input As String) As String
        Me.url = Me.domain & "/api/v" + Me.version + "/"c + Me.path
        Dim success As Int32 = 0
        Dim returned As String = ""
        Dim network_info As String = ""
        Dim json As String = ""
        Dim request As HttpWebRequest = CType(WebRequest.Create(Me.url), HttpWebRequest)

        If request IsNot Nothing Then
            request.ContentType = "application/x-www-form-urlencoded"
            request.Timeout = Me.timeout
            request.UserAgent = Me.useragent
            request.Headers("Key") = Me.api_key
            request.Headers("Authorization") = Me.auth()
            request.Method = "POST"

            Console.WriteLine("sending request to end point =" & Me.url)
            If input IsNot Nothing And input.Length > 0 Then
                request.ContentLength = input.Length

                Using dataStream = request.GetRequestStream()
                    dataStream.Write(System.Text.Encoding.UTF8.GetBytes(input), 0, input.Length)
                End Using
            End If

            Try
                Dim timer As System.Diagnostics.Stopwatch = New Stopwatch()
                timer.Start()
                Dim response As HttpWebResponse = TryCast(request.GetResponse(), HttpWebResponse)
                timer.[Stop]()
                Me.total_time = Convert.ToDouble(timer.ElapsedMilliseconds) / 1000.0
                Dim result As String = ""

                Using responseStream As Stream = response.GetResponseStream()
                    Dim reader As StreamReader = New StreamReader(responseStream, System.Text.Encoding.UTF8)
                    result += reader.ReadToEnd()
                End Using

                Console.WriteLine("end point successfull sent result = ")
                Console.WriteLine()
                Console.WriteLine()

                If result Is Nothing OrElse result = String.Empty Then
                    success = 0
                    returned = result
                    network_info = Me.get_network_info(response, request)
                Else
                    success = 1
                    returned = result
                    network_info = Me.get_network_info(response, request)
                End If

                json += "{"
                json += """success"":" & success & ","
                json += """returned"":" & returned & ","
                json += """network_info"":" & network_info & ""
                json += "}"
            Catch e As Exception
                json = "{""code"":100,""error"":""" & e.Message & """}"
            End Try
        Else
            json = """code"":100,""error"":""Asp.Net HttpWebRequest not enabled"""
        End If

        Return json
    End Function
    Public Function get_network_info(ByVal response As HttpWebResponse, ByVal request As HttpWebRequest) As String
        Dim info As String = "{"
        info += """url"":""" & response.ResponseUri.ToString() & ""","
        info += """content_type"":""" & response.ContentType & ""","
        info += """http_code"":" & Convert.ToInt32(response.StatusCode) & ","
        Dim RequestHeaderSize As Double = 0

        For Each key As String In request.Headers.AllKeys
            RequestHeaderSize += request.Headers(key).Length
        Next

        Dim HeaderSize As Double = 0

        For Each key As String In response.Headers.AllKeys
            HeaderSize += response.Headers(key).Length
        Next

        Dim hostname As String = response.ResponseUri.Host
        Dim host As IPHostEntry
        host = Dns.GetHostEntry(hostname)
        Me.primary_ip = ""

        For Each ip As IPAddress In host.AddressList
            Me.primary_ip = ip.ToString()
            Exit For
        Next

        info += """header_size"":" & HeaderSize & ","
        info += """request_size"":" & (request.ContentLength + RequestHeaderSize) & ","
        info += """filetime"":-1,"
        info += """ssl_verify_result"":0,"
        info += """redirect_count"":0,"
        info += """total_time"":" & Me.total_time & ","
        info += """namelookup_time"":"""","
        info += """connect_time"":"""","
        info += """pretransfer_time"":"""","
        info += """size_upload"":" & request.ContentLength & ","
        info += """size_download"":" & response.ContentLength & ","
        info += """speed_download"":"""","
        info += """speed_upload"":"""","
        info += """download_content_length"":" & (response.ContentLength + HeaderSize) & ","
        info += """upload_content_length"":" & request.ContentLength & ","
        info += """starttransfer_time"":"""","
        info += """redirect_time"":"""","
        info += """redirect_url"":"""","
        info += """primary_ip"":""" & Me.primary_ip & ""","
        info += """certinfo"":[{}],"
        info += """primary_port"":" & response.ResponseUri.Port & ","
        info += """local_ip"":""" & Me.GetLocalIPAddress() & ""","
        info += """local_port"":"""""
        info += "}"
        Return info
    End Function
    Public Function GetLocalIPAddress() As String
        Dim ipHostInfo As IPHostEntry = Dns.GetHostEntry(Dns.GetHostName())
        Dim ipAddress As IPAddress = ipHostInfo.AddressList(0)
        Return ipAddress.ToString()
    End Function

End Class
