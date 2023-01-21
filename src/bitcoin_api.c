#include "bitcoin_api.h"


/* Init of the custom struct */
void init_string(struct custom_string* str) 
{
	str->len = 0;
	str->ptr = malloc((str->len + 1) * sizeof(char));

	if (str->ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	str->ptr[0] = '\0';
}

/* Free of the custom struct */
void free_string(struct custom_string* str)
{
	str->len = 0;
	free(str->ptr);
}

/* Casting of the CURLcode into string */
size_t writefunc(void* ptr, size_t size, size_t nmemb, struct custom_string* str)
{
	size_t new_len = str->len + size * nmemb;
	str->ptr = realloc(str->ptr, new_len + 1);

	if (str->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}

	memcpy(str->ptr + str->len, ptr, size * nmemb);
	str->ptr[new_len] = '\0';
	str->len = new_len;

	return size * nmemb;
}

/* Function to get the bitcoin price returned in a string */
void get_bitcoin_price(char* btc_price, int buffersize)
{
	CURL* curl;
	CURLcode res;

	struct custom_string str;
	init_string(&str);
	
	curl = curl_easy_init();
	if(curl) {

		/*Getting date from the blochain info website*/
		curl_easy_setopt(curl, CURLOPT_URL, "https://blockchain.info/ticker");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
		res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}

	/*Parsing of the json object returned by the website*/
	struct json_object* parsed_json;
	struct json_object* USD_json;
	struct json_object* bitcoin_price;
	parsed_json = json_tokener_parse(str.ptr);
	json_object_object_get_ex(parsed_json, "USD", &USD_json);
	json_object_object_get_ex(USD_json, "15m", &bitcoin_price);

	/*Copy the price of bitcoin into the string send to this function*/
	strncpy(btc_price, json_object_get_string(bitcoin_price), buffersize - 1);
	btc_price[buffersize - 1] = '\0';

	/*Cleaning up*/
	free_string(&str);
}