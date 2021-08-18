#include <iostream>
#include <sstream>
#include "Fetch.h"
using namespace std;


int main(void)
{
    Config config("http://120.24.7.188:8082", "seraagaldnialaldshgadl12312lasdfaaa");
    config.setUserAuthKey("from cpp client init");

    try {
	    Fetch fetch(config);
        string apiName = "server.ctl.main.Test";
        // 接口名称
        string workerName = "t5";
        // 请求参数
        vector<string> params;
        params.insert(params.begin(), "aa大哥");  
        // 查看原始数据
        //string response = fetch.sendRequest(apiName, workerName, params);
        //Json::Value response = fetch.getString(apiName, workerName, params);
        string response = fetch.getString(apiName, workerName, params);
        cout << " res: " << response << endl;


        vector<string> paramsEmpty;
        // params.insert(params.begin(), "aa");  

        //Json::Value response2 = fetch.getObject("server.ctl.dama.Dama", "getNeedToDamaList", paramsEmpty);
        Json::Value response2 = fetch.getObject("server.ctl.dama.Dama", "getNeedToDamaList", params);
        cout << " res2: " << response2 << endl;


    } catch (ServerResponseException & e) {
	    cout << "catch: " << e.msg;
    }


    return 0;
}
