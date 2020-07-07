package org.example;

import java.util.Map;

// org.example.PostResponse contains data returned from POST request
public class PostResponse {
    boolean success;
    Map<Object, Object> returned;

    public PostResponse(Map<Object, Object> returned, boolean success) {
        this.returned = returned;
        this.success = success;
    }
}
