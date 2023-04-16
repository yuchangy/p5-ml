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
    
    set<string> unique_words(const string &str, const string &tag) {
        int frequency = 0;
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
              map_pair.insert({{tag, word}, frequency++});
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
            unique_words(row["content"], row["tag"]);
            labels.insert(row["tag"]);
            labelSearch.insert({row["tag"], 0});
            all_data.insert({row["tag"], {row["content"]}});
        }
    }
        
    double find_word_numPost(){
        map<std::string ,string>::iterator it = all_data.begin();
        while(it != all_data.end()){
            
        }
        return 0;
    }
    
    double find_label_numPost(){
        set<string>::iterator itr = labels.begin();
        map<string,int>::iterator it;
        map<string, int>::iterator find;
    
        while(it != labelSearch.end()){
            find = labelSearch.find(*itr);
        }
        return 0;
    }
    
    double find_label_word_numPost(){
        return 0;
    }
    
    void train(string data){
        load(data);
        find_label_word_numPost();
        find_label_numPost();
        find_label_word_numPost();
    }
           //calculation:
    //The classifier should predict whichever label has the
    //highest log-probability score for the post.
    //If multiple labels are tied, predict whichever comes first alphabetically.
    //calculation:
    double label_probability(){
        double prediction = 0;
        double divide = (find_label_numPost()/numPosts);
        prediction = log(divide);
        return prediction;
    }
    double label_probability_with_word(){
        double prediction = 0;
        double divide = (find_label_word_numPost()/find_label_numPost());
        prediction = log(divide);
        return prediction;
    }
    double probability_no_word_in_label(){
        double prediction = 0;
        double divide = (find_word_numPost()/find_label_numPost());
        prediction = log(divide);
        return prediction;
    }
    double probability_no_word(){
        double prediction = 0;
        double divide = (1/numPosts);
        prediction = log(divide);
        return prediction;
    }
       
    double final_probability(){
        double prediction = 0;
        if (find_label_numPost() > 0) {
            prediction = label_probability();
        }
        else if (find_label_word_numPost() > 0) {
            prediction = label_probability_with_word();
        }
        else if (find_label_word_numPost() == 0.0) {
            prediction = probability_no_word_in_label();
        }
        else if (find_word_numPost() == 0.0) {
            prediction = probability_no_word();
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
    prediction.train(input);
    prediction.final_probability();
    
    int numTraining=0;
    cout << "trained on" << numTraining << "examples" << endl;
    cout << "test data:" << endl;
    //some kind of loop
    cout << "correct = " ///<<tag
         << "predicted = " ///<<tag
         << "log-probability score = " ///num
         << "content" << endl;
    
    cout << "performance: " ///2/3
         << "posts predicted correctly"
         << endl;
    
}

