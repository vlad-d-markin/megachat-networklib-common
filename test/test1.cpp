#include "../include/hostaddress.h"
#include "../include/tcpsocket.h"

#include <iostream>
#include <string.h>


void testHostAddress() {
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
}


void testTcpSocket() {
    TcpSocket sock1;
    
    sock1.Connect(HostAddress("ya.ru", "80"));
    
    const char * req = "GET / HTTP/1.1\r\n\r\n";
    sock1.Send(req, strlen(req));
    
    char resp[1024];
    int n = sock1.Receive(resp, 1024);
    resp[n] = '\0';
    
    std::cout << resp << std::endl;
    
    sock1.Close();
}

int main() {
    
    std::cout << "Testing HostAddress..." << std::endl;
    testHostAddress();
    
    std::cout << "Testing TcpSocket..." << std::endl;
    testTcpSocket();
    
    return 0;
}