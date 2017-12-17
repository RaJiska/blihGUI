#pragma once

#include "include/BlihGUI.hpp"


/* TODO: Change to struct ? */
class Repository
{
	public:
	Repository(void);

	bool info_queried = false;

	std::string uuid;
	std::string url;
	std::string description;
	std::string is_public;
	long creation;
};