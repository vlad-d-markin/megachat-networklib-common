#include "../include/hostaddress.h"
#include <iostream>

int main() {
    
    HostAddress addr1("google.com");
    
    std::cout << addr1.toString() << std::endl;
    
    HostAddress addr2("ya.ru");
    
    std::cout << addr2.toString() << std::endl;
    
    HostAddress addr3("youtube.com");
    
    std::cout << addr3.toString() << std::endl;
    
    HostAddress addr4("localhost");
    
    std::cout << addr4.toString() << std::endl;
    
    HostAddress addr5("8.8.8.8");
    
    std::cout << addr5.toString() << std::endl;
    
    return 0;
}