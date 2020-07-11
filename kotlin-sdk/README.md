# Kotlin SDK for executium Trending News

### Pre-requisites and Installation

The code was tested with JDK 1.8.0_251. Download and install JDK 8 from Oracle or
from a similar source. The easiest option is probably:
https://adoptopenjdk.net/?variant=openjdk8&jvmVariant=hotspot, but any Java 8 JDK
(not JRE) should be sufficient. 

To run the project, download and install **Gradle** from https://gradle.org/install/,
or via the operating system's package manager. Add the gradle executable's path, for
example the `C:\gradle-6.5.1\bin\` directory to the operating system's PATH 
environment variable. For more info on how to do ths, visit: https://gradle.org/install/

Go to the project folder and type

```
kotlin-sdk/
``` 

Then
```
kotlin-sdk\gradle build
```

Or **import the project into IntelliJ IDEA**, to build and run the program. 


### How to run the program

The are two easy options to run the code.
1. Go to the project folder and type

```
kotlin-sdk\gradle test --info 
``` 
this should run the tests (there are 2 of them) and one of them executes an authorized api
request.

2. Open the `Usage.kt` file and press the IDE's run button to execute its main function.   

### About the code


There are 3 files in total. The bulk of the program is implemented in `ApiAccess.kt`,
 The code can be run via the `main` function inside `Usage.kt`.

In the JVM / Android world api keys and secrets can come from many places, for
example injected via an IoC container, from properties files, from XML files,
from JSON files, from shared preferences, from environment variables, container
orchestration.... so it is best to just simply show how to use them instead.

Create an instance:
```kotlin
val api = ApiAccess(
    "",
    ""
)
```
Set the endpoint, the input, and send a request to the API.
```kotlin
val endpoint = "public/trending-news-data"
val input = mapOf("date" to "2020-07-05")
val result = api.send(endpoint, input, mutableMapOf())
```

Print the results as a nicely indented JSON:    
```kotlin
println("${result?.toString(4)}")

println("The endpoints are: ${api.endpoints}")
```

Also note, that there aren't any explicit getter and setter method in kotlin, if you
want to configure an object you can simply use the follow idiom with `.apply {...}`.
A fictional configuration to show how to things change things:
```kotlin
api.apply {
    upgrade the version
    version = 5;
    domain = "https://trendingnews.executium.com"
    userAgent = "API v2 (Kotlin)"
    path = ""
    url = ""
    endpoints = arrayListOf()
    timeout = 7000 // milliseconds
}
```
