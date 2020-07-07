package org.example;

import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.io.IOException;
import java.net.URI;
import java.net.URLEncoder;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.nio.charset.StandardCharsets;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.time.Duration;
import java.time.ZoneId;
import java.util.*;

// org.example.APIAccess class is the object that will be implementing org.example.API interface
public class APIAccess implements API {
    Map<Object, Object> payload;
    private String apiKey;
    private String apiSecret;
    private int version;
    private String domain;
    private String userAgent;
    private String path;
    private String URL;
    private List<String> endPoints;
    private int timeout;

    // Constructor
    public APIAccess(String apiKey, String apiSecret) {
        this.apiKey = apiKey;
        this.apiSecret = apiSecret;
        this.version = 2;
        domain = "https://trendingnews.executium.com";
        userAgent = "org.example.API v2";
        timeout = 3000;
    }

    // Encode request body to pushed with post call
    private static HttpRequest.BodyPublisher buildFormDataFromMap(Map<Object, Object> data) {
        var builder = new StringBuilder();
        for (Map.Entry<Object, Object> entry : data.entrySet()) {
            if (builder.length() > 0) {
                builder.append("&");
            }
            builder.append(URLEncoder.encode(entry.getKey().toString(), StandardCharsets.UTF_8));
            builder.append("=");
            builder.append(URLEncoder.encode(entry.getValue().toString(), StandardCharsets.UTF_8));
        }
        return HttpRequest.BodyPublishers.ofString(builder.toString());
    }

    /* config is a ApiAccess implementation of org.example.API interface function config
      It receives a map of key-value pairs with which org.example.APIAccess can be initialized
    */

    @Override
    public void config(Map<String, ?> arr) {
        for (String key : arr.keySet()) {
            switch (key) {
                case "version":
                    this.version = Integer.parseInt(String.valueOf(arr.get(key)));
                    break;
                case "domain":
                    this.domain = String.valueOf(arr.get(key));
                    break;
                case "useragent":
                    this.userAgent = String.valueOf(arr.get(key));
                    break;
                case "path":
                    this.path = String.valueOf(arr.get(key));
                    break;
                case "url":
                    this.URL = String.valueOf(arr.get(key));
                    break;
                case "endpoints":
                    this.endPoints = (List<String>) arr.get(key);
                case "timeout":
                    this.timeout = Integer.parseInt(String.valueOf(arr.get(key)));
                    break;


            }
        }
    }

    /* getAPIURL is a org.example.APIAccess implementation of org.example.API interface function getAPIURL
       It returns full org.example.API URL by concatenating domain name with api version and path
     */
    @Override
    public String getAPIURL(String path) {
        return this.domain + "/api/v" + this.version + "/" + path;
    }

    /* setPath is a org.example.APIAccess implementation of org.example.API interface function setPath
       It sets the path inside the struct to the one that is passed as argument
     */
    @Override
    public void setPath(String path) {
        this.path = path;
    }

    /* getConfig is a org.example.APIAccess implementation of org.example.API interface function getConfig
       It returns configuration set up inside APIAccessStruct
       */
    @Override
    public APIAccess getConfig() {
        return this;
    }

    /* send is a org.example.APIAccess implementation of org.example.API interface function send
       It sets the path for org.example.API call and executes the POST request to org.example.API
       */
    @Override
    public PostResponse send(String path, Map<Object, Object> input, Map<Object, Object> payload) {
        this.setPath(path);
        return this.post(input, payload);
    }

    /* nonce is a org.example.APIAccess implementation of org.example.API interface function nonce
       It creates a nonce like given in requirements
     */
    @Override
    public String nonce() {
        NanoClock nanoClock = new NanoClock(ZoneId.systemDefault());
        return String.valueOf(nanoClock.nanos()).substring(0, 17);
    }

    /* auth is a org.example.APIAccess implementation of org.example.API interface function auth
       It creates an authorization token passed to the org.example.API
     */
    @Override
    public String auth() {
        try {
            String b01 = Base64.getEncoder().encodeToString("{\"typ\":\"JWT\",\"alg\":\"HS256\"}".getBytes()).replaceAll("\"[+-=_/]+\"", "");
            this.payload.put("nonce", this.nonce());
            String b02 = Base64.getEncoder().encodeToString(JSONValue.toJSONString(this.payload).getBytes()).replaceAll("\"[+-=_/]+\"", "");
            Mac sha256_HMAC = Mac.getInstance("HmacSHA256");
            sha256_HMAC.init(new SecretKeySpec(this.apiSecret.getBytes(), "HmacSHA256"));
            String b03 = Base64.getEncoder().encodeToString(sha256_HMAC.doFinal((b01 + "." + b02).getBytes())).replaceAll("\"[+-=_/]+\"", "");
            return b01 + "." + b02 + "." + b03;
        } catch (NoSuchAlgorithmException | InvalidKeyException e) {
            e.printStackTrace();
        }
        return "";

    }

    /* post is a org.example.APIAccess implementation of org.example.API interface function post
       It executes a Post request
     */
    @Override
    public PostResponse post(Map<Object, Object> input, Map<Object, Object> payload) {
        this.payload = payload;
        this.URL = domain + "/api/v" + version + "/" + path;
        HttpRequest request;
        HttpClient httpClient = HttpClient.newBuilder()
                .version(HttpClient.Version.HTTP_2)
                .connectTimeout(Duration.ofMillis(this.timeout))
                .build();
        if (input.size() > 0) {
            request = HttpRequest.newBuilder()
                    .POST(buildFormDataFromMap(input))
                    .headers("Key", this.apiKey, "Authorization", this.auth(), "Content-Type", "application/x-www-form-urlencoded", "User-Agent", this.userAgent)
                    .uri(URI.create(this.URL))
                    .build();
        } else {
            request = HttpRequest.newBuilder()
                    .GET()
                    .headers("Key", this.apiKey, "Authorization", this.auth(), "Content-Type", "application/x-www-form-urlencoded", "User-Agent", this.userAgent)
                    .uri(URI.create(this.URL))
                    .build();
        }
        HttpResponse<String> response = null;
        try {
            response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        Map<Object, Object> parsed = (Map<Object, Object>) JSONValue.parse(response.body());
        return new PostResponse(parsed, (long) ((JSONObject) parsed.get("meta")).get("status") == 200);
    }

    /* getEndpoints is a org.example.APIAccess implementation of org.example.API interface function getEndpoints
       It returns list of endpoints inside the APIAccessStruct object
       */
    @Override
    public List<String> getEndpoints() {
        return this.getEndpoints();
    }

    /* setEndpoints is a org.example.APIAccess implementation of org.example.API interface function setEndpoints
       It is used to set endpoints of the org.example.APIAccess to response received from calling POST with given input
       */
    @Override
    public void setEndpoints(Map<Object, Object> input) {
        this.setPath("system/ep");
        Map<Object, Object> map = new HashMap<>();
        PostResponse response = this.post(input, map);
        this.endPoints = (List<String>) response.returned.get("data");
    }

    /* decode is a org.example.APIAccess implementation of org.example.API interface function decode
       It decodes bytes passed as arguments
     */
    @Override
    public Map<String, ?> decode(byte[] result) {
        return (Map<String, ?>) JSONValue.parse(Arrays.toString(result));
    }
}
