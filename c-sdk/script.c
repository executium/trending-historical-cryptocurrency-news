#include <stdio.h>
#include <curl/curl.h>
#include <config.h>
#include <class.h>
#include <script.h>
#include <stdlib.h>




int main()
{
    char endpoint[]="public/trending-news-data";
    char input[][MAX_STRING_SIZE]={"date=2020-07-15"};
    payload_struct payload[5]; // Size of 5 Payloads
    _send(endpoint,input,payload);
}

//# Result
//echo '<pre>';
//	print_r($result);
//echo '</pre>';
