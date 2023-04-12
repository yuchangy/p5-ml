// Project UID db1f506d06d84ab787baf250c265e24e
//  main.cpp
//  p5-ml
//
//  Created by Andrew Yu on 3/30/23.
//

#include <iostream>
#include <map>
#include <string>
#include "csvstream.h"
#include <vector>
#include <set>
#include <cmath>

using namespace std;

int main(int argc, const char * argv[]) {
    
    //Command Line Check:
    if(argc != 3 || argc != 4){
        std::cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << std::endl;
        return -1;
    }
    
    if(std::string(argv[3]) != "--debug"){
        std::cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << std::endl;
        return -1;

    }
    //Construct Classifier ADT:
    class EECS280{
    private:
        int numPosts = 0;
        int uniqueWords = 0;
        map<string, int> wordSearch;
        map<string, int> labeSearch;
        map<pair<string, string>, int> map_pair;
        set<string> unique_words;
        
    public:
        //Training:
        std::string file_name;
        
        
        //calculation:
        double label_probability(){
            double prediction = 0;
            return prediction;
        }
        double label_probability_with_word(){
            double prediction = 0;
            return prediction;
        }
        
        double final_probability(){
            double prediction = 0;
            return prediction;
        }
        
    };
    
    //Training:
    
    
    
    //Testing:
    
    
    
}
