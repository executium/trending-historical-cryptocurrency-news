# Executium Trending News - VB.net SDK

1. Software Requirement
	- This project was build in Microsoft Visual Studio 2010 IDE Kit.
	- Minmum .Net Framework Required is .net Framework 4.5

2. How to Open Project	
    - Download and Install Microsoft Visual Studio 2010 or Later version
	- Run Microsoft Visual Studio 2010
	- and Now Open "API-VBNET.sln" project in IDE

3. How to run program without Visual Studio
	- Go to Project Root Directory
	- Explore bin\debug direcoty.
	- Double click or run as Administrator "API-VBNET.exe" file.
	- You will get result on console screen. 
	
4. Attched Source Code
	- Config.xml
	- Class1.vb
	- Module1.vb
	- Confix.xml :- This contains following configuration information
        - api : the api key
        - secret : the api secret
		- domain : the domain url (e.g. https://trendingnews.executium.com)
		- endpoint : the endpoint of domain (e.g public/trending-news-data)
		- version: it is version of api
		- utc_server_time_difference_sec : it is UTC time difference , in my PC or Window Server there is difference of -240 seconds.
			
	- Class1.vb
        - This is our actual source code it has coding to sent request to end point and getting json response from end point.
