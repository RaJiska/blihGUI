#include "include/BlihGUI.hpp"

class BlihAPI
{
	public:
	BlihAPI(void);
	~BlihAPI(void);

	private:
	void sendRequest(void);

	CURL *curl;
};