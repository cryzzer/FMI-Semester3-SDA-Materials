#include <iostream>
#include<vector>
#include<string>
#include<algorithm>

int main(){
    std::string lectures;
    std::cin >> lectures;

    const unsigned int ASCII_LENGTH = 127;
    const int FREE_POS = -69;
    const int TAKEN_POS = -420;


    std::vector<int> indexOfLectures(ASCII_LENGTH,FREE_POS);

    int asciiNumberForChar = 0;
    for(int i = 0; i < lectures.length(); i++){
        asciiNumberForChar = lectures[i];
        if(indexOfLectures[asciiNumberForChar] == FREE_POS){
            indexOfLectures[asciiNumberForChar] = i;
        }
        else{
            indexOfLectures[asciiNumberForChar] = TAKEN_POS;
        }
    }

    std::sort(indexOfLectures.begin(), indexOfLectures.end());

    for (auto && positions : indexOfLectures){
        if(positions >= 0){
            std::cout << positions << ' ';
        }
    }
}