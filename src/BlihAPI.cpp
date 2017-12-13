#include "include/BlihAPI.hpp"

BlihAPI::BlihAPI(void)
{
	this->curl = curl_easy_init();
	if (!this->curl)
		throw std::bad_alloc();
}

BlihAPI::~BlihAPI(void)
{
	curl_easy_cleanup(this->curl);
}

