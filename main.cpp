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
    map<string, string> all_data;
    set<string> labels;
    map<string, int> wordSearch; //The number of posts with the word string
    map<string, int> labelSearch; //This item is used to search through so
    map<pair<string, string>, int> map_pair;
    
    
public:
    set<string> unique_words(const string &str) {
      istringstream source(str);
      string word;
      while (source >> word) {
          auto pos = words.find(word);
          if(*pos == word){
              continue;
          }
          else{
              words.insert(word);
              wordSearch.insert({word, 0});
              uniqueWords++;
          }
      }
      return words;
    }
    
    void load(string data){
        csvstream csvin(data);
        map<string, string> row;
        while(csvin >> row){
            numPosts++;
            unique_words(row["content"]);
            labels.insert(row["tag"]);
            labelSearch.insert({row["tag"], 0});
            all_data.insert({row["tag"], {row["content"]}});
        }
    }
    
    void parse_string_from_map(){
        map<std::string, string>::iterator it = all_data.begin();
        while(it != all_data.end()){
            unique_words(it->second);
        }
    }
    void find_word_numPost(){
        map<std::string ,string>::iterator it = all_data.begin();
        while(it != all_data.end()){
            
        }
    }
    
    void find_label_numPost(){
        set<string>::iterator itr = labels.begin();
        map<string,int>::iterator it;
        
        while(it != labelSearch.end()){
            labelSearch.find(*itr);
        }
        
    }
    
    void find_label_word_numPost(){
        
    }
    
    void train(string data){
        load(data);
        find_word_numPost();
        find_label_numPost();
        find_label_word_numPost();
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
    prediction.train(input);
    
    
    
    
    //Training:
    
    
    //Testing:
    
    
    
}
