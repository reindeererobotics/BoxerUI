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

    char arry[30] = "\0 Aaron\0 192.168.2.3\0 8003";
    char arry2[30] = "\0 John\0 1.0.0.0\0 8920";
    char arry3[30] = "\0 Mike\0 124.154.3.6\0 8769";

    node.addToTable(arry);
    node.addToTable(arry2);
    node.addToTable(arry3);

    //Information about device in table
    //
    printf("\n\n\n\nInformation about Device in table\n\n");
    char sample_name[20] = "Mike";
    int index = node.search_table(sample_name);

    printf("Search result for Mike: \n");
    printf("Name: %s\n", node.tableName(index));
    printf("Ip: %s\n", node.tableIp(index));
    printf("Port: %s\n\n", node.tablePort(index));
    //

    //node.outputTable();

    //Seeting information for Node
    //
    unsigned char name[16] = "Aaron";
    char ip[30] = "192.168.2.3";
    int port = 8005;
    int transport = socket(AF_INET, SOCK_STREAM, 0);

    node.name = name;
    node.setPersonnelAddress(port, ip, transport);

    //node.outputName();
    //

    node.outputAddress(node.tableToAddress(index));

}
