#include <opencv2/highgui/highgui.hpp>

#include "socketLibrary.h"

#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string>
#include <vector>

//vector<char> int size -> IO
void output(std::vector<char> data, int size) {

    int i = 0;
    while(i < size) {
        std::cout<<data[i]<<'\n';
        i+=1;
    }
}



struct sockaddr_in serveraddr;
socklen_t serveraddrLength;
int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

int main() {

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);
    serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int status = 0;

    int rows;
    int cols;
    bool activity = true;
    cv::MatStep stp;

    status = sendto(sockfd, &activity, sizeof(bool), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(status < 0)
        perror("send failed");
    std::cout<<"sent activity\n";
    recvfrom(sockfd, &rows, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);
    recvfrom(sockfd, &cols, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);

    std::cout<<"\nReceived rows cols: "<<rows<<" "<<cols<<'\n';
    std::cout<<"size of frame "<<rows*cols<<'\n';

    int size;
    std::stringstream ss;

    int scale = 1;
    cv::Mat new_frame = cv::Mat(rows, cols, CV_8UC4);
    cv::Mat current_frame = cv::Mat(rows * scale, cols * scale, CV_8UC4);
    while(true) {

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

        int count = 0;
        while(count < size) {
            ss << cstr[count];
            count += 1;
        }
        std::cout<<ss.str()<<"\n\n";

        std::vector<unsigned char> vec;
        {
            cereal::BinaryInputArchive archive(ss);
            archive(CEREAL_NVP(vec));
        }
        std::cout<<"serealized\n"<<ss.str()<<'\n';
        ss.str("");


        current_frame = decodeFrame(vec);


        //Thought this was working at some pint yesterdY??
        //cv::cvtColor(current_frame, current_frame, cv::COLOR_BGR2RGBA);
        std::cout<<"trying to show \n";
        cv::imshow("view", current_frame); 
        std::cout<<"showed image\n";

        // Display frame for 30 milliseconds
        cv::waitKey(30);
    }
}
