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


    //Seeting information for Node
    //
    unsigned char name[16] = "Aaron";
    char ip[30] = "0.0.0.0";
    int port = 8001;
    int transport = socket(AF_INET, SOCK_DGRAM, 0);

    node.setPersonnelAddress(name, port, ip, transport);

    node.listen();

}
