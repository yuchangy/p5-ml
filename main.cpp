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
    map<string, int> wordSearch; //The number of posts with the word string
    map<string, int> labelSearch; //This item is used to search through so
    map<string, map<string, int>> map_pair;
    
    
public:
    //training portion:
    void load(string data){
        csvstream csvin(data);
        map<string, string> row;
        while(csvin >> row){
            numPosts++;
            if(label_is_in(row["tag"]) == false){
                labelSearch.insert({row["tag"], 0});
            }
            
            else if(label_is_in(row["tag"])== true){
                labelSearch[row["tag"]]++;
            }
            
            unique_words(row["content"], row["tag"]);
        }
    }
    
    set<string> unique_words(const string &str, const string &tag) {
      istringstream source(str);
        set<string> words;
      string word;
        
        while (source >> word) {
              words.insert({word});
        }
        for(auto it = words.begin(); it != words.end(); it++){
            string value = *it;
            wordSearch[value]++;
            map_pair[tag][value]++;
        }
      return words;
    }
    
    
    const bool label_is_in(string str){
        if(labelSearch.find(str) != labelSearch.end()){
            return true;
        }
        return false;
    }
        
    void train(string data){
        load(data);
    }
    
    void test(string data){
        csvstream csvin(data);
        map<string, string> row;
        while(csvin >> row){
            
        }
    }
    
    double find_word_numPost(){
        
        return 0;
    }
    
    double find_label_numPost(){
        
        return 0;
    }
    
    double find_label_word_numPost(){
        return 0;
    }
    
    
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
       double probability_no_word(){ // done
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
    
      double final_probability2(){
           double prediction1 = 0;
           double prediction2 = 0;
           double prediction3 = 0;
           double prediction4 = 0;
           double log_probability_score = 0;
           
           prediction1 = label_probability();
           prediction2 = label_probability_with_word();
           prediction3 = probability_no_word_in_label();
           prediction4 = probability_no_word();
           
           if (prediction1 > prediction2) {
               log_probability_score = prediction1;
           }
           
           return log_probability_score;
       }
};


int main(int argc, const char * argv[]) {
    
    std::cout.precision(3);
    string input = argv[1];
    string input_test = argv[2];
    ifstream fin(input);
    ifstream testfin(input_test);
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
    
    if(!testfin.is_open()){
        cout << "Error opening file: " << input_test << endl;
        return -1;
    }
    
    EECS280 prediction;
    prediction.train(input);
    prediction.test(input_test);
    
    int numTraining = 0; // num posts
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
    //Training:
    
    
    //Testing:
    

