#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct Node {
    bool life = false;
    std::vector<char*> lookup_table; // name:0.0.0.0:8001
    //bool listening = false;
    //int node_count = 0;
    //int node_port = 0;

    socklen_t sock_length;
    int sockfd = NULL;
    sockaddr_in device_address;
    sockaddr_in  personnel_address;
    //const int global_port = 0;
    unsigned char* name;

    void setPersonnelAddress(int port, const char* ip) {
        personnel_address.sin_family = AF_INET;
        personnel_address.sin_port = htons(port);
        personnel_address.sin_addr.s_addr = inet_addr(ip);
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    }

    char* nextToken(char* arry, int size, char token, int tokens) {
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

    void deviceAphiliate() {
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


    void addToTable(char* name_to_add) {
        lookup_table.push_back(name_to_add);
    }

    int search_table(char* name) {

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

    char* tableName(int index) {
        return nextToken(lookup_table[index], 30, '\0', 1);
    }

    char* tableIp(int index) {
        return nextToken(lookup_table[index], 30, '\0', 2);
    }

    char* tablePort(int index) {
        return nextToken(lookup_table[index], 30, '\0', 3);
    }

    sockaddr_in tableToAddress(int index){
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
    void connectTo() {

    }

    //listen for a device to ask to connect
    ////trade names
    void listen() {
    }

    //internal use only
    //
    //
    void outputTable() {
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

    void outputName() {
        std::cout<<"Personnel Name: "<<name<<'\n';
    }
    void outputAddress(sockaddr_in addr) {
        printf("Address> Port: %d Ip: %s\n", ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
    }

};


