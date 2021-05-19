#pragma once

#include "socketLibrary.h"
#include <cereal/archives/xml.hpp>
#include <iostream>
#include <string>

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

using namespace std;

struct Photo {
    int elevation;
    int humidity;
    unsigned char name[6];

    template <class Archive>
    void serialize(Archive& ar) {
        ar(elevation, humidity, name);
    }
};

int main() {

    char ip[] = "174.91.98.18";
    //int client = connect_socket(1, 8000, ip);
    //int client = accept(clientConnect, NULL, NULL);

#ifdef _WIN32
    SOCKET client = connect_socket(1, 8000, ip);  //IP, protocal, blah
    //SOCKET server_connect_socket = connect_socket(1, 9000, "0.0.0.0");;  //IP, protocal, blah
#else
    int client = connect_socket(1, 8000, ip)
#endif // _WIN32
        char temp[96];
    char *msg=temp;
    recv(client, msg, 95, 0);

    std::cout << msg << endl;
std:stringstream message;
    message << msg;

    Photo john;
    Photo* ptr = &john;

    {
        cereal::XMLInputArchive archive2(message);
        archive2.loadBinaryValue(ptr, sizeof(int) * 2 + sizeof(char) * 7, "names");
    }

    cereal::XMLOutputArchive archive3(std::cout);
    archive3(john);
}