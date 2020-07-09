# C# Example of API use

This example is <b>.Net Console application </b> that uses .Net Framework 4.5 and library for JSON decoding [Newtonsoft.Json](https://www.nuget.org/packages/Newtonsoft.Json/) that is available on nuget for <b>.Net</b> and <b>.Net Core</b>

## Instructions

* Pull Project
* Compile
* Run 

## Files to modify
If you wish to change the `endpoint`, you can access `CSharpExample/Program.cs`. This file provides a lot of the routine and functionality that you will be seeking.

If you are looking to modify data around `useragent` or any connection related variables then `CSharpExample/ApiAccess.cs` is the location for that.

## Authentication

* The API `key` and `secret` are located in `CSharpExample/Config.cs`

## Sample code that utilizes `ApiAccess.cs`

```
// Set Endpoint
var endpoint = "public/trending-news-data";

// Input payload that is send by POST method
var input = new Dictionary<string, string> {{"date", "2020-07-04"}};

// Initialize with Api Key and Api Secret
var apiAccess = new ApiAccess(Config.Key, Config.Secret);

// Post input payload to the specified endpoint
var result = await apiAccess.Send(endpoint, input, new List<string>());

// Write result
Console.WriteLine(result);
```
