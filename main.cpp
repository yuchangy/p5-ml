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
    double numPosts = 0;
    int uniqueWords = 0;
    map<string, int> wordSearch;
    map<string, int> labelSearch;
    map<string, map<string, int>> map_pair;
    
public:
    //training portion:
    void load(string data, bool debug){
        csvstream csvin(data);
        map<string, string> row;
        while(csvin >> row){
            numPosts++;
            if(label_is_in(row["tag"]) == false){
                labelSearch.insert({row["tag"], 1});
            }
            
            else if(label_is_in(row["tag"])== true){
                labelSearch[row["tag"]]++;
            }
            
            unique_words(row["content"], row["tag"]);
            
            if(debug == true){
                std::cout << "  label = " << row["tag"] << ", content = " << row["content"] << "\n" << "\n";
            }
        }
        uniqueWords = wordSearch.size();
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
    
    void debug(string data, string train,  bool debug){
        //print trained Data
        std::cout << "training data: " << "\n";
        
        load(train, debug);
        
        std::cout << "trained on " << numPosts << " examples" << "\n";
        std::cout << "vocabulary size = " << uniqueWords << "\n" << "\n";
        
        //print test daata
        std::cout << "classes:" << "\n";
        for(auto it = labelSearch.begin(); it != labelSearch.end(); it++){
            std::cout << "  " << it->first << ", "
            << it->second << " examples, log-prior = "<<
            label_probability(it->first) << "\n";
        }
        
        //classifier parameters:
        std::cout << "classifier parameters: " << "\n";
        
        for(auto outer = map_pair.begin(); outer != map_pair.end(); outer++){
            for(auto inner = outer->second.begin();
                inner != outer->second.end();  inner++){
                std::cout << "  " << outer->first << ":"
                << inner->first <<", count = " << inner->second
                << ", log-likelihood = "
                << label_probability_with_word(inner->first, outer->first)
                << "\n";
            }
        }
        test(data, debug);
    }
        
    void train(string data, bool debug){
        load(data, debug);
    }
    
    void test_debug(string data, bool debug){
        test(data, debug);
    }
    
    void test(string data, bool debug){
        set<string> post;
        string final_predict_label = "";
        map<string, double> test_map_item;
        double log_probability_score = 0;
        int performance = 0;
        int num_test_post = 0;
        
        csvstream csvin(data);
        map<string, string> row;
        if(debug == true){
            std::cout << "trained on " << numPosts
            << " examples" << "\n" << "\n";

        }
        
        std::cout << "test data:" << "\n";
        
        while(csvin >> row){
            post = test_words(row["content"]);
            //parses all the contents
            double predictions = label_probability(row["tag"]);
            
            for(auto it1 = post.begin(); it1!= post.end(); it1++){
                if(detect_label_word_numPost(*it1, row["tag"]) == true){
                    predictions += label_probability_with_word(*it1, row["tag"]);
                    final_predict_label = row["tag"];
                }
                else if(detect_word_numPost(*it1) == true){
                    predictions +=  probability_no_word_in_label(*it1,row["tag"]);
                    final_predict_label = find_word_with_label(*it1);
                }
                else{
                    predictions += probability_no_word();
                }
                
            }
            
            log_probability_score = predictions;
            
            std::cout << "  correct = " << row["tag"] <<
                        " predicted = " << final_predict_label <<
            " log-probability score = " << log_probability_score <<"\n";
            
            std::cout << "  content = " << row["content"] << "\n";
            
            if(row["tag"] == final_predict_label){
                performance++;
            }
            num_test_post++;
        }
        std::cout << "performance: " << performance << " / " <<
        num_test_post << " posts predicted correctly" << "\n";
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
    
    string find_word_with_label(string str){
        for(auto it = map_pair.begin(); it != map_pair.end(); it++){
            for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                if(it2->first == str){
                    return it->first;
                }
            }
        }
        return " ";
    }
        
        
    bool detect_word_numPost(string str){
        auto it = wordSearch.find(str);
        if(it != wordSearch.end()){
            return true;
        }
        return false;
    }
    
    bool detect_label_word_numPost(string str, string tag){
        map<string, map<string, int>>::iterator it = map_pair.find(tag);
        
        for (auto ptr = it->second.begin(); ptr != it->second.end(); ptr++) {
                if(ptr->first == str){
                    return true;
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
           double divide = (double(find_label_numPost(str)/numPosts));
           prediction = log(divide);
           return prediction;
       }
        
       double label_probability_with_word(string str, string tag){
           double prediction = 0;
           double divide = 0;
           divide = (double(find_label_word_numPost(str, tag)/find_label_numPost(tag)));
           prediction = log(divide);
           return prediction;
       }
        
       double probability_no_word_in_label(string str, string tag){
           double prediction = 0;
           double divide = (double(find_word_numPost(str)
                                   /find_label_numPost(tag)));
           prediction = log(divide);
           return prediction;
       }
        
       double probability_no_word(){ // done
           double prediction = 0;
           double divide = 0;
           divide = 1.0/numPosts;
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
    
    cout.precision(3);
    ifstream fin(argv[1]);
    ifstream testfin(argv[2]);
    EECS280 prediction;
    bool debug = false;

    //Command Line Check:
    if(argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    if (argc == 4) {
    string hi = argv[3];
        if(hi == "--debug"){
            debug = true;
            prediction.debug(argv[2], argv[1], debug);

    }
    else if(hi != "--debug"){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    }
    if (!fin.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return -1;
    }
    
    if(!testfin.is_open()){
        cout << "Error opening file: " << argv[2] << endl;
        return -1;
    }
    
    prediction.train(argv[1], debug);
    prediction.test(argv[2], debug)
}
