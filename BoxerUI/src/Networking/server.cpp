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

#include "backend.cpp"

void returnQuery(std::vector<char*> query, struct sockaddr_in client) {
    int size = query.size();
    sendto(Backend::sockfd, &size, sizeof(size), 0, (struct sockaddr*)&client, sizeof(client));
    sendto(Backend::sockfd, &query[0], size, 0, (struct sockaddr*)&client, sizeof(client));
}

void addClient(char* name, struct sockaddr_in client) {
    char address[30];
    Backend::addressToChars(address, name, client);
    Backend::lookup_table.push_back(address);
}

void queryName(std::vector<char*> names, struct sockaddr_in client) {
    if(names.size() == 0) {
        returnQuery(Backend::lookup_table, client);
    }
    else {
        //search logic
    }
}

