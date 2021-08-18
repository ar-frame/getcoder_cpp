#include <iostream>
#include <sstream>
using namespace std;
class Cipher
{
public:

    static std::string str2HexStr(std::string str)
    {
        const std::string hex = "0123456789ABCDEF";
        std::stringstream ss;
    
        for (std::string::size_type i = 0; i < str.size(); ++i)
            ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf];
        
        return ss.str();
    }

    static std::string hexStr2Str(std::string str)
    {
        std::string result;
        for (size_t i = 0; i < str.length(); i += 2)
        {
            std::string byte = str.substr(i, 2);
            char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
            result.push_back(chr);
        }
        return result;
    }


private:

};


// int main()
// {
//     cout << Cipher::str2HexStr("{\"data\":{\"method\":\"t4\",\"param\":[\"helloaa\"],") << endl;
//     cout << Cipher::hexStr2Str("7B2264617461223A7B226D6574686F64223A227434222C22706172616D223A5B2268656C6C6F6161225D2C");
//     return 0;
// }