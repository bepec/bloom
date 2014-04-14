#include <iostream>
#include <fstream>
#include <cassert>
#include "BloomFilter.hpp"
#include "HashSetCalculatorMD5.hpp"

using namespace std;

int main(int argc, char* argv[])
{
   HashSetCalculatorMD5 hasher(3, 3);
   BloomFilter filter(hasher);

   assert(argc == 2);

   ifstream fin(argv[1]);

   string word;
   int counter = 0;

   while (fin.good())
   {
      fin >> word;
      filter.feed(word);
      ++counter;
   }

   cout << "Read words: " << counter << endl;
   cout << "Please enter a word to check, empty line to finish." << endl;

   while (getline(cin, word) && !word.empty())
   {
      cout << word.length() << endl;
      if (filter.has(word))
      {
         cout << "correct" << endl;
      }
      else
      {
         cout << "unknown" << endl;
      }
   }

   return 0;
}
