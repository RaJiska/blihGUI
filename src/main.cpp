#include <QApplication>

#include "include/BlihGUI.hpp"
#include "include/BlihAPI.hpp"
#include "include/Credentials.hpp"


const std::string BLIHGUI_WHOAMI = "blihGUI";
const std::string BLIHAPI_ADDRESS = "https://blih.epitech.eu/";
const long _CURL_GLOBAL_INIT_FLAG = CURL_GLOBAL_DEFAULT;
const char *CONFIG_FILE = "blihGUI.cfg";

int main(int argc, char **argv)
{
	CURLcode curl_code;
	int ret;

	if ((curl_code = curl_global_init(_CURL_GLOBAL_INIT_FLAG)))
	{
		std::cerr << "Could not init global curl: "
			<< curl_easy_strerror(curl_code)
			<< std::endl;
		return EXIT_FAILURE;
	}
	QApplication app(argc, argv);
	ret = app.exec();
	curl_global_cleanup();
	return ret;
}