#pragma once

#include <iostream>
#include <cstdlib>
#include <new>
#include <fstream>
#include <string>

#include <curl/curl.h>

#include "include/json.hpp"

using json = nlohmann::json;

extern const std::string BLIHGUI_WHOAMI;
extern const std::string BLIHAPI_ADDRESS;
extern const long _CURL_GLOBAL_INIT_FLAG;
extern const char *CONFIG_FILE;