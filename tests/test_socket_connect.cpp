#include <gtest/gtest.h>

#include <tcpsocket.h>

//static const IpAddress addr("93.184.216.34", 80);

TEST(TestSocket, ConnectGoogle) {
    try {
        TcpSocket sock;
        sock.setBlocking(true);

//         google.com
        IpAddress addr("178.45.249.237", 80);

        sock.connect(addr);
        sock.close();
    }
    catch(TcpSocketException &e) {
        FAIL() << e.description();
    }
}


TEST(TestSocket, ConnectWrong) {
    try {
        TcpSocket sock;
        sock.setBlocking(true);

        // google.com
        IpAddress addr("127.0.0.1", 9996);

        sock.connect(addr);
        sock.close();
    }
    catch(TcpSocketException &e) {
        SUCCEED();
    }
}


TEST(TestSocket, RequestGoogle) {
    try {
        TcpSocket sock;
        sock.setBlocking(true);

        // google.com
        IpAddress addr("178.45.249.237", 80);

        sock.connect(addr);

        sock.send("GET / HTTP/1.0\r\n\r\n");

        sock.close();
    }
    catch(TcpSocketException &e) {
        FAIL() << e.description();
    }
}

TEST(TestSocket, GetResponseGoogle) {
    try {
        TcpSocket sock;
        sock.setBlocking(true);

        // google.com
        IpAddress addr("178.45.249.237", 80);

        sock.connect(addr);

        sock.send("GET / HTTP/1.0\r\n\r\n");

        if(sock.receive(20).size() <= 0)
            FAIL() << "No response";

        sock.close();
    }
    catch(TcpSocketException &e) {
        FAIL() << e.description();
    }
}
