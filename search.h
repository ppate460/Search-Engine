/*
-------------------------------------------------------------------------------------------
    Project 2 - Search Engine 
    
    System: Mac using Visual Studio Code
    Author: Pratik Patel

    Project Overview:
    Recreated the phenomenal technological development using the map and set abstractions
    to buid a document search engine that can find matching pages for a user's query with 
    lightning-fast response time. This is a simplified version of the technology 
    underpinning Spotlight, Google, Bing, and every other modern search engine that you 
    encounter in your day-to-day internet use.

    Creative Component:
    The function named removeStopWords() was added by author as a creative component.
    The job of that function is to read a word of txt file which has majority of the 
    stop words, and erase any stop words within the user provided txt file. 
    The pro of this technique is to reduce the amount of searches done by the program,
    so that program has to compare less number of searches when finding for URLs.
    A grader or professor can uncomment line 116 and line 40 - 63 to check if needed.
-------------------------------------------------------------------------------------------
*/

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;

//-------------------------------------------------------------------------------------------
// this is a "Creative Component" function created by an author.
// removeStopWords() takes a set of cleaned/trimmed version of token and remove
// majority of the stop words from the set.
set<string> removeStopWords(set <string> body) {
    set<string> stopWords;
    string word;
    
    // read the stopwords.txt and store all stop words into a set
    ifstream stopWordsFile("stopwords.txt");
    if (stopWordsFile.is_open()) {
        while ( stopWordsFile.good() ) {
            getline(stopWordsFile, word, '\n');
            word[0] = tolower(word[0]);
            stopWords.insert(word);
        }
    }
    
    // remove majority of the stop words from a set of body 
    for (auto stopWord : stopWords) { 
        for (auto token : body) {
            if (token == stopWord) {
                body.erase(token);
            }
        }
    }
    return body;
} 
// end of removeStopWords()

//-------------------------------------------------------------------------------------------
// cleanToken() takes a string as parameter and return the trimmed
// version of the string, and return empty if it meant to be discarded
string cleanToken(string s) {
    int counter = 0, countChar = 0;

    // remove/erase all of the punctuation in the beginning and ending
    while( ispunct(s[0]) || ispunct(s[s.size()-1]) ) {

        if (ispunct(s[0]) ) { 
            s.erase(0, 1); 
        }
        if (ispunct(s[s.size()-1]) ) { 
            s.erase(s.size()-1, 1); 
        }
    }
    // set the string to lowercase characters
    while (counter <= s.size()) {
        s[counter] = tolower(s[counter]);
        if ( isalpha(s[counter]) ) { 
            countChar++; 
        }
        counter++;
    }
    // discarded string should be returned empty
    if( countChar == 0) { 
        s = ""; 
    }
    return s; 
} // end of cleanToken()

//-------------------------------------------------------------------------------------------
// gatherTokens() takes a string as a parameter and return a set of lowercase parsing
// version of a string without any punctuation at the beginning or ending of a word
set<string> gatherTokens(string text) {
    set<string> tokens;
    string trimmedToken, word;

    stringstream ss(text);
    // read in a word and call cleanToken() to clean a string
    // return the set of strings after calling cleanToken() function
    while (ss >> word) {
        trimmedToken = cleanToken (word);
        if (trimmedToken != "" ) { 
            tokens.insert(trimmedToken); 
        } 
    }

    // this is a creative component function, in order to use this function
    // uncomment line 103 and line 33-57 which is a removeStopWords() function if needed
    // tokens = removeStopWords( tokens );

    return tokens; 
} // end of gatherTokens()

//-------------------------------------------------------------------------------------------
// buildIndex() takes a filename, and map of indexes as a prameter split the file 
// and call gatherToken() to return a set of strings then stores those strings as
// key and set of values required the function returns number of indexes/pages processed
int buildIndex(string filename, map<string, set<string> >& index) {
    
    string url, body;
    int countIndexPages = 0;
    set <string> bodySet;       // body of the URL
    set <string> urlSet;        // https://www.cplusplus.com/......

    ifstream myFile(filename);
    // if the file is succesfully opened, then start reading the file
    if (myFile.is_open()) {
        getline(myFile, url, '\n');
        getline(myFile, body, '\n');

        while ( myFile.good() ) {
            urlSet.insert(url);
            bodySet = gatherTokens(body);
            
            // the nested loop's job is to make_pair of urls and set of strings
            // returned from gatherToken() in map, if the key already exists in the
            // map then add another URL into set of values associated to that key 
            for (auto key : bodySet) {
                for (auto value : urlSet) {
                    index.insert(make_pair(key, urlSet));
                    if (index.count(key)) { 
                        index[key].insert(value); 
                    }
                }
            } 
            urlSet.clear();
            getline(myFile, url, '\n');
            getline(myFile, body, '\n');

            countIndexPages++;
        }
        myFile.close();
    }
    else { 
        cout << "Error opening the file."; 
    }
    return countIndexPages;
} // end of buildIndex()

//-------------------------------------------------------------------------------------------
// storeURL() takes a string of query/sentence and index map
// the function is compating to see if the query exists in the key of map
// if so, insert into a set and return that set
set<string> storeURL( string query, map<string, set<string> > index) {
    set<string> setURLs;

    // looping through the map and comparing every value and see if the value
    // matches the key of the map, if so, insert the value into a set and
    // return a set of URL's which the function does
    for (auto key : index) {
        for (auto value : key.second) {
            if (query == key.first) {
                setURLs.insert(value);
            }
        }
    }
    return setURLs;
}

//-------------------------------------------------------------------------------------------
// findQueryMatches() takes an index map and a sentence as a parameter
// the function returns a set of URL's who contains a sentence in their body
set<string> findQueryMatches(map<string, set<string> >& index, string sentence) {
    set<string> result;         // final calculated URLs
    set<string> spaceQuary;       // vector bool ratio .....
    set<string> spaceURL;       // url of the first query

    set<string> plusWords;       // +vector +bool .....
    set<string> minusWords;      // -vector -bool .....

    set<string> plusURL;        // all URL with +word
    set<string> minusURL;       // all URL with -word
    string word;
    int countPlus = 0, countMinus = 0;

    stringstream ss(sentence);
    // if the user sentences contains + or - then, store them according
    // to their order with + or - in another set, also clean each query
    while (ss >> word) { 
        if (word[0] == '+' ) { 
            countPlus++;
            word = cleanToken(word); 
            plusURL = storeURL (word, index);
            plusWords.insert(word);  
        }
        else if (word[0] == '-' ) {
            countMinus++; 
            word = cleanToken(word); 
            minusURL = storeURL (word, index);
            minusWords.insert(word); 
        }
        else { 
            spaceQuary.insert(word);
            spaceURL = storeURL (word, index); 
        }
    }

    // if user did not enter any + or - , which means no need to do any 
    // intersections or unions or substraction
    if (countPlus == 0 && countMinus == 0) {
        for (auto key : index) {
            for (auto value : key.second) {
                for (auto word : spaceQuary) {
                    if ( key.first == word) { 
                        result.insert(value); 
                    }
                }
            }
        }
    }

    // if the user only enters +'s , which means no need to do any
    // union or subtraction
    if (countPlus > 0 && countMinus == 0) {
        for (auto url1 : spaceURL) { 
            for (auto url2 : plusURL) {
                if (url1 == url2) {
                    result.insert(url2);
                }
            }
        }
    }

    // if the user only enters -'s , which means no need to do any
    // intersections or unionization
    if (countPlus == 0 && countMinus > 0) {
        for (auto url1 : spaceURL) {
            if (minusURL.count(url1) == 0)  {
                result.insert(url1);
            }
        }
    }

    return result;
} // end of findQueryMatches()

//-------------------------------------------------------------------------------------------
// searchEngine() takes a filename as a parameter
// the function pass the filename into buildIndex() function and asks user to enter a
// series of sentences in which they would like to see all URls associated to that sentences,
// they need to use + or - to define which URL's are union or intersection of a sentence
void searchEngine(string filename) {
    map <string, set<string> > buildIndexMap;
    set<string> finalResult;
    string userQuery;       // user input sentence
    int numIndexPages;

    cout << "Stand by while building index...\n";
    // returned value of buildIndex() is the number of total indexes processed
    numIndexPages = buildIndex(filename, buildIndexMap);
    cout << "Indexed " << numIndexPages << " pages containing " << buildIndexMap.size() << " unique terms\n" << endl;

    // do-while() loop will continue to run until user choose to opt out and hit "ENTER-key"
    do {
        cout << "Enter query sentence (press enter to quit): ";
        getline (cin, userQuery);

        finalResult = findQueryMatches(buildIndexMap, userQuery);
        if (userQuery != "") {
            cout << "Found " << finalResult.size() << " matching pages" << endl;
            for (auto url : finalResult) { 
                cout << url << endl; 
            }
            cout << endl;
        }
    } while( userQuery != "" );
    // display thank you message.
    cout << "Thank you for searching!";

} // end of searchEngine()
