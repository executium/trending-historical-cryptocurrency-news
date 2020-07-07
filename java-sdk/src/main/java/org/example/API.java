package org.example;

import java.util.List;
import java.util.Map;

// org.example.API is interface that states which methods need to be implemented
public interface API {
    void config(Map<String, ?> arr);

    String getAPIURL(String path);

    void setPath(String path);

    APIAccess getConfig();

    PostResponse post(Map<Object, Object> input, Map<Object, Object> payload);

    PostResponse send(String path, Map<Object, Object> input, Map<Object, Object> payload);

    String nonce();

    String auth();

    List<String> getEndpoints();

    void setEndpoints(Map<Object, Object> input);

    Map<String, ?> decode(byte[] result);
}
