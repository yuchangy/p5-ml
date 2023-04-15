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
     //The classifier should predict whichever label has the highest log-probability score for the post. If multiple labels are tied, predict whichever comes first alphabetically.
    //calculation:
    double label_probability(){
        double prediction = 0;
        int numC = 0;
        double divide = (numC/numPosts);
        prediction = log(divide);
        return prediction;
    }
    double label_probability_with_word(){
        double prediction = 0;
        int numCW = 0;
        double divide = (numCW/numPosts);
        prediction = log(divide);
        return prediction;
    }
    
    double label_probability_new_word(){
        double prediction = 0;
        string word;
        if (words.find(word) == words.end()) {
            double divide = (1/numPosts);
            prediction = log(divide);
        }
       
        return prediction;
    }
    double final_probability(){
        double prediction = 0;
        string word;
        string tag;
        int frequency;
      
        //does not occur in posts labeled
        // but does occur in the training data overall
        //  map_pair.find({{tag, word}, frequency});
        if (words.find(word) != words.end()) {
          //      && !(map_pair) {
            double divide = (frequency/numPosts);
            prediction = log(divide);
        }
       
        //word does not occur anywhere at all in the training set
        else if (words.find(word) == words.end()) {
            double divide = (1/numPosts);
            prediction = log(divide);
        }
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
    prediction.final_probability();
    
    int numTraining=0;
    cout << "trained on" << numTraining << "examples" << endl;
    cout << "test data:" << endl;
    //some kind of loop
    cout << "correct = " ///<<tag
         << "predicted = " ///<<tag
         << "log-probability score = " ///<<num
         << "content" << endl;
    
    cout << "performance: " ///2/3
         << "posts predicted correctly"
         << endl;
    
    
    
    //Training:
    
    //split string into words
    // EFFECTS: Return a set of unique whitespace delimited words.x
    //set<string> unique_words(const string &str) {
    //  istringstream source(str);
    //  set<string> words;
    //  string word;
    //  while (source >> word) {
    //    words.insert(word);
    //  }
    //  return words;
    //}

    
    
    //Testing:
    
    
    
}

