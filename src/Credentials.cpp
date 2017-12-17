#include "include/Credentials.hpp"

Credentials::Credentials(void)
{

}

Credentials::Credentials(const std::string &login, const std::string &password)
{
	unsigned int it;

	this->login = login;
	SHA512((unsigned char *) password.c_str(), password.length(), this->passwordDigest);
	for (it = 0; it < SHA512_DIGEST_LENGTH; it++)
		sprintf(&this->password[it * 2], "%02x", (unsigned int) this->passwordDigest[it]);
}

Credentials::~Credentials(void)
{

}

/* --------------- PUBLIC --------------- */

/* TODO: Handle when file exists but not readable */
bool Credentials::readFromConfig(void)
{
	std::ifstream ifs;
	unsigned int it;

	try
	{
		ifs.open(CONFIG_FILE, ios::in | ios::binary);
		std::getline(ifs, this->login, (char) 0);
		ifs.read((char *) this->passwordDigest, SHA512_DIGEST_LENGTH);
		ifs.close();
	}
	catch (...)
	{
		return false;
	}
	for (it = 0; it < SHA512_DIGEST_LENGTH; it++)
		sprintf(&this->password[it * 2], "%02x", (unsigned int) this->passwordDigest[it]);
	return true;
}

bool Credentials::writeToConfig(void)
{
	std::ofstream ofs;

	try
	{
		ofs.open(CONFIG_FILE, ios::out | ios::binary);
		ofs.write(this->login.c_str(), this->login.length());
		ofs.put((char) 0);
		ofs.write((char *) this->passwordDigest, SHA512_DIGEST_LENGTH);
		ofs.close();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void Credentials::setLogin(const std::string &login)
{
	this->login = login;
}

void Credentials::setPassword(const std::string &password)
{
	unsigned int it;

	SHA512((unsigned char *) password.c_str(), password.length(), this->passwordDigest);
	for (it = 0; it < SHA512_DIGEST_LENGTH; it++)
		sprintf(&this->password[it * 2], "%02x", (unsigned int) this->passwordDigest[it]);
}

/* --------------- OPERATORS --------------- */

bool Credentials::operatorEqual(const Credentials &crd2) const
{
	unsigned int it;

	if (this->login != crd2.login)
		return false;
	for (it = 0; it < SHA512_DIGEST_LENGTH; it++)
	{
		if (this->passwordDigest[it] != crd2.passwordDigest[it])
			return false;
	}
	return true;
}

/* --------------- PRIVATE --------------- */

std::string Credentials::getLogin(void)
{
	return this->login;
}

char *Credentials::getPassword(void)
{
	return this->password;
}

unsigned char *Credentials::getPasswordDigest(void)
{
	return this->passwordDigest;
}

bool operator==(const Credentials &crd1, const Credentials &crd2)
{
	return crd1.operatorEqual(crd2);
}

bool operator!=(const Credentials &crd1, const Credentials &crd2)
{
	return !crd1.operatorEqual(crd2);
}