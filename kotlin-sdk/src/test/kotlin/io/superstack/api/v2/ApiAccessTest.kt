package io.trendingnews.api.v2

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test
import java.util.*

internal class ApiAccessTest {


    @Test
    fun `b01, this does not change`() {
        // $payload=array();
        // $payload['nonce']=nonce();
        // $api_secret = "";
        val b01 = ""

        val encodeBase64 = Base64.getEncoder()::encodeToString

        // pay attention to to how the characters are escaped in the String
        val encoded = encodeBase64("{\"typ\":\"JWT\",\"alg\":\"HS256\"}".toByteArray()).replaceCharacters()
        assertEquals(b01, encoded)
    }

    @Test
    fun `the usage of the api`() {
        main()
    }
}