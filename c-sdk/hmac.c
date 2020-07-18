#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/x509.h>
#include <openssl/hmac.h>

void
hmac_sha256(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    void                *digest)    /* caller digest to be filled in */
{
#ifdef  EVP_MAX_MD_SIZE

    unsigned int result_len;
    unsigned char result[EVP_MAX_MD_SIZE];

    HMAC(EVP_sha256(),
         key, strlen(key),
         text, strlen(text),
         result, &result_len);
    memcpy(digest, result, result_len);

#else

    unsigned char k_ipad[65];   /* inner padding -
                                 * key XORd with ipad
                                 */
    unsigned char k_opad[65];   /* outer padding -
                                 * key XORd with opad
                                 */
    unsigned char tk[SHA256_DIGEST_LENGTH];
    unsigned char tk2[SHA256_DIGEST_LENGTH];
    unsigned char bufferIn[1024];
    unsigned char bufferOut[1024];
    int           i;

    /* if key is longer than 64 bytes reset it to key=sha256(key) */
    if ( key_len > 64 ) {
        SHA256( key, key_len, tk );
        key     = tk;
        key_len = SHA256_DIGEST_LENGTH;
    }

    /*
     * the HMAC_SHA256 transform looks like:
     *
     * SHA256(K XOR opad, SHA256(K XOR ipad, text))
     *
     * where K is an n byte key
     * ipad is the byte 0x36 repeated 64 times
     * opad is the byte 0x5c repeated 64 times
     * and text is the data being protected
     */

    /* start out by storing key in pads */
    memset( k_ipad, 0, sizeof k_ipad );
    memset( k_opad, 0, sizeof k_opad );
    memcpy( k_ipad, key, key_len );
    memcpy( k_opad, key, key_len );

    /* XOR key with ipad and opad values */
    for ( i = 0; i < 64; i++ ) {
        k_ipad[i] ^= 0x36;
        k_opad[i] ^= 0x5c;
    }

    /*
     * perform inner SHA256
     */
    memset( bufferIn, 0x00, 1024 );
    memcpy( bufferIn, k_ipad, 64 );
    memcpy( bufferIn + 64, text, text_len );

    SHA256( bufferIn, 64 + text_len, tk2 );

    /*
     * perform outer SHA256
     */
    memset( bufferOut, 0x00, 1024 );
    memcpy( bufferOut, k_opad, 64 );
    memcpy( bufferOut + 64, tk2, SHA256_DIGEST_LENGTH );

    SHA256( bufferOut, 64 + SHA256_DIGEST_LENGTH, digest );

#endif
}

#ifdef  TEST
#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

void
printdump( const char *buffer, size_t sz )
{
    int             i, c;
    unsigned char   buf[80];

    for ( i = 0; (unsigned)i < sz; i++ ) {
        if ( (i != 0) && (i % 16 == 0) ) {
            buf[16] = NUL;
            fprintf( stderr, "    %s\n", buf );
        }
        if ( i % 16 == 0 )
            fprintf( stderr, "%08x:", &buffer[i] );
        c = buffer[i] & 0xFF;
        if ( (c >= ' ') && (c <= 0x7E) )
            buf[i % 16] = (unsigned char)c;
        else
            buf[i % 16] = '.';
        fprintf( stderr, " %02x", c & 0xFF );
    }
    if ( i % 16 == 0 )
        buf[16] = NUL;
    else {
        buf[i % 16] = NUL;
        for ( i = i % 16; i < 16; i++ )
            fputs( "   ", stderr );
    }
    fprintf( stderr, "    %s\n", buf );
}

static char b[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  /* 0000000000111111111122222222223333333333444444444455555555556666 */
  /* 0123456789012345678901234567890123456789012345678901234567890123 */
char    *
base64( const unsigned char *src, size_t sz )
{
    unsigned char               *pp, *p, *q;
    Thread static unsigned char *qq = NULL;
    size_t                      i, safe = sz;

    if ( qq ) {
        free( qq );
        qq = NULL;
    }
    if ( !src || (sz == 0) )
        return ( NULL );

    if ( (sz % 3) == 1 ) {
        p = (unsigned char *)malloc( sz + 2 );
        if ( !p )
            return ( NULL );
        memcpy( p, src, sz );
        p[sz] = p[sz + 1] = '=';
        sz += 2;
    }
    else if ( (sz % 3) == 2 ) {
        p = (unsigned char *)malloc( sz + 1 );
        if ( !p )
            return ( NULL );
        memcpy( p, src, sz );
        p[sz] = '=';
        sz++;
    }
    else
        p = (unsigned char *)src;

    q = (unsigned char *)malloc( (sz / 3) * 4 + 2 );
    if ( !q ) {
        if ( p != src )
            free( p );
        return ( NULL );
    }

    pp = p;
    qq = q;
    for ( i = 0; i < sz; i += 3 ) {
        q[0] = b[(p[0] & 0xFC) >> 2];
        q[1] = b[((p[0] & 0x03) << 4) | ((p[1] & 0xF0) >> 4)];
        q[2] = b[((p[1] & 0x0F) << 2) | ((p[2] & 0xC0) >> 6)];
        q[3] = b[p[2] & 0x3F];
        p += 3;
        q += 4;
    }
    *q = NUL;
    if ( (safe % 3) == 1 ) {
        *(q - 1) = '=';
        *(q - 2) = '=';
    }
    if ( (safe % 3) == 2 )
        *(q - 1) = '=';

    if ( pp != src )
        free( pp );
    return ( (char *)qq );
}
/*
int
main( int argc, char *argv[] )
{
    // via http://docs.amazonwebservices.com/AWSECommerceService/latest/DG/index.html?rest-signature.html
    // see also:
    //    http://chalow.net/2009-05-09-1.html
    //     http://d.hatena.ne.jp/zorio/20090509/1241886502
    char        *p;
    const char  *key = "1234567890";
    char    req[2048];
    char    message[10240];
    char    digest[BUFSIZ];

    sprintf( req,
             "AWSAccessKeyId=%s&"
             "ItemId=%s&"
             "Operation=%s&"
             "ResponseGroup=%s&"
             "Service=%s&"
             "Timestamp=%s&"
             "Version=%s",
             "00000000000000000000",
             "0679722769",
             "ItemLookup",
             "ItemAttributes%2COffers%2CImages%2CReviews",
             "AWSECommerceService",
             "2009-01-01T12%3A00%3A00Z",
             "2009-01-06" );

    sprintf( message,
             "%s\n"
             "%s\n"
             "%s\n"
             "%s",
             "GET",
             "webservices.amazon.com",
             "/onca/xml",
             req );

    memset( digest, 0x00, BUFSIZ );
    hmac_sha256( message, strlen(message), key, strlen(key), digest );
    printdump( digest, BUFSIZ );

    { int c; fputs( ": ", stderr ); c = getchar(); }
    // 35 a7 1e f9 4d c0 cf 83 a1 37 bb 48 4a a8 2c d6
    // f7 4b 04 70 44 8a 35 9c 05 e0 aa 2f 9c 4d f7 18

    p = base64( digest, SHA256_DIGEST_LENGTH );
    if ( p )
        printf( "RESULT: %s\n", p );
    { int c; fputs( ": ", stderr ); c = getchar(); }
    // RESULT: Nace+U3Az4OhN7tISqgs1vdLBHBEijWcBeCqL5xN9xg=

    /*
        // via http://stackoverflow.com/questions/699041/hmacsha256-in-php-and-c-differ
        string password = "Password";
        string filename = "Filename";
        var hmacsha256 = new HMACSHA256(Encoding.UTF8.GetBytes(password));
        hmacsha256.ComputeHash(Encoding.UTF8.GetBytes(filename));
        foreach(byte test in hmacsha256.Hash){
            Console.Write(test.ToString("X2"));
        }
        // 5FE2AE06FF9828B33FE304545289A3F590BFD948CA9AB731C980379992EF41F1
    */
/*
    key = "Password";
    sprintf( message, "Filename" );
    memset( digest, 0x00, BUFSIZ );
    hmac_sha256( message, strlen(message), key, strlen(key), digest );
    printdump( digest, BUFSIZ );

    { int c; fputs( ": ", stderr ); c = getchar(); }
    // 5f e2 ae 06 ff 98 28 b3 3f e3 04 54 52 89 a3 f5
    // 90 bf d9 48 ca 9a b7 31 c9 80 37 99 92 ef 41 f1

    p = base64( digest, SHA256_DIGEST_LENGTH );
    if ( p )
        printf( "RESULT: %s\n", p );
    { int c; fputs( ": ", stderr ); c = getchar(); }
    // X+KuBv+YKLM/4wRUUomj9ZC/2UjKmrcxyYA3mZLvQfE=

    return ( 0 );
}*/
#endif
