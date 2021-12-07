#ifndef DEF_BITCOINAPI
#define DEF_BITCOINAPI

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <json-c/json.h>

/*Custom struct for casting CURLcode into string*/
struct custom_string {
  char *ptr;
  size_t len;
};

void init_string(struct custom_string *s) ; //Function to init the string
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct custom_string *s); //Function to convert our CURLcode into string
void get_bitcoin_price(char* btc_price, int buffersize); //Function to put the current bitcoinprice into a string

#endif