#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "node.cpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


void addToHeap(char* arry, char value, int max) {
    int i = 0;

    while(i < max) {
        arry[i] = value;
        i+=1;
    }
}
 void printHeap(char* arry, int max) {
     int i = 0;

     printf("First address is: %d\n", &arry[0]);
     while(i < max) {
         printf("%c", arry[i]);
         i+=1;
     }
     printf("\n");
 }

int main() {
    char* array = (char*)calloc(1, sizeof(char[5]));
    addToHeap(array, 'A', 5);
    printHeap(array, 5);

    char* array2 = (char*)calloc(1, sizeof(char[5]));
    addToHeap(array2, 'B', 5);
    printHeap(array2, 5);

    array = (char*)realloc(array, sizeof(char[20]));
    addToHeap(array, 'C', 20);
    printHeap(array, 20);

    printHeap(array2, 5);


//  int k = 0;
//   struct Node node;
//
//   char arry[30] = "\0 Robot\0 0.0.0.0\0 8005";
//   node.addToTable(arry);
//
//   printf("Table fn: %s\n", Backend::tableIp(0));
//
//   struct sockaddr_in address = Backend::tableToAddress(0);
//
//   char identity[30] = "\0 ";
//   char name[10] = "Ricky";
//
//   Backend::addressToChars(identity, name, address);
//   printf("Full identity:\n%s\n%s\n%s\n", identity + 2, identity + 9, identity + 18);
}
