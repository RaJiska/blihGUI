#pragma once

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "include/BlihGUI.hpp"
#include "include/Credentials.hpp"

class BlihAPI
{
	public:
	BlihAPI(void);
	~BlihAPI(void);

	bool checkCredentials(void);
	json repositoryCreate(const std::string &name);
	json repositoryDelete(const std::string &name);
	json repositoryList(void);
	json repositoryInfo(const std::string &name);
	json repositorySetAcl(const std::string &name, const std::string &user, const std::string &acls);
	json repositoryGetAcl(const std::string &name);
	void setCredentials(const Credentials &crd);
	Credentials getCredentials(void);

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