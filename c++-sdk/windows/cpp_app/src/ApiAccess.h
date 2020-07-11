#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>


#undef max
#undef min
#include "jwt-cpp/jwt.h"

#define CURL_STATICLIB 
#include "curl/curl.h"

typedef std::map<std::string, std::string> Map;

class ApiAccess
{
public:
	ApiAccess(std::string api_key, std::string api_secret);
	std::string get_api_url(std::string path);
	void set_path(std::string path);
	void set_endpoints(Map input);
	picojson::value::object send(std::string path, Map input, Map payload);
	long long nonce();
	std::string auth();
	picojson::value::object post(Map input, Map payload);

public:
	std::string api_key;
	std::string api_secret;
	int version;
	std::string domain;
	std::string useragent;
	std::string path;
	std::string url;
	picojson::value endpoints;
	int timeout;
	std::map<std::string, std::string> payload;


private:
	static size_t write_result(void* buffer, size_t size, size_t nmemb, void* param);
	std::string build_http_query(Map input);
	picojson::value parse_return_data(std::string str);
	picojson::value::object parse_network_info(CURL* curl);
	template<class T>
	picojson::value get_network_info_numerical(CURL* curl, std::string tag, CURLINFO info_flag);
	template<class T>
	picojson::value get_network_info_text(CURL* curl, std::string tag, CURLINFO info_flag);
};