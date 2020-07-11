#include <iostream>
#include <string>

#include "ApiAccess.h"



void test_api_access()
{
	std::string key = "";
	std::string secret = "";

	std::string end_point = "public/trending-news-data";

	ApiAccess access(key, secret);

	Map input;
	input["date"] = "2020-07-05";

	Map payload;

	picojson::object response = access.send(end_point, input, payload);

	std::cout << picojson::value(response).serialize() << std::endl;
}

int main()
{
	test_api_access();
	// void test_json();
}