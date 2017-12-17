#pragma once

#include <openssl/sha.h>

#include "include/BlihGUI.hpp"

using namespace std;

class Credentials
{
	public:
	Credentials(void);
	Credentials(const std::string &login, const std::string &password);
	~Credentials(void);

	bool readFromConfig(void);
	bool writeToConfig(void);
	std::string getLogin(void);
	char *getPassword(void);
	unsigned char *getPasswordDigest(void);
	void setLogin(const std::string &login);
	void setPassword(const std::string &passwird);

	bool operatorEqual(const Credentials &crd2) const;

	private:
	std::string login;
	unsigned char passwordDigest[SHA512_DIGEST_LENGTH];
	char password[SHA512_DIGEST_LENGTH * 2];
};

bool operator==(const Credentials &crd1, const Credentials &crd2);
bool operator!=(const Credentials &crd1, const Credentials &crd2);