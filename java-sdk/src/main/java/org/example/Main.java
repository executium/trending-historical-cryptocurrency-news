package org.example;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public class Main {

    public static void main(String[] args) {
        String apiKey = "";
        String apiSecret = "";
        try (InputStream input = new FileInputStream("src/main/resources/config.properties")) {
            Properties prop = new Properties();
            prop.load(input);
            apiKey = prop.getProperty("api_key");
            apiSecret = prop.getProperty("api_secret");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        API api = new APIAccess(apiKey, apiSecret);
/*
  # Interchange the endpoint and consult the `REST-org.example.API` documentation for the required `input`. `input` is the POST parameters which are required or optional.
*/
        String endPoint = "public/trending-news-data";
        Map<Object, Object> input = new HashMap<>();
        input.put("date", "2020-07-02");
        System.out.println(api.send(endPoint, input, new HashMap<>()).returned);

    }
}
