#include "include/BlihAPI.hpp"

BlihAPI::BlihAPI()
{
	this->curl_header = NULL;
	this->curl = curl_easy_init();
	if ((!this->curl) ||
		(!(this->curl_header = curl_slist_append(
			this->curl_header, "Content-Type: application/json")
		)) ||
		(!(this->curl_header = curl_slist_append(
			this->curl_header, 
			("User-Agent: " + BLIHGUI_WHOAMI).c_str()))
		))
		throw std::bad_alloc();
}

BlihAPI::~BlihAPI(void)
{
	curl_slist_free_all(this->curl_header);
	curl_easy_cleanup(this->curl);
}

/* --------------- PUBLIC --------------- */

bool BlihAPI::checkCredentials(void)
{
	json response;

	this->curl_url = (BLIHAPI_ADDRESS + "repositories");
	curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "GET");
	if ((response = this->sendRequest()) == nullptr)
		return false;
	return (response["_STATUS_CODE"] == "200");
}

json BlihAPI::repositoryCreate(const std::string &name)
{
	json data;

	this->curl_url = (BLIHAPI_ADDRESS + "repositories");
	curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "POST");
	data["name"] = name;
	data["type"] = "git";
	return this->sendRequest(data);
}

json BlihAPI::repositoryList(void)
{
	this->curl_url = (BLIHAPI_ADDRESS + "repositories");
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	return this->sendRequest();
}

json BlihAPI::repositoryDelete(const std::string &name)
{
	this->curl_url = (BLIHAPI_ADDRESS + "repository/" + name);
	curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	return this->sendRequest();
}

json BlihAPI::repositoryInfo(const std::string &name)
{
	this->curl_url = (BLIHAPI_ADDRESS + "repository/" + name);
	curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "GET");
	return this->sendRequest();
}

json BlihAPI::repositorySetAcl(
	const std::string &name,
	const std::string &user,
	const std::string &acls)
{
	json data;

	this->curl_url = (BLIHAPI_ADDRESS + "repository/" + name + "/acls");
	curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "POST");
	data["user"] = user;
	data["acl"] = acls;
	return this->sendRequest(data);
}

json BlihAPI::repositoryGetAcl(const std::string &name)
{
	this->curl_url = (BLIHAPI_ADDRESS + "repository/" + name + "/acls");
	curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "GET");
	return this->sendRequest();
}

void BlihAPI::setCredentials(const Credentials &crd)
{
	this->crd = crd;
}

/* --------------- PRIVATE --------------- */

bool BlihAPI::computeSignature(char *sig, const char *key, const char *msg)
{
	unsigned char *digest;
	unsigned int it;

	digest = HMAC(EVP_sha512(), key, SHA512_DIGEST_LENGTH * 2, (unsigned char *) msg, strlen(msg), NULL, NULL);
	if (!digest)
		return false;
	for (it = 0; it < SHA512_DIGEST_LENGTH; it++)
		sprintf(&sig[it * 2], "%02x", (unsigned int) digest[it]);
	return true;
}

std::string BlihAPI::formatData(const json &data)
{
	json full_data;
	std::string str_data;
	char signature[SHA512_DIGEST_LENGTH * 2 + 1];

	signature[SHA512_DIGEST_LENGTH * 2] = 0;
	str_data = this->crd.getLogin();
	if (data != nullptr)
	 {
		str_data += data.dump(4, ' ');
		full_data["data"] = data;
	 }
	full_data["user"] = this->crd.getLogin();
	this->computeSignature(&signature[0], crd.getPassword(), str_data.c_str());
	full_data["signature"] = std::string(&signature[0]);
	str_data = full_data.dump(4, ' ');
	return str_data;
}

static size_t requestCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}

json BlihAPI::sendRequest(const json &data)
{
	std::string raw_response;
	json response;
	std::string str_data;
	CURLcode code;

	str_data = this->formatData(data);
	curl_easy_setopt(this->curl, CURLOPT_URL, this->curl_url.c_str());
	curl_easy_setopt(this->curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->curl_header);
	curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, str_data.c_str());
	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, requestCallback);
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &raw_response);
	code = curl_easy_perform(this->curl);
	response = (code != CURLE_OK) ? json(json::value_t::null) : this->retrieveResponse(raw_response);
	curl_easy_reset(this->curl);
	return response;
}

json BlihAPI::retrieveResponse(const std::string &raw_response)
{
	json response;
	json jraw_response;
	long status_code;

	curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &status_code);
	response["_STATUS_CODE"] = std::to_string(status_code);
	jraw_response = json::parse(raw_response);
	for (auto &it : json::iterator_wrapper(jraw_response))
		response[it.key()] = it.value();
	return response;
}
