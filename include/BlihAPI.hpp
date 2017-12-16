#pragma once

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "include/BlihGUI.hpp"
#include "include/Credentials.hpp"

class BlihAPI
{
	public:
	BlihAPI(Credentials &crd);
	~BlihAPI(void);

	json repositoryCreate(std::string &name);
	json repositoryDelete(std::string &name);
	json repositoryList(void);
	json repositoryInfo(std::string &name);
	json repositorySetAcl(std::string &name, std::string &user, std::string &acls);
	json repositoryGetAcl(std::string &name);

	private:
	bool computeSignature(char *result, const char *key, const char *msg);
	std::string formatData(const json &data);
	json sendRequest(const json &data = nullptr);
	json retrieveResponse(const std::string &raw_response);

	CURL *curl;
	std::string curl_url;
	struct curl_slist *curl_header;
	Credentials crd;
};