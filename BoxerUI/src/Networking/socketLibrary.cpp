#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "frame_computation.h"

#include <opencv2/highgui/highgui.hpp>

int status;

//Mat -> string
std::string serealizeFrame(cv::Mat new_frame, std::vector<unsigned char> compressed_frame) {
    std::vector<unsigned char> vec;
    if(compressed_frame.size() != 0){
        std::cout<<"Seriliased jpg/png encoding\n";
        vec = compressed_frame;
    } else {
        std::vector<unsigned char> frameVec(new_frame.begin<unsigned char>(), new_frame.end<unsigned char>());
        vec = frameVec;
    }

    std::stringstream ss;
    {
        cereal::BinaryOutputArchive archive(ss);
        archive(CEREAL_NVP(vec));
    }

    return ss.str();

}

//i32 i32 -> u1
struct sockaddr_in sendFrameOverhead(int rows, int cols, struct sockaddr_in serveraddr, struct sockaddr_in clientaddr, int sockfd) {
    socklen_t clientaddrLength, serveraddrLength;

    bool activity = false;
    while(activity == false)
        status = recvfrom(sockfd, &activity, sizeof(bool), 0, (struct sockaddr*)&clientaddr, &clientaddrLength);
    if(status < 0)
        perror("recv error");

    std::cout<<activity<<'\n';

    status = sendto(sockfd, &rows, sizeof(int), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0)
        perror("semd error");
    status = sendto(sockfd, &cols, sizeof(int), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0)
        perror("send error");

    std::cout<<"Sent row col stp: "<<rows<<" "<<cols<<'\n';

    return clientaddr;
}


struct FrameStructure {
    int rows = 0;
    int cols = 0;
};

struct FrameStructure recvFrameOverhead(int sockfd, struct sockaddr_in serveraddr) {
    socklen_t clientaddrLength, serveraddrLength;
    struct FrameStructure Overhead;

    bool activity = true;
    status = sendto(sockfd, &activity, sizeof(bool), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(status < 0)
        perror("send failed");
    std::cout<<"sent activity\n";

    recvfrom(sockfd, &Overhead.rows, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);
    recvfrom(sockfd, &Overhead.cols, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);

    std::cout<<"\nReceived rows cols: "<<Overhead.rows<<" "<<Overhead.cols<<'\n';
    std::cout<<"size of frame "<<Overhead.rows * Overhead.cols<<'\n';

    return Overhead;
}

void sendFrame(cv::Mat new_frame, struct sockaddr_in serveraddr, struct sockaddr_in clientaddr, int sockfd) {
    socklen_t clientaddrLength, serveraddrLength;

    std::vector<unsigned char> encode_vec = encodeFrame(new_frame, 0);
    std::string str = serealizeFrame(new_frame, encode_vec);

    int size = str.length();

    const char* cstr = str.c_str();

    std::cout<<"size of frame is "<<size<<'\n';
    status = sendto(sockfd, &size, sizeof(int), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0) {
        perror("Perameter <size> failed to send..");
        exit(0);
    }

    std::cout<<"Size of frame "<<size<<'\n';
    status = sendto(sockfd, cstr, size, 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0) {
        perror("Perameter <cstr> failed to send..");
        exit(0);
    }
}

cv::Mat recvFrame(int sockfd, struct sockaddr_in serveraddr) {
    socklen_t clientaddrLength, serveraddrLength;
    int size;

    std::cout<<"Starting to recieve\n";
    status = recvfrom(sockfd, &size, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);
    if(status < 0)
        perror("recv error");

    char cstr[size];
    std::cout<<"Size of frame "<<size<<'\n';
    status = recvfrom(sockfd, cstr, size, MSG_WAITALL, (struct sockaddr*)&serveraddr, &serveraddrLength);
    if(status < 0)
        perror("recv error");
    std::cout<<"recieved data\n";


    std::vector<unsigned char> vec = deserializeFrame(cstr, size);

    return decodeFrame(vec);
}

//Socket Automation
//
struct initialize {
    struct sockaddr_in sockets;
    int network_socket;
};

//creates the socket, the socket() function is not propper as it 
//should follow the function inputs
struct initialize socket_initialise(int ipType, int port, const char * ip) {
    struct initialize setup;
    //struct sockaddr_in server_address = setup.sockets;
    setup.network_socket = socket(AF_INET, SOCK_STREAM, 0); //ip protocal blah

    if(ipType == 1) {
        setup.sockets.sin_family = AF_INET; //set ipv4
    } else {
        setup.sockets.sin_family = AF_INET; //set ipv6
    }

    setup.sockets.sin_port = htons(port); //set port to alocate or target
    setup.sockets.sin_addr.s_addr = inet_addr(ip); // inet_addr was form before

    return setup;
}


//allows other processes to talk with master to ask for data to be 
//sent to them. They will have to recieve the data after after

int listen_socket(int a, int b, const char * c) {
    struct initialize setup = socket_initialise(a, b, c); //iptype port address
    int network_socket = setup.network_socket;
    struct sockaddr_in server_address = setup.sockets;

    bind(network_socket, (struct sockaddr*) &server_address, sizeof(server_address)); //reserves port for server on machine

    listen(network_socket, 1); //listen for clients to connect

    return network_socket;
}

int connect_socket(int a, int b, const char * c) {
    struct initialize setup = socket_initialise(a, b, c); //iptype port address
    int network_socket = setup.network_socket;
    struct sockaddr_in server_address = setup.sockets;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)); //Requests to connect to the server
    if (connection_status == -1) //if connection fail print
        printf("Error during connect");

    return network_socket;
}

//exaple 0, depricated!!!
/*
   int main() {
   struct initialize setup = socket_initialise(1, 9001, "0.0.0.0"); //iptype port address
   int network_socket = setup.network_socket;
   struct sockaddr_in server_address = setup.sockets;

   bind(network_socket, (struct sockaddr*) &server_address, sizeof(server_address)); //reserves port for server on machine
   listen(network_socket, 5); //listen for clients to connect
   int client_socket = accept(network_socket, NULL, NULL); //block communications unless a connection is requested

   char value[20] = "Hello World";
   send(network_socket, &value, sizeof(value), 0); //sending the string value to the client

   close(network_socket); //closing connection
   return 0;
   }
   */

//example 2: connect to machine, then send data
/*
   int main() {
   int network_socket_1 = connect_socket(1, 8999, "0.0.0.0");

   int value = 5;
   send(network_socket_1, &value, sizeof(value), 0); //sending the string value to the client

   close(network_socket_1); //closing connection
   return 0;
   }
   */

//example 3: listen for machine to connect, then recieve a message
/*
   int main() {
   int network_socket_2 = listen_socket(1, 8999, "0.0.0.0");

   char server_response[20];
   recv(network_socket_2, &server_response, sizeof(server_response), 0); //Recieve the message sent from server and store it in server_response

   close(network_socket_2); //closing connection
   return 0;
   }
   */
