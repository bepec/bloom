#include <cassert>
#include "BloomFilter.hpp"

using namespace std;

static const size_t BITS_IN_BYTE = 8;

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

   for (size_t i = 0; i < indices.size(); i++)
   {
      _filterMap[indices[i]] = true;
   }
}

bool BloomFilter::has(const string& word) const
{
   vector<size_t> indices =
      _hashSetCalculator.calculate(word);

   for (size_t i = 0; i < indices.size(); i++)
   {
      if (!_filterMap[indices[i]])
         return false;
   }

   return true;
}

