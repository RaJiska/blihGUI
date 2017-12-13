#include <QApplication>

#include "include/BlihGUI.hpp"

#ifndef _WIN32
const long _CURL_GLOBAL_INIT_FLAG = CURL_GLOBAL_NOTHING;
const char *CONFIG_FILE = "blihGUI.cfg";
# else
const long _CURL_GLOBAL_INIT_FLAG = CURL_GLOBAL_WIN32;
const char *CONFIG_FILE = "blihGUI.cfg";
#endif


int main(int argc, char **argv)
{
	CURLcode curl_code;

	if ((curl_code = curl_global_init(_CURL_GLOBAL_INIT_FLAG)))
	{
		std::cerr << "Could not init global curl: "
			<< curl_easy_strerror(curl_code)
			<< std::endl;
		return EXIT_FAILURE;
	}
	QApplication app(argc, argv);
	curl_global_cleanup();
    return app.exec();
}