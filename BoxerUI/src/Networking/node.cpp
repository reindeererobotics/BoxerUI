/**
 *  @file   node.cpp
 *  @brief  Backend Comunication Interface
 *  @author Aaron Rohrer
 *  @date   2021-07-1 
 ***********************************************/

#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/epoll.h>
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

    personnel_address.sin_family = AF_INET;
    personnel_address.sin_port = htons(port);
    personnel_address.sin_addr.s_addr = INADDR_ANY;
    Backend::sockfd = transport;
    printf("sockfd: %d\n", transport);

    bind(transport, (struct sockaddr*)&personnel_address, sizeof(personnel_address));
}

void Node::deviceAphiliate() {
    int verifaction = 77;
    unsigned char initial_message[17]; // @(byte) + name(16 byte)        const unsigned char verifaction = 77;

    int status = recvfrom(Backend::sockfd, &initial_message, sizeof(initial_message), 0, (struct sockaddr*)&device_address, &sock_length);

    if(status >= 0) {
        sendto(Backend::sockfd, &verifaction, sizeof(verifaction), 0, (struct sockaddr*)&device_address, sizeof(device_address));
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
    while(true)
    sendto(Backend::sockfd, &instruction, sizeof(instruction), 0, (struct sockaddr*)&device, sizeof(device));

}

//listen for a device to ask to connect
////trade names

struct epoll_event epollInit(int fd) {
    struct epoll_event event;
    event.events = EPOLLIN; // | EPOLLEXCLUSIVE;
    event.data.fd = fd;

    return event;
}

void listenStream(socklen_t sock_l, int t_thread) {
    struct sockaddr_in device;

    int fd = Backend::sockfd;
    struct epoll_event events[1];
    events[0] = epollInit(fd);
    int epfd = epoll_create1(0);
    int res = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &events[0]);

    int data;
    while(true) {
        epoll_wait(epfd, events, 1, -1);
        recvfrom(fd, &data, sizeof(data), MSG_DONTWAIT, (struct sockaddr*)&device, &sock_l);
        //read(events[0].data.fd, &data, sizeof(data));

        printf("Data recieved: %d, from thread %d\n", data, t_thread);
    }
}

void Node::listen() {
   std::thread thread1(listenStream, sock_length, 1);
   thread1.detach();

   std::thread thread2(listenStream, sock_length, 2);
   thread2.detach();

   std::thread thread3(listenStream, sock_length, 3);
   thread3.detach();
   while(true) {}
}


void initStream(int fd, socklen_t sock_l, struct sockaddr_in device, int data) {

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

