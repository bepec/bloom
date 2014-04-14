#include <cassert>
#include <iostream>
#include "BloomFilter.hpp"

using namespace std;

BloomFilter::BloomFilter(IHashSetCalculator& hashSetCalculator)
   : _hashSetCalculator(hashSetCalculator)
   , _filterMap(hashSetCalculator.getMaxHashValue()+1, false)
{
   assert(_filterMap.size() != 0);
}

void BloomFilter::feed(const string& word)
{
   vector<size_t> indices =
      _hashSetCalculator.calculate(word);

   cerr << hex << _filterMap.size() << " >> ";
   for (size_t i = 0; i < indices.size(); i++)
   {
      cerr << indices[i] << " ";
      _filterMap[indices[i]] = true;
   }
   cout << endl;
}

bool BloomFilter::has(const string& word) const
{
   vector<size_t> indices =
      _hashSetCalculator.calculate(word);

   cout << hex << _filterMap.size() << " >> ";
   for (size_t i = 0; i < indices.size(); i++)
   {
      cout << indices[i] << " ";
      if (!_filterMap[indices[i]])
         return false;
   }
   cout << endl;

   return true;
}

