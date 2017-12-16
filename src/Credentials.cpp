#include "include/Credentials.hpp"

Credentials::Credentials(void)
{

}

Credentials::Credentials(std::string login, std::string password)
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
		ofs.write(this->login.c_str(), this->login.length() + 1);
		ofs.write((char *) this->password, SHA512_DIGEST_LENGTH);
		ofs.close();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

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