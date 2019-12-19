#include <fstream>
#include "WordFrequency.h"
#include "sanitize.h"
using namespace std;

WordFrequency::WordFrequency() {}
void WordFrequency::readIn(const string & filename) {
  ifstream find(filename);

  string word;

  while(find >> word) {
    //word goes in the readIn
    sanitize(word);
    //will take out any punctuation not needed
    char punctuation = word[word.size() - 1];

    if(punctuation == '!' || punctuation == '.' || punctuation == '?') {
      word = word.substr(0, word.size() -1);
    }
    if(mymap.count(word) == 0) {
      mymap[word] = 1;
    } else {
      mymap.at(word) += 1;
    }
  }
}

//will return the number of words inside the hash table
size_t WordFrequency::numberOfWords() {
  return mymap.size();
}

//will return the number of times a word shows up
size_t WordFrequency::wordCount(const string & word) {
  return mymap[word];
}

//will return the most frequent word
string WordFrequency::mostFrequentWord() {
  unordered_map<string,int>::iterator it = mymap.begin();
  string mostOccured = it -> first;

  while(it!=mymap.end()) {
    if(mymap[mostOccured] < mymap[it -> first]) {
      mostOccured = it -> first;
    }
    it++;
  }
  return mostOccured;
}

size_t WordFrequency::maxBucketSize() {
  size_t largest = 0;

  for(int i = 0; i < mymap.bucket_count(); i++) {
    if(mymap.bucket_size(i) > largest) {
      largest = mymap.bucket_size(i);
    }
  }
  return largest;
}
