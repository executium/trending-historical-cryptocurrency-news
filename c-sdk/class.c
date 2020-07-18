#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <sys/time.h>
#include <locale.h>
#include <stdlib.h>
#include <class.h>
#include <script.h>
#include <config.h>
#include <base64.h>
#include <json-c/json.h>
#include <hmac.h>
#include <errno.h>


char version[] ="2";
char domain[]="https://trendingnews.executium.com";
char useragent[]="API v2 (C-SDK)";
char *path;
char url[100];
char endpoints[]="";
char timeout[]="3000";
payload_struct *_payload;
char *_api_key;
char *_api_secret;
char ret[250];
char hmac[250];
char str1[250],str2[250];
char _nonce[256];
char sig[BUFSIZ]; //Buffer Size
char input1[][MAX_STRING_SIZE]={"request=1"};
struct curl_slist *list = NULL;
struct MemoryStruct {
  char *memory;
  size_t size;
};


// fork from https://github.com/irl/la-cucina/blob/master/str_replace.c
char* str_replace(char* string, const char* substr, const char* replacement) {
	char* tok = NULL;
	char* newstr = NULL;
	char* oldstr = NULL;
	int   oldstr_len = 0;
	int   substr_len = 0;
	int   replacement_len = 0;


	newstr = strdup(string);
	substr_len = strlen(substr);
	replacement_len = strlen(replacement);

	if (substr == NULL || replacement == NULL) {
		return newstr;
	}

	while ((tok = strstr(newstr, substr))) {
		oldstr = newstr;
		oldstr_len = strlen(oldstr);
		newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));

		if (newstr == NULL) {
			free(oldstr);
			return NULL;
		}

		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replacement, replacement_len);
		memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
		memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);

		free(oldstr);
	}

	free(string);

	return newstr;
}

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}



char * nonce()
{
  struct timeval time;
  gettimeofday(&time, NULL); // returns a struct that has microsecond precision.
  long microsec = ((unsigned long long)time.tv_sec * 10000000) + time.tv_usec;


  sprintf(_nonce, "%ld", microsec);


  return _nonce;


}

char* auth()
{

    size_t output_length;
    char *str;
    char *b01,*b02,*b03;


    _payload[0].key="nonce";
    _payload[0].value=nonce();


      str=base64_encode("{\"typ\":\"JWT\",\"alg\":\"HS256\"}",strlen("{\"typ\":\"JWT\",\"alg\":\"HS256\"}"),&output_length);
      //printf("String is %s \n" , str);
      b01=str_replace(str,"+", "-");
      b01=str_replace(b01,"/", "_");
      b01=str_replace(b01,"=", "");

      //Manipulate the JSON
      /*Creating a json object*/
      json_object * jobj = json_object_new_object();
      for (int i=0;i<=(sizeof(_payload)/sizeof(_payload[0]));i++)
      {
        /*Creating a json string*/
        json_object *jstring = json_object_new_string(_payload[i].value);
        json_object_object_add(jobj,_payload[i].key, jstring);
      }

			str=str_replace(json_object_to_json_string(jobj)," ","");


      str=base64_encode(str,strlen(str),&output_length);
      b02=str_replace(str,"+", "-");
      b02=str_replace(b02,"/", "_");
      b02=str_replace(b02,"=", "");

		//	Adjust String
			int size = strlen(b02);
			b02[size-1] = '\0';

      strcat(hmac,b01);
      strcat(hmac,".");
      strcat(hmac,b02);


      memset( sig, 0x00, BUFSIZ );

      hmac_sha256(hmac,strlen(hmac),_api_secret,strlen(_api_secret), sig);

      str=base64_encode(sig,strlen(sig),&output_length);

      b03=str_replace(str,"+", "-");
      b03=str_replace(b03,"/", "_");
      b03=str_replace(b03,"=", "");

			strcat(ret,b01);
      strcat(ret,".");
      strcat(ret,b02);
      strcat(ret,".");
      strcat(ret,b03);

      return ret;


}

int api_access(char api_key[], char api_secret[])
{
    _api_key=api_key;
    _api_secret=api_secret;

}

int _post(char input[][MAX_STRING_SIZE],payload_struct *payload)
{
  CURL *curl;
  CURLcode res;
	enum json_tokener_error jerr = json_tokener_success;
	json_object *json;

	struct MemoryStruct chunk;

  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */

  curl = curl_easy_init();

  if(curl) {

    _payload=payload;



    strcat(url,domain);

    strcat(url,"/api/v");
    strcat(url,version);
    strcat(url,"/");
    strcat(url,path);


   curl_easy_setopt(curl, CURLOPT_URL, url);
   curl_easy_setopt(curl, CURLOPT_HEADER, 0);
   curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
   curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
   curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent);
	 /* send all data to this function  */
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
   strcat(str1,"Key: ");
   strcat(str1,_api_key);
	 list = curl_slist_append(list, str1);
   strcat(str2,"Authorization: ");
	 strcat(str2,auth());
	 list = curl_slist_append(list, str2);

   curl_easy_setopt(curl, CURLOPT_HTTPHEADER,list);



   if (sizeof(input1)/sizeof(input1[0])>0)
	 {
		 curl_easy_setopt(curl, CURLOPT_POST,sizeof(input1)/sizeof(input1[0][0]));
		 curl_easy_setopt(curl, CURLOPT_POSTFIELDS,input1[0]);
	 }


    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);


    /* Check for errors */
   if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	 else
	 {


    //  printf("%s \n", chunk.memory);
			json = json_tokener_parse_verbose( chunk.memory, &jerr);

			char *ct;
		 /* ask for the content-type */
		 res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
	//	 if((CURLE_OK == res) && ct)
  //      printf("We received Content-Type: %s\n", ct);
			printf("%s\n", json_object_to_json_string(json));
  //  	json_tokener_parse(json);


	 }




    /* always cleanup */
		free(chunk.memory);
    curl_easy_cleanup(curl);
  }
  else
  {
     char *error[2][2]={
         { "code","error"} ,
       {"100","CURL Problem"}
      };

  }




}

int _send(char endpoint[],char input[][MAX_STRING_SIZE],payload_struct *payload)
{

  path=endpoint;
  api_access(API_KEY,API_SECRET);


  return _post(input, payload);

}
