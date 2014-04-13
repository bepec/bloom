#include "BloomFilter.hpp"
#include <iostream>


static const std::size_t BITS_IN_BYTE = 8;

BloomFilter::BloomFilter(IHashSetCalculator& hashSetCalculator)
   : _hashSetCalculator(hashSetCalculator)
   , _filterMap(hsc.getHashSize() << BITS_IN_BYTE, false)
{
   std::cout << "ctor: size=" << _filterMap.size() << std::endl;
}

void BloomFilter::feed(const std::string& word)
{
   std::cout << "feed: " << word << ": " ;

   std::vector<ByteBuffer> hashes =
      _hashSetCalculator.calculate(word.c_str(), word.length());

   for (std::size_t i = 0; i < hashes.size(); i++)
   {
      std::cout << std::hex << static_cast<int>(hashes[i][0]) << " ";
      _filterMap[hashes[i][0]] = true;
   }
   std::cout << std::endl;
}

bool BloomFilter::has(const std::string& word) const
{
   std::cout << "has: " << word << ": " ;
   std::vector<ByteBuffer> hashes =
      _hashSetCalculator.calculate(word.c_str(), word.length());

   for (std::size_t i = 0; i < hashes.size(); i++)
   {
      std::cout << std::hex << static_cast<int>(hashes[i][0]) << " ";
      if (!_filterMap[hashes[i][0]])
         return false;
   }
   std::cout << std::endl;

   return true;
}

