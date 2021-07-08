#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "node.cpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    struct Node node;

    char arry[30] = "\0 Aaron\0 0.0.0.0\0 8001";

    node.addToTable(arry);

    //Seeting information for Node
    //
    unsigned char name[16] = "Aaron";
    char ip[30] = "192.168.2.3";
    int port = 8005;
    int transport = socket(AF_INET, SOCK_DGRAM, 0);

    node.name = name;
    node.setPersonnelAddress(port, ip, transport);

    node.connectTo(0, 5);

}

