package io.trendingnews.api.v2

import org.json.JSONObject
import java.net.HttpURLConnection
import java.net.URL
import java.net.URLEncoder
import java.nio.charset.StandardCharsets
import java.util.*
import javax.crypto.Mac
import javax.crypto.spec.SecretKeySpec

/**
 * @param string apiKey       Your API key obtained from executium.com
 * @param string apiSecret    Your API secret obtained from executium.com
 */
class ApiAccess(val apiKey: String, val apiSecret: String) {

    var version = 2;
    var domain = "https://trendingnews.executium.com"
    var userAgent = "API v2 Kotlin"
    var path = ""
    var url = ""
    var endpoints: List<String> = arrayListOf<String>()
    var timeout = 3000 // milliseconds
    var payload = mutableMapOf<String, Any>()

    fun nonce(): String {
        val now = java.time.Instant.now()
        val nonce = now.toEpochMilli() * 10000 + Random().nextInt(10000).toLong()
        return nonce.toString()
    }


    fun auth(): String {
        payload["nonce"] = nonce()

        val encodeBase64 = Base64.getEncoder()::encodeToString

        val b01 = encodeBase64("{\"typ\":\"JWT\",\"alg\":\"HS256\"}".toByteArray()).replaceCharacters()
        val b02 = encodeBase64(JSONObject(payload).toString().toByteArray()).replaceCharacters()


        val hashingAlgorithm = "HmacSHA256"
        val sha256Mac = Mac.getInstance(hashingAlgorithm)
        sha256Mac.init(SecretKeySpec(apiSecret.toByteArray(), hashingAlgorithm))

        val sig = sha256Mac.doFinal("$b01.$b02".toByteArray())

        val b03 = encodeBase64(sig).replaceCharacters()

        return "$b01.$b02.$b03"
    }

    fun post(input: Map<String, Any>, payload: MutableMap<String, Any>): JSONObject? {

        this.payload = payload
        url = "$domain/api/v$version/$path"


        with(URL(url).openConnection() as HttpURLConnection) {

            requestMethod = "POST"

            doOutput = true
            readTimeout = timeout // this corresponds to CURLOPT_TIMEOUT_MS
            instanceFollowRedirects = true // CURLOPT_FOLLOWLOCATION, TRUE
            setRequestProperty("User-Agent", userAgent) // CURLOPT_USERAGENT
            setRequestProperty("Key", apiKey)
            setRequestProperty("Authorization", auth())

            // Some other options that could be set:
            // connectTimeout = timeout // this corresponds to CURLOPT_CONNECTTIMEOUT_MS
            // contentType = "application/x-www-form-urlencoded; charset=UTF-8");

            // beware: the "Authorization" header is set correctly, but this wouldn't display it
            // println(requestProperties)
            // save for later
            val networkInfo = mutableMapOf<String, Any>().apply {
                put("url", url)
                put("request_method", requestMethod)
                put("endpoints", endpoints)
                put("read_timeout", readTimeout)
                put("connection_timeout", connectTimeout)
                put("follow_redirects", instanceFollowRedirects)
                put("using_proxy", usingProxy())
                putAll(requestProperties)
            }

            // Sending the request
            connect()
            outputStream.bufferedWriter().use {
                if (input.isNotEmpty()) {
                    val postData = input.entries.map {
                        val key = URLEncoder.encode(it.key, StandardCharsets.UTF_8.toString())
                        val value = URLEncoder.encode(it.value.toString(), StandardCharsets.UTF_8.toString())
                        return@map "$key=$value"
                    }.joinToString("&")
                    it.write(postData)
                }
            }


            // Receiving the response
            inputStream.bufferedReader().use {
                val responseText = it.readText()

                if (responseCode == HttpURLConnection.HTTP_OK && responseText.isNotEmpty()) {
                    val responseJson = JSONObject(responseText)
                    // set the endpoints from the json, so it can be accessed later
                    endpoints = responseJson.getJSONArray("data").map { it.toString() }.toList()
                    return JSONObject().apply {
                        put("success", true)
                        put("returned", responseJson)
                        put("network_info", JSONObject(networkInfo))
                    }
                } else {
                    return JSONObject().apply {
                        put("success", false)
                        put("returned", responseText)
                        put("network_info", JSONObject(networkInfo))
                    }
                }
            }
        }
    }

    fun send(path: String, input: Map<String, Boolean>, payload: MutableMap<String, Any>): JSONObject? {
        this.path = path
        return post(input, payload)
    }
}

fun String.replaceCharacters() =
    replace("+", "-")
        .replace("/", "_")
        .replace("=", "")

