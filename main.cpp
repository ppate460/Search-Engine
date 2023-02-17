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

#include <iostream>
#include "search.h"
using namespace std;

int main() {

    // map <string, set<string> > buildIndexMap;

    // string str = "?>><>678const7d>?#$^@";
    // str = cleanToken(str);
    // gatherTokens(str);
    // cout << str << endl;

    // buildIndex(fileName, buildIndexMap);
    // findQueryMatches(buildIndexMap, sentence);

    searchEngine("wiki-unit.txt"); //

    return 0;
}

