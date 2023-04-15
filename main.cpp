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

class EECS280{
private:
    int numPosts = 0;
    int uniqueWords = 0;
    set<string> words;
    map<string, int> wordSearch; //The number of posts with the word string
    map<string, int> labelSearch; //This item is used to search through so
    map<pair<string, string>, int> map_pair;
    
    
public:
    set<string> unique_words(const string &str, const string tag) {
        int frequency = 0;
      istringstream source(str);
      string word;
      while (source >> word) {
          auto pos = words.find(word);
          if(*pos == word){
              continue;
              
          }else{
              uniqueWords++;
              words.insert(word);
              map_pair.insert({{tag, word}, frequency++});
          }
      }
      return words;
    }
    
    int wordSearch_frequency(){
        return 0;
    }
    
    int get_numPosts(){
        return numPosts;
    }
    
    int get_uniqueWords(){
        return uniqueWords;
    }
    
    map<string, int> get_labelSearch(){
        return labelSearch;
    }
    
    set<string> get_words(){
        return words;
    }
    
    map<pair<string, string>, int> map_search(map<string, string>){
        assert(false);
    }
    
    //for(auto i:m ){
    //  cout << i.first << " " << i.second << endl;
    
    void open_file(string data){
        csvstream csvin(data);
        map<string, string> row;
        
        while(csvin >> row){
            numPosts++;
            unique_words(row["content"], row["tag"]);
            
            
        }
        
        
    }
    
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


int main(int argc, const char * argv[]) {
    
    std::cout.precision(3);
    string input = argv[1];
    ifstream fin(input);
    //Command Line Check:
    if(argc != 3 && argc != 4){
        std::cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << std::endl;
        return -1;
    }
    
    if(std::string(argv[3]) != "--debug"){
        std::cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << std::endl;
        return -1;
    }

    if (!fin.is_open()) {
        cout << "Error opening file: " << input << endl;
        return -1;
    }
    
    EECS280 prediction;
    prediction.open_file(input);
    
    
    
    //Training:
    
    
    //Testing:
    
    
    
}
