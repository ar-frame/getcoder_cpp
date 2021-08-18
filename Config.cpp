#include <iostream>
#include <sstream>
using namespace std;
class Config
{
public:
	string SERVER_ADDRESS;
	string AUTH_SERVER_OPKEY;
	string SERVER_RESPONSE_TAG;
	string USER_AUTH_KEY;

    Config (string SERVER_ADDRESS, string AUTH_SERVER_OPKEY) 
    {
        this->SERVER_ADDRESS = SERVER_ADDRESS;
		this->AUTH_SERVER_OPKEY = AUTH_SERVER_OPKEY;
		SERVER_RESPONSE_TAG = "___SERVICE_STD_OUT_SEP___";

    }


    void setUserAuthKey(string key)
	{
		this->USER_AUTH_KEY = key;
	}

private:

};
