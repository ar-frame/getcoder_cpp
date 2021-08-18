#include <iostream>
#include <iostream>
using namespace std;
class ServerResponseException
{
public:
    std::string msg;
    ServerResponseException(std::string str)
    {
        string prefix = "Fetch ServerResponseException: ";
        prefix.append(str);
        msg = prefix + "\n";
    }
};
/*


int main() 
{
    int a = 1;
    if (a > 0) {
        try {
            cout << "a" << endl;
            throw ServerResponseException("a is > 0");
        } catch (ServerResponseException &e) {
            cout << " some thing error " << e.msg;
        }
    }
}
*/
