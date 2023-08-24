#include <iostream>
#include "CryptTest.h"

int main()
{
    //CryptTest01();
    //CryptTest01();

    //GenerateRandomNumber(1, 3);
    std::string ret = GenerateRandomStr(1, 3);
    std::cout << ret << std::endl;
    

    return 0;
}
