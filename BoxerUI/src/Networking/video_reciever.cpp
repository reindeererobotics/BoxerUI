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

int main() {

    int client_socket = connect_socket(1, 8000, "184.146.119.106");

    int rows;
    int cols;
    cv::MatStep stp;
    recv(client_socket, &rows, sizeof(int), 0);
    recv(client_socket, &cols, sizeof(int), 0);

    std::cout<<"Received rows cols: "<<rows<<" "<<cols<<'\n';

    int size;
    std::stringstream ss;

    while(true) {

        recv(client_socket, &size, sizeof(int), 0);
        char cstr[size];
        recv(client_socket, cstr, size, 0);
        std::cout<<"recieved data\n";

        int count = 0;
        while(count < size) {
        ss << cstr[count];
        count += 1;
        }
        std::cout<<ss.str()<<"\n\n";

        std::vector<unsigned short> vec;
        {
            cereal::BinaryInputArchive archive(ss);
            archive(CEREAL_NVP(vec));
        }
        std::cout<<"serealized\n"<<ss.str()<<'\n';
        ss.str("");


        cv::Mat new_frame = cv::Mat(rows, cols, CV_16UC1);
        memcpy(new_frame.data, vec.data(), vec.size() * sizeof(unsigned short));

      cv::Mat current_frame = cv::Mat(720, 1280, CV_16UC1);
      resize(new_frame, current_frame, cv::Size(), 100, 100);


        //Thought this was working at some pint yesterdY??
        std::cout<<"trying to show \n";
        cv::imshow("view", current_frame); 
        std::cout<<"showed image\n";

        // Display frame for 30 milliseconds
        cv::waitKey(220);
        cv::destroyWindow("view");
    }
}
