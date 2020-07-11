package io.trendingnews.api.v2

fun main() {
    // in the JVM / Android world api keys and secrets can come from many places, for example injected via an IoC
    // container, from properties files, from XML files, from JSON files, from shared preferences, from environment
    // variables, container orchestration.... so it is best to just simply show how to use them instead
    val api = ApiAccess(
        "",
        ""
    )

    val endpoint = "public/trending-news-data"
    val input = mapOf("date" to "2020-07-05")
    val result = api.send(endpoint, input, mutableMapOf())

    println("${result?.toString(4)}")

    println("The endpoints are: ${api.endpoints}")


    // A fictional configuration for later when things change
//    api.apply {
//        // upgrade the version
//        version = 5;
//        //
//        domain = "https://trendingnews.executium.com"
//        // but still use the old user agent
//        userAgent = "API v2 (Kotlin)"
//        // this path is also set with with the "endpoint" variable as an argument to api.send(endpoint...)
//        path = ""
//        url = ""
//        endpoints = arrayListOf()
//        timeout = 7000 // milliseconds
//    }
}
