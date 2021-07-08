/** 
 *  @file   node.h
 *  @brief  Backend Comunication Interface header
 *  @author Aaron Rohrer
 *  @date   2021-07-1 
 ***********************************************/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct Node {
    std::vector<char*> lookup_table;
    socklen_t sock_length;
    int sockfd;
    sockaddr_in device_address;
    sockaddr_in  personnel_address;
    const unsigned char* name;

    /** @brief Mutates the |personnel_address| member to use as the 
      nodes address which other nodes will use to comunicate with it.
      @param |int port| is the internal port the node will use to listen on, 
      |const char* ip| is the internal IP the node will lsiten on.
      @return This function returns no value, only mutates the 
      |personnel_address| member.
     **/
    void setPersonnelAddress(int port, const char* ip, int transport);

    char* nextToken(char* arry, int size, char token, int tokens);

    void deviceAphiliate();

    void addToTable(char* name_to_add);

    int search_table(char* name);

    char* tableName(int index);

    char* tableIp(int index);

    char* tablePort(int index);

    sockaddr_in tableToAddress(int index);

    void connectTo(int index, int instruction);

    void listen();

    static void streamCamera(int fd, socklen_t sock_l, struct sockaddr_in device);

    //Internal Testing
    //
    void outputTable();

    void outputName();

    void outputAddress(sockaddr_in addr);

};

