#include <opencv2/highgui/highgui.hpp>

#include "socketLibrary.h"

#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "cerialize.cpp"
#include <string>
#include <vector>

void output(std::vector<char> data, int size) {

    int i = 0;
    while(i < size) {
        std::cout<<data[i]<<'\n';
        i+=1;
    }
}

int main() {//refactor to payloadRecv();

    int client_socket = connect_socket(1, 8000, "0.0.0.0");

    int rows;
    int cols;
    cv::MatStep stp;
    recv(client_socket, &rows, sizeof(int), 0);
    recv(client_socket, &cols, sizeof(int), 0);

    std::cout<<"Received rows cols: "<<rows<<" "<<cols<<'\n';

    int size;
    std::stringstream ss;

    int scale = 1;
    cv::Mat new_frame = cv::Mat(rows, cols, CV_8UC1);
    cv::Mat current_frame = cv::Mat(rows * scale, cols * scale, CV_8UC1);
    while(true) {

        recv(client_socket, &size, sizeof(int), 0);
        char cstr[size];
        recv(client_socket, cstr, size, MSG_WAITALL);
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


        memcpy(new_frame.data, vec.data(), vec.size() * sizeof(unsigned char));

        resize(new_frame, current_frame, cv::Size(), scale, scale);


        //Thought this was working at some pint yesterdY??
        cv::cvtColor(current_frame, current_frame, cv::COLOR_BGR2RGBA);
        std::cout<<"trying to show \n";
        cv::imshow("view", current_frame); 
        std::cout<<"showed image\n";

        // Display frame for 30 milliseconds
        cv::waitKey(180);
    }
}
