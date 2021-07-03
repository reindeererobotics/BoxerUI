#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "node.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

std::vector<char*> lookup_table; // name:0.0.0.0:8001


char* nextToken(char* arry, int size, char token) {
    int i = 0;
    while(i < size) {
        if(arry[i] == token) {
            std::cout<<"Next Token: "<<&arry[i+1]<<"\n";
            return &arry[i + 1];
    }
        i+=1;
    }
    perror("Accessing out specified size");
    exit(0);
}

int search_table(char* name) {
    int i = 0;
    while(i < lookup_table.size()) {
        std::cout<<"Searching table\n";
        if(strcmp(name, nextToken(lookup_table[i], 20, '\0')) == 0) {
            std::cout<<"Found name\n";
            return i;
        } 
        i += 1;
    }
    return (-1);
}

//truct sockadd_in tableToAddress(int index) {
//   struct sockaddr_in table_addr;
//
//   table_addr.sin_family = AF_INET;
//   table_addr.sin_port = htons(std::8000);
//   table_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
//

int main() {
//   char device_name[30] = "\0Ricky Bobby\00.0.0.0\08000";
//   char other_name[30] = "\0Magic Man\00.0.0.0:8000";
//   char other_part_name[10] = "Magic Man";
//
//   int j = 0;
//   while(j < 15) {
//       if(j > 7) {
//           lookup_table.insert(lookup_table.begin() + j, other_name);
//           std::cout<<"Populating table\n";
//           j += 1;
//       } else{
//           lookup_table.insert(lookup_table.begin() + j, device_name);
//           std::cout<<"Populating table\n";
//           j += 1;
//       }
//   }
//
//   int g = 0;
//   while(g < lookup_table.size()) {
//       printf("Table Index: %d Table Name: %s\n", g, lookup_table[g] + 1);
//       g+=1;
//   }
//
//   std::cout<<"printing name\n";
//   int index = search_table(other_part_name);
//   if(index == -1) {
//       std::cout<<"Not in lookup table";
//       exit(1);
//   }
//
//   g = 0;
//   while(g < lookup_table.size()) {
//       printf("Table Index: %d Table Name: %s\n", g, lookup_table[g] + 1);
//       g+=1;
//   }
//
//   printf("Index in table: %d\n", index);
//   printf("Name searching for: %s Name found: %s\n", other_name + 1, lookup_table[index] + 1);
//
    char arry[30] = "\0Aaron\0 192.168.2.3\08003";
    char arry2[30] = "\0John\0 123.543.5.1\08920";
    char arry3[30] = "\0Mike\0 345.654.3.6\08769";

    struct Node node;
    node.addToTable(arry);
    node.addToTable(arry2);
    node.addToTable(arry3);

    node.outputTable();
}
