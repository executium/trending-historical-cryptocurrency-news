# Executium Trending News Java SDK
Within this folder you will find all files related to using JAVA with the executium trending news API.

## Installation

**1.** First of All you need to install JDK(Java Development Kit) on your linux machine
complete guide https://tecadmin.net/install-openjdk-java-ubuntu/

**1.1. Install OpenJDK 11**
```
sudo apt-get install openjdk-11-jre openjdk-11-jdk
```
**1.2. Update environment variables**
```
echo "JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64/" >> /etc/environment
source /etc/environment
```
**1.3. Check the output** 
```
echo $JAVA_HOME #this should output the following:
/usr/lib/jvm/java-11-openjdk-amd64/
``` 
**2. Now you need to install `Maven`** 

Installing `Maven` on `Ubuntu` using apt is a simple, straightforward process.

Start by updating the package index:
```
sudo apt update
```
Next, install Maven by typing the following command:
```
sudo apt install maven
```
Verify the installation by running the mvn -version command:
```
mvn -version
```
The output should look something like this:
```
Apache Maven 3.5.2
Maven home: /usr/share/maven
Java version: 10.0.2, vendor: Oracle Corporation
Java home: /usr/lib/jvm/java-11-openjdk-amd64
Default locale: en_US, platform encoding: ISO-8859-1
OS name: "linux", version: "4.15.0-36-generic", arch: "amd64", family: "unix"
```
**3. Open terminal in root directory of project and type**
```
mvn assembly:assembly  #This will generate Jar JAVA-1.0.jar in root directory
```
Now run
```
java -jar JAVA-1.0.jar
```
The output should look something like the following:
``` javascript
{"data":[{"date":{"format2":"2nd July 2020 00:00","format1":"2020-07-02","time_published":"1593648000","day":"Thursday"},"brief":"BTC\/USD bulls have remained in charge for the second straight day as the price went up from $9237 to $9245 in the early hours of Thursday. The Elli.","image":"\/\/lh5.googleusercontent.c
om\/proxy\/MUsMnQ5mYC-rzwD0GM16EvX4trcwVElzzDSZnynBI2mpQWzyR3F_oYVPP5saZ1F2Q2MW_DKBqwk-OgdRjD5e-VpI_jHkAhXXtBJRFOsTax9SHxPhB1hgBIyoVl5-5kQLAoyVNZe5nA7k58UuLSlcs-vsNzJdTmx6pXCxiJwVTqie3g","keywords":"bitcoin,BTC\/USD,bitcoin price","tone":{"data":[],"status":"Subscription required."},"author":"","price_impact_300s":{
"data":[],"status":"Subscription required."},"source":"FXStreet","price_impact_600s":{"data":[],"status":"Subscription required."},"price_impact_1800s":{"data":[],"status":"Subscription required."},"title":"Bitcoin Price Forecast: BTC\/USD bulls stay in control for the second straight day as price makes a charge tow
ards $9,250","url":"https:\/\/www.fxstreet.com\/cryptocurrencies\/news\/bitcoin-price-forecast-btc-usd-bulls-stay-in-control-for-the-second-straight-day-as-price-makes-a-charge-towards-9-250-202007020042","price_impact_120s":{"data":[],"status":"Subscription required."},"price_impact_1200s":{"data":[],"status":"Subs
cription required."},"price_impact_3600s":{"data":{"btcusdt":{"before":"9224.70000000","difference":"-3.61000000","after":"9221.09000000","pair":"BTCUSDT","status":"compiled"} 
...
...

```

## API `key` and `secret`
You can locate and configure these at `java\src\main\resources\config.properties`

These are called in the `src/main/java/org/example/Main.java` file.
```javascript
API api = new APIAccess(apiKey, apiSecret);
```
## Changing the `endpoint`
You can modify the `endpoint` at `src/main/java/org/example/Main.java`. As part of this package it is set to `public/trending-news-data`

```java
String endPoint = "public/trending-news-data";
```
