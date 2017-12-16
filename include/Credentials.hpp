#pragma once

#include <openssl/sha.h>

#include "include/BlihGUI.hpp"

using namespace std;

class Credentials
{
	public:
	Credentials(void);
	Credentials(std::string login, std::string password);
	~Credentials(void);

	bool readFromConfig(void);
	bool writeToConfig(void);
	std::string getLogin(void);
	char *getPassword(void);
	unsigned char *getPasswordDigest(void);

	private:
	std::string login;
	unsigned char passwordDigest[SHA512_DIGEST_LENGTH];
	char password[SHA512_DIGEST_LENGTH * 2];
};