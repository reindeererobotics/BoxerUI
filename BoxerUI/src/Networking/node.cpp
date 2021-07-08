/**
 *  @file   node.cpp
 *  @brief  Backend Comunication Interface
 *  @author Aaron Rohrer
 *  @date   2021-07-1 
 ***********************************************/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../../header/Networking/node.h"
#include "socketLibrary.cpp"


void Node::setPersonnelAddress(int port, const char* ip, int transport) {
    personnel_address.sin_family = AF_INET;
    personnel_address.sin_port = htons(port);
    personnel_address.sin_addr.s_addr = inet_addr(ip);
    sockfd = transport;
    bind(sockfd, (struct sockaddr*)&personnel_address, sizeof(personnel_address));
}

char* Node::nextToken(char* arry, int size, char token, int tokens) {
    int i = 0;
    int j = 0;
    while(i < size) {
        if(arry[i] == token) {
            j+=1;
            if(j == tokens) {
                return &arry[i + 2];
            }
        }
        i+=1;
    }
    perror("Accessing out specified size");
    exit(0);
}

void Node::deviceAphiliate() {
    int verifaction = 77;
    unsigned char initial_message[17]; // @(byte) + name(16 byte)        const unsigned char verifaction = 77;

    int status = recvfrom(sockfd, &initial_message, sizeof(initial_message), 0, (struct sockaddr*)&device_address, &sock_length);

    if(status >= 0) {
        sendto(sockfd, &verifaction, sizeof(verifaction), 0, (struct sockaddr*)&device_address, sizeof(device_address));
        name = &initial_message[1];

    }
}

//converts a name from a lookup table to a address from its ip and 
//port


void Node::addToTable(char* name_to_add) {
    lookup_table.push_back(name_to_add);
}

int Node::search_table(char* name) {

    int i = 0;
    while(i < lookup_table.size()) {
        std::cout<<"Searching table\n";
        if(strcmp(name, nextToken(lookup_table[i], 30, '\0', 1)) == 0) {
            std::cout<<"Found name\n";
            return i;
        }
        i += 1;
    }

    return (-1);
}

char* Node::tableName(int index) {
    return nextToken(lookup_table[index], 30, '\0', 1);
}

char* Node::tableIp(int index) {
    return nextToken(lookup_table[index], 30, '\0', 2);
}

char* Node::tablePort(int index) {
    return nextToken(lookup_table[index], 30, '\0', 3);
}

sockaddr_in Node::tableToAddress(int index){
    std::string port_str(nextToken(lookup_table[index], 30, '\0', 3), nextToken(lookup_table[index], 30, '\0', 3) + 5);

    sockaddr_in Address;
    Address.sin_family = AF_INET;
    Address.sin_port = htons(std::stoi(port_str));
    Address.sin_addr.s_addr = inet_addr(nextToken(lookup_table[index], 30, '\0', 2));

    return Address;
}

//connects to a specific device which is one of the options in 
//the lookupTable, can not manually enter only what is in lookup 
//table
//trade names
void Node::connectTo(int index, int instruction) {
    sockaddr_in device = tableToAddress(index);
    sendto(sockfd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, sizeof(device));

    //Internal testing
    //
    if(instruction == 5) {
        std::thread threadObj((streamCamera()), sockfd, sock_length, device);

        while(true) {
            printf("Main thread wiating\n");
        }
    }
}

//listen for a device to ask to connect
////trade names
void Node::listen() {
    int instruction;
    sockaddr_in device;

    recvfrom(sockfd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, &sock_length);
    printf("Sub thread Instruction recieved: %d\n", instruction);

    if(instruction == 5) {
        while(true) {
            sendto(sockfd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, &sock_length);
        }
    }
}

void Node::streamCamera(int fd, socklen_t sock_l, struct sockaddr_in device) {
    int instruction;

    while(true) {
        recvfrom(fd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, &sock_l);
        printf("Instruction back: %d\n", instruction);
    }
}

//internal use only
//
//
void Node::outputTable() {
    int size = lookup_table.size();
    int counter = 0;
    while(counter < size) {
        std::cout<<"Device: "<<counter<<'\n';
        std::cout<<"Name: "<<nextToken(lookup_table[counter], 30, '\0', 1)<<'\n';
        std::cout<<"Ip: "<<nextToken(lookup_table[counter], 30, '\0', 2)<<'\n';
        std::cout<<"Port: "<<nextToken(lookup_table[counter], 30, '\0', 3)<<"\n\n\n";
        counter += 1;
    }
}

void Node::outputName() {
    std::cout<<"Personnel Name: "<<name<<'\n';
}
void Node::outputAddress(sockaddr_in addr) {
    printf("Address> Port: %d Ip: %s\n", ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
}

