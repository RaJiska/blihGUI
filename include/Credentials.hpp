#include <openssl/sha.h>

#include "include/BlihAPI.hpp"

using namespace std;

class Credentials
{
	public:
	Credentials(void);
	Credentials(std::string login, std::string password);
	~Credentials(void);

	bool readFromConfig(void);
	bool writeToConfig(void);

	private:
	std::string login;
	unsigned char password[SHA512_DIGEST_LENGTH];
};