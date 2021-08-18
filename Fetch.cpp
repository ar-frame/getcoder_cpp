#include <iostream>
#include <sstream>
#include <stdio.h>
#include <curl/curl.h>
#include<vector>
#include <jsoncpp/json/json.h>

using namespace std;
static char errorBuffer[CURL_ERROR_SIZE];
static string retstring;
class Fetch 
{
public:
    static int writer(char *data, size_t size, size_t nmemb,
                    std::string *writerData)
    {
        if(writerData == NULL)
            return 0;
        writerData->append(data, size*nmemb);
        return size * nmemb;
    }

    Config config = Config(" ", " ");

    Fetch (Config & config) 
    {
        this->config = config;
    }

    string getResponse(string ws) 
    {
        *&retstring = "";
        char errString[200];
        //string retstring;

        CURL *curl;
        CURLcode code;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);

            curl_easy_setopt(curl, CURLOPT_URL, config.SERVER_ADDRESS.c_str());
            string wsString = "ws=";
            string postString = wsString.append(ws);

            code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
            if(code != CURLE_OK) {
                sprintf(errString, "Failed to set error buffer [%d]\n", code);
                throw ServerResponseException(errString);
            }

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
            code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &retstring);


            if(code != CURLE_OK) {
                sprintf(errString, "Failed to set write data [%s]\n", errorBuffer);
                throw ServerResponseException(errString);
            }
            code = curl_easy_perform(curl);

            if(code != CURLE_OK) {
                sprintf(errString, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(code));
		//cout << "err:" << errString;
                throw ServerResponseException(errString);
            }
            /* always cleanup */ 
            curl_easy_cleanup(curl);
            //stringstream ss;
            //ss<<res;
            //ss>>retstring;
        }
        curl_global_cleanup();

        if (retstring.length() == 0) {
            throw ServerResponseException("error get nothing ");
        }

        if (retstring.find(config.SERVER_RESPONSE_TAG) == string::npos) {
            throw ServerResponseException("bad response :" + retstring);
        } else {
            retstring = Cipher::hexStr2Str(retstring.substr(retstring.find(config.SERVER_RESPONSE_TAG) + config.SERVER_RESPONSE_TAG.length()));
        }
        string response = retstring;
        return response;
    }

    string sendRequest(string api, string workerName, vector<string> params)
    {
        Json::Value dataMap;
        dataMap["type"] = "array";

        Json::Value authSign;
        authSign["AUTH_SERVER_OPKEY"] = config.AUTH_SERVER_OPKEY;
        authSign["USER_AUTH_KEY"] = config.USER_AUTH_KEY;

        Json::Value map;
        map["class"] = api;
        map["method"] = workerName;

        if (params.size() > 0) {
            Json::Value p;
            for (int i = 0; i < params.size(); i++) {
                p.append(params[i]);
            } 
            map["param"] = p;
        } else {
            map["param"] = "[\"\"]";
        }
        map["authSign"] = authSign;
        map["CLIENT_SERVER"] = "GETCODER-CPP-SDK-20191107";

        dataMap["data"] = map;
        string sendJsonString = dataMap.toStyledString();

        string ws = Cipher::str2HexStr(sendJsonString);

		return getResponse(ws);
	}


    Json::Value getObject(string api, string workerName, vector<string> params) 
    {
		string response = sendRequest(api, workerName, params);

        Json::Reader reader;
        Json::Value jObject;
    
        if (reader.parse(response, jObject))
        {
            if (jObject["type"].asString() == "object") {
                return jObject["data"];
            } else {
                throw ServerResponseException("type check error, 'object' expected but "
						+ jObject["type"].asString() + " provided," + response);
            }
        } else {
            throw ServerResponseException("type check error, 'object' expected, response: " + response);
        }
	}

    Json::Value getJson(string api, string workerName, vector<string> params) 
    {
		string response = sendRequest(api, workerName, params);

        Json::Reader reader;
        Json::Value jObject;
    
        if (reader.parse(response, jObject))
        {
            if (jObject["type"].asString() == "array") {
                return jObject["data"];
            } else {
                throw ServerResponseException("type check error, 'array' expected but "
						+ jObject["type"].asString() + " provided," + response);
            }
        } else {
            throw ServerResponseException("type check error, 'array' expected, response: " + response);
        }
	}

    Json::Value getArray(string api, string workerName, vector<string> params) 
    {
		return getJson(api, workerName, params);
	}

    string getString(string api, string workerName, vector<string> params) 
    {
		string response = sendRequest(api, workerName, params);

        Json::Reader reader;
        Json::Value jObject;
    
        if (reader.parse(response, jObject))
        {
            if (jObject["type"].asString() == "string") {
                return jObject["data"].asString();
            } else {
                throw ServerResponseException("type check error, 'string' expected but "
						+ jObject["type"].asString() + " provided," + response);
            }
        } else {
            throw ServerResponseException("type check error, 'string' expected, response: " + response);
        }
	}

    int getInt(string api, string workerName, vector<string> params) 
    {
		string response = sendRequest(api, workerName, params);

        Json::Reader reader;
        Json::Value jObject;
    
        if (reader.parse(response, jObject))
        {
            if (jObject["type"].asString() == "int") {
                return jObject["data"].asInt();
            } else {
                throw ServerResponseException("type check error, 'int' expected but "
						+ jObject["type"].asString() + " provided," + response);
            }
        } else {
            throw ServerResponseException("type check error, 'int' expected, response: " + response);
        }
	}

    int getBool(string api, string workerName, vector<string> params) 
    {
		string response = sendRequest(api, workerName, params);

        Json::Reader reader;
        Json::Value jObject;
    
        if (reader.parse(response, jObject))
        {
            if (jObject["type"].asString() == "bool") {
                return jObject["data"].asBool();
            } else {
                throw ServerResponseException("type check error, 'bool' expected but "
						+ jObject["type"].asString() + " provided," + response);
            }
        } else {
            throw ServerResponseException("type check error, 'bool' expected, response: " + response);
        }
	}

    double getFloat(string api, string workerName, vector<string> params) 
    {
		string response = sendRequest(api, workerName, params);

        Json::Reader reader;
        Json::Value jObject;
    
        if (reader.parse(response, jObject))
        {
            if (jObject["type"].asString() == "float") {
                return jObject["data"].asDouble();
            } else {
                throw ServerResponseException("type check error, 'float' expected but "
						+ jObject["type"].asString() + " provided," + response);
            }
        } else {
            throw ServerResponseException("type check error, 'float' expected, response: " + response);
        }
	}

    double getDouble(string api, string workerName, vector<string> params) 
    {
		return getFloat(api, workerName, params);
	}

};
 

