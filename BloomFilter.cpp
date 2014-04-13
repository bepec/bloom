#include "BloomFilter.hpp"
#include <iostream>


static const std::size_t BITS_IN_BYTE = 8;

BloomFilter::BloomFilter(IHashSetCalculator& hashSetCalculator)
   : _hashSetCalculator(hashSetCalculator)
   , _filterMap(hashSetCalculator.getHashSize() << BITS_IN_BYTE, false)
{
   std::cout << "ctor: size=" << _filterMap.size() << std::endl;
}

void BloomFilter::feed(const std::string& word)
{
   std::cout << "feed: " << word << ": " ;

   std::vector<std::size_t> indices =
      _hashSetCalculator.calculate(word);

   for (std::size_t i = 0; i < indices.size(); i++)
   {
      std::cout << std::hex << indices[i] << " ";
      _filterMap[indices[i]] = true;
   }
   std::cout << std::endl;
}

bool BloomFilter::has(const std::string& word) const
{
   std::cout << "has: " << word << ": " ;
   std::vector<std::size_t> indices =
      _hashSetCalculator.calculate(word);

   for (std::size_t i = 0; i < indices.size(); i++)
   {
      std::cout << std::hex << indices[i] << " ";
      if (!_filterMap[indices[i]])
         return false;
   }
   std::cout << std::endl;

   return true;
}

