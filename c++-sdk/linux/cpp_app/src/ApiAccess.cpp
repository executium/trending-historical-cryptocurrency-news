#include "ApiAccess.h"

ApiAccess::ApiAccess(std::string api_key, std::string api_secret) :
	api_key(api_key),
	api_secret(api_secret),
	version(2),
	domain("https://trendingnews.executium.com"),
	useragent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36"),
	timeout(80000)
{
}

std::string ApiAccess::get_api_url(std::string path)
{
	std::string url = domain;
	url += "/api/v";
	url += std::to_string(version);
	url += "/";
	url += path;
	return url;
}

void ApiAccess::set_path(std::string path)
{
	this->path = path;
}

void ApiAccess::set_endpoints(Map input)
{
	set_path("system/ep");
	Map payload;
	picojson::value::object  returned = post(input, payload);
	bool success = returned["success"].get<bool>();
	if (success)
	{
		picojson::value::object& obj = returned["returned"].get<picojson::object>();
		endpoints = obj["data"];
	}
}

picojson::value::object ApiAccess::send(std::string path, Map input, Map payload)
{
	this->set_path(path);
	return post(input, payload);
}

long long ApiAccess::nonce()
{
	std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	long long nonce = ms.count() * 10;
	return nonce;
}

std::string ApiAccess::auth()
{
	payload["nonce"] = std::to_string(nonce());
	
	jwt::builder builder = jwt::create()
		.set_type("JWT")
		.set_algorithm("HS256");

	std::map<std::string, std::string>::iterator it = payload.begin();
	for (; it !=payload.end(); ++it)
	{
		builder.set_payload_claim(it->first, jwt::claim(it->second));
	}

	std::string token = builder.sign(jwt::algorithm::hs256{api_secret});

	return token;
}

picojson::value ApiAccess::parse_return_data(std::string str)
{
	picojson::value v;
	std::string err = picojson::parse(v, str);
	if (!err.empty())
	{
		std::cout << err << std::endl;
	}
	return v;
}

picojson::value::object ApiAccess::parse_network_info(CURL * curl)
{
	std::map<std::string, CURLINFO> flags;

	std::vector<std::string> string_info;
	// string
	flags["url"] = CURLINFO_EFFECTIVE_URL;
	string_info.push_back("url");
	flags["content_type"] = CURLINFO_CONTENT_TYPE;
	string_info.push_back("content_type");
	flags["primary_ip"] = CURLINFO_PRIMARY_IP;
	string_info.push_back("primary_ip");
	flags["local_ip"] = CURLINFO_LOCAL_IP;
	string_info.push_back("local_ip");
	flags["redirect_url"] = CURLINFO_REDIRECT_URL;
	string_info.push_back("redirect_url");
	
	std::vector<std::string> long_info;
	// long
	flags["http_code"] = CURLINFO_RESPONSE_CODE;
	long_info.push_back("http_code");
	flags["header_size"] = CURLINFO_HEADER_SIZE;
	long_info.push_back("header_size");
	flags["request_size"] = CURLINFO_REQUEST_SIZE;
	long_info.push_back("request_size");
	flags["filetime"] = CURLINFO_FILETIME;
	long_info.push_back("filetime");
	flags["ssl_verify_result"] = CURLINFO_SSL_VERIFYRESULT;
	long_info.push_back("ssl_verify_result");
	flags["redirect_count"] = CURLINFO_REDIRECT_COUNT;
	long_info.push_back("redirect_count");
	flags["primary_port"] = CURLINFO_PRIMARY_PORT;
	long_info.push_back("primary_port");
	flags["local_port"] = CURLINFO_LOCAL_PORT;
	long_info.push_back("local_port");
	
	std::vector<std::string> double_info;
	// double
	flags["total_time"] = CURLINFO_TOTAL_TIME;
	double_info.push_back("total_time");
	flags["namelookup_time"] = CURLINFO_NAMELOOKUP_TIME;
	double_info.push_back("namelookup_time");
	flags["connect_time"] = CURLINFO_CONNECT_TIME;
	double_info.push_back("connect_time");
	flags["pretransfer_time"] = CURLINFO_PRETRANSFER_TIME;
	double_info.push_back("pretransfer_time");
	flags["size_upload"] = CURLINFO_SIZE_UPLOAD;
	double_info.push_back("size_upload");
	flags["size_download"] = CURLINFO_SIZE_DOWNLOAD;
	double_info.push_back("size_download");
	flags["speed_download"] = CURLINFO_SPEED_DOWNLOAD;
	double_info.push_back("speed_download");
	flags["speed_upload"] = CURLINFO_SPEED_UPLOAD;
	double_info.push_back("speed_upload");
	flags["download_content_length"] = CURLINFO_CONTENT_LENGTH_DOWNLOAD;
	double_info.push_back("download_content_length");
	flags["upload_content_length"] = CURLINFO_CONTENT_LENGTH_UPLOAD;
	double_info.push_back("upload_content_length");
	flags["starttransfer_time"] = CURLINFO_STARTTRANSFER_TIME;
	double_info.push_back("starttransfer_time");
	flags["redirect_time"] = CURLINFO_REDIRECT_TIME;
	double_info.push_back("redirect_time");
	
	std::vector<std::string> char_ptr_info;
	// char*
	flags["certinfo"] = CURLINFO_CERTINFO;
	char_ptr_info.push_back("certinfo");
	
	

	picojson::value::object network_info;
	std::map<std::string, CURLINFO>::iterator it = flags.begin();
	for (; it != flags.end(); ++it)
	{
		picojson::value value;
		std::string tag = it->first;
		if (std::find(string_info.begin(), string_info.end(), tag) != string_info.end())
		{
			value = get_network_info_text<char*>(curl, tag, it->second);
		}
		else if (std::find(long_info.begin(), long_info.end(), tag) != long_info.end())
		{
			value = get_network_info_numerical<long>(curl, tag, it->second);
		}
		else if (std::find(double_info.begin(), double_info.end(), tag) != double_info.end())
		{
			value = get_network_info_numerical<double>(curl, tag, it->second);
		}
		else if (std::find(char_ptr_info.begin(), char_ptr_info.end(), tag) != char_ptr_info.end())
		{
			value = get_network_info_text<char*>(curl, tag, it->second);
		}
		network_info[tag] = value;
	}
	
	return network_info;
}

template<class T>
picojson::value ApiAccess::get_network_info_numerical(CURL* curl, std::string tag, CURLINFO info_flag)
{
	T info;
	CURLcode res;
	picojson::value jsonval = picojson::value();
	res = curl_easy_getinfo(curl, info_flag, &info);
	if (CURLE_OK == res)
	{
		std::string val = std::to_string(info);
		jsonval = picojson::value(val);
	}
	return jsonval;
}

template<class T>
picojson::value ApiAccess::get_network_info_text(CURL* curl, std::string tag, CURLINFO info_flag)
{
	T info;
	CURLcode res;
	picojson::value jsonval = picojson::value();
	res = curl_easy_getinfo(curl, info_flag, &info);
	if (CURLE_OK == res&&info)
	{
		std::string val = std::string(info);
		jsonval = picojson::value(val);
	}
	return jsonval;
}


picojson::value::object ApiAccess::post(Map input, Map payload)
{
	picojson::value::object result;
	result["success"] = picojson::value(false);

	CURL* curl;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (!curl) 
	{
		return result;
	}
	
	this->payload = payload;
	
	std::string curl_result;

	std::string url = get_api_url(path);
	std::cout << "Try : " << url << std::endl;
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HEADER, false);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, true);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_result);
	// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	struct curl_slist* headers = NULL;
	std::string key_header = "key:" + api_key;
	std::string auth_header = "Authorization:" + auth();
	headers = curl_slist_append(headers, key_header.c_str());
	headers = curl_slist_append(headers, auth_header.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


	if (input.size() > 0)
	{
		curl_easy_setopt(curl, CURLOPT_POST, input.size());
		std::string query = build_http_query(input);
		std::cout << "query :- " << query << std::endl;
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
	}
	
	CURLcode res;
	res = curl_easy_perform(curl);

	
	result["returned"] = picojson::value(picojson::object());
	result["network_info"] = picojson::value(picojson::object());

	if (CURLE_OK != res) {
		std::cout << "CURL error: " << res << '\n';
		return result;
	}
	picojson::value info_net = picojson::value(parse_network_info(curl));

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	result["success"] = picojson::value(true);
	result["network_info"] = info_net;
	result["returned"] = parse_return_data(curl_result);
	
	return result;
}

size_t ApiAccess::write_result(void * buffer, size_t size, size_t nmemb, void * param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

std::string ApiAccess::build_http_query(Map input)
{
	std::string query;
	Map::iterator it = input.begin();
	for (; it != input.end(); ++it)
	{
		if (!query.empty())
		{
			query += "&";
		}
		query += it->first;
		query += "=";
		query += it->second;
	}
	return query;
}
