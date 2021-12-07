#include "bitcoinapi.h"


/*Init of the custom struct*/
void init_string(struct custom_string *s) 
{
  s->len = 0;
  s->ptr = malloc(s->len+1);

  if (s->ptr == NULL) 
  {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }

  s->ptr[0] = '\0';
}

/*Casting of the CURLcode into string*/
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct custom_string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);

  if (s->ptr == NULL) 
  {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }

  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

/*Function to get the bitcoin price returned in a string*/
void get_bitcoin_price(char* btc_price, int buffersize)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) 
  {
    struct custom_string s;
    init_string(&s);

    /*Getting date from the blochain info website*/
    curl_easy_setopt(curl, CURLOPT_URL, "https://blockchain.info/ticker");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    curl_easy_perform(curl);

    /*Parsing of the json object returned by the website*/
    struct json_object *parsed_json;
    struct json_object *USD_json;
    struct json_object *bitcoin_price;
    parsed_json = json_tokener_parse(s.ptr);
    json_object_object_get_ex(parsed_json, "USD",&USD_json);
    json_object_object_get_ex(USD_json, "15m",&bitcoin_price);

    /*Copy the price of bitcoin into the string send to this function*/
    strncpy(btc_price, json_object_get_string(bitcoin_price), buffersize-1);
    btc_price[buffersize-1] = '\0';


    /*Cleaning up*/
    free(s.ptr);
    curl_easy_cleanup(curl);
  }
}