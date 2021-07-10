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
#include "backend.cpp"
//#include "socketLibrary.cpp"


void Node::setPersonnelAddress(unsigned char* name, int port, const char* ip, int transport) {
    Backend::name = name;

    Backend::personnel_address.sin_family = AF_INET;
    Backend::personnel_address.sin_port = htons(port);
    Backend::personnel_address.sin_addr.s_addr = inet_addr(ip);
    Backend::sockfd = transport;

    bind(Backend::sockfd, (struct sockaddr*)&Backend::personnel_address, sizeof(Backend::personnel_address));
}

void Node::deviceAphiliate() {
    int verifaction = 77;
    unsigned char initial_message[17]; // @(byte) + name(16 byte)        const unsigned char verifaction = 77;

    int status = recvfrom(Backend::sockfd, &initial_message, sizeof(initial_message), 0, (struct sockaddr*)&Backend::device_address, &sock_length);

    if(status >= 0) {
        sendto(Backend::sockfd, &verifaction, sizeof(verifaction), 0, (struct sockaddr*)&Backend::device_address, sizeof(Backend::device_address));
        Backend::name = &initial_message[1];

    }
}

//converts a name from a lookup table to a address from its ip and 
//port


//Bring out of struct
void Node::addToTable(char* name_to_add) {
    Backend::lookup_table.push_back(name_to_add);
}


//connects to a specific device which is one of the options in 
//the lookupTable, can not manually enter only what is in lookup 
//table
//trade names
void Node::connectTo(int index, int instruction) {
    sockaddr_in device = Backend::tableToAddress(index);
    //sendto(Backend::sockfd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, sizeof(device));

    std::thread threadObj(streamCamera, Backend::sockfd, sock_length, device, instruction);
    threadObj.join();
}

//listen for a device to ask to connect
////trade names
void Node::listen() {
    int instruction;
    sockaddr_in device;
    int fd = Backend::sockfd;

    int status;

    status = recvfrom(fd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, &sock_length);
    if(status < 0) {
        perror("Error recieving \n");
    }
    printf("Value: %d\n", instruction);
    status = sendto(fd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, sizeof(device));
    if(status < 0) {
        perror("Error sending\n");
    }
}

void Node::streamCamera(int fd, socklen_t sock_l, struct sockaddr_in device, int data) {
    //printf("Thread running\n");

    int status;

        status = sendto(fd, &data, sizeof(data), 0, (struct sockaddr*)&device, sizeof(device));
    if(status < 0) {
        perror("Error sending\n");
    }
        int instruction;
        status = recvfrom(fd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, &sock_length);
    if(status < 0) {
        perror("Error recieving \n");
    }
        printf("Value: %d", instruction);
}

//internal use only
//
//
void Node::outputTable() {
    int size = Backend::lookup_table.size();
    int counter = 0;
    while(counter < size) {
        std::cout<<"Device: "<<counter<<'\n';
        std::cout<<"Name: "<<Backend::nextToken(Backend::lookup_table[counter], 30, '\0', 1)<<'\n';
        std::cout<<"Ip: "<<Backend::nextToken(Backend::lookup_table[counter], 30, '\0', 2)<<'\n';
        std::cout<<"Port: "<<Backend::nextToken(Backend::lookup_table[counter], 30, '\0', 3)<<"\n\n\n";
        counter += 1;
    }
}

void Node::outputName() {
    std::cout<<"Personnel Name: "<<Backend::name<<'\n';
}
void Node::outputAddress(sockaddr_in addr) {
    printf("Address> Port: %d Ip: %s\n", ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
}

