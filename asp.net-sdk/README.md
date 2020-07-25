# Executium Trending News ASP.net SDK
**Table of Contents**

- Server Requirement
- Attached Source Code
	- Config.xml
	- Class.cs
	- Default.aspx
	
1. Server Requirment
	- This project was build in Microsoft Visual Studio 2013 IDE Kit
	- This Website can be hosted on any Window Server That Support Asp.Net website.
	- Minmum .Net Framework Required is .Net Framework 4.5
	
2. Attched Source Code
	- You can see below mentioned files in Source code
	- App_Code/Config.xml
	- App_Code/Class.cs
	- Default.Aspx.cs
	- Default.aspx
	- Web.config
	
	2.1 Config.xml
		This is configuration file it has following values
			- key : it is api key
			- secret: it is api secret
			- utc_server_time_difference_sec : if there is difference in your server's UTC time and Remote Server's UTC time, then use this parameter to mentioned difference in second. e.g for example, if your server's UTC clock is 240 second ahead of standard UTC timezone, you would then subtract by 240 second to calculate the nonce.
	
    2.1 Class.cs : This is main code file . It has code to send request to end point and returned result in json format. All methods inside have comment to better understand
	
	2.2 Default.aspx: This page is used display Json data that was returned from Class.cs. We used javascript to beautify json data on page.


												 		
