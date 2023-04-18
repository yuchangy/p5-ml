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
            uniqueWords++;
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
        set<string> post;
        string final_predict_label = "";
        map<string, double> test_map_item;
        double log_probability_score = 0;
        int performance = 0;
        int num_test_post = 0;
        
        
        csvstream csvin(data);
        map<string, string> row;
        std::cout << "trained on " << numPosts << " examples" << "\n" << "\n";
        std::cout << "test data:" << "\n";
        
        while(csvin >> row){
            post = test_words(row["content"]);
            
            test_map_item = test_map(row["tag"], post);
            
            final_predict_label = final_probability_answer(test_map_item);
            
            log_probability_score = final_probability_num(test_map_item, final_predict_label);
            
            std::cout << "  correct = " << row["tag"] << " predicted = " << final_predict_label <<
            " log-probability score = " << log_probability_score <<"\n";
            
            std::cout << "content = " << row["content"] << "\n";
            
            if(row["tag"] == final_predict_label){
                performance++;
            }
            num_test_post++;
        }
        std::cout << "performance: " << performance << " / " << num_test_post << " posts predicted correctly" << "\n";
        
    }
    
    map<string, double> test_map(string tag, set<string> content){
        map<string, double> predictions;
        predictions[tag] = label_probability(tag);
        
        for(auto it1 = content.begin(); it1!= content.end(); it1++){
            if(detect_label_word_numPost(*it1) == true){
                predictions[tag] += label_probability_with_word(*it1, tag);
            }
            else if(find_word_numPost(*it1)){
                predictions[tag] += probability_no_word_in_label(*it1);
            }
            else{
                predictions[tag] += probability_no_word();
            }
            
        }
        return predictions;
    }
    
    set<string> test_words(const string &str){
        istringstream source(str);
        set<string> words;
        string word;
        while(source >> word){
            words.insert({word});
        }
        return words;
    }
    
    double find_word_numPost(string str){
        map<string, int>::iterator it = wordSearch.find(str);
        
        return it->second;
    }
    
    double find_label_numPost(string str){
        map<string, int>::iterator it = labelSearch.find(str);
        return it->second;
    }
    
    bool detect_word_numPost(string str){
        auto it = wordSearch.find(str);
        if(it != wordSearch.end()){
            return true;
        }
        return false;
    }
    
    bool detect_label_word_numPost(string str){
        map<string, map<string, int>>::iterator it;
        for (it = map_pair.begin(); it != map_pair.end(); it++) {
            for (auto ptr = it->second.begin(); ptr != it->second.end(); ptr++) {
                if(ptr->first == str){
                    return true;
                }
                
            }
            
        }
        return false;
    }
    
    double find_label_word_numPost(string str, string tag){
        return map_pair[tag][str];
        
    }
    
    //calculation:
    double label_probability(string str){
           double prediction = 0;
           double divide = (find_label_numPost(str)/numPosts);
           prediction = log(divide);
           return prediction;
       }
        
       double label_probability_with_word(string str, string tag){
           double prediction = 0;
           double divide = (find_label_word_numPost(str, tag)/find_label_numPost(str));
           prediction = log(divide);
           return prediction;
       }
        
       double probability_no_word_in_label(string str){
           double prediction = 0;
           double divide = (find_word_numPost(str)/find_label_numPost(str));
           prediction = log(divide);
           return prediction;
       }
        
       double probability_no_word(){ // done
           double prediction = 0;
           double divide = (1/numPosts);
           prediction = log(divide);
           return prediction;
       }
//
    
    string final_probability_answer(map<string, double> predict){
        double temp = -10000;
        string label = "";
        for(auto it = predict.begin(); it != predict.end(); it++){
            if(it->second > temp){
                label = it->first;
                temp = it->second;
            }
        }
        
        return label;
    }
    
    double final_probability_num(map<string, double> test_map, string label){
        auto it = test_map.find(label);
        
        return it->second;
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
    
}

