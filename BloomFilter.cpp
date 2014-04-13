#include "BloomFilter.hpp"
#include <iostream>

BloomFilter::BloomFilter(IHashSetCalculator& hsc)
   : hashSetCalculator(hsc)
   , filterMap(1 << 8, 0)
{
}

void BloomFilter::feed(const std::string& word)
{
   std::cout << "feed: " << word << ": " ;

   std::vector<ByteBuffer> hashes =
      hashSetCalculator.calculate(word.c_str(), word.length());

   for (size_t i = 0; i < hashes.size(); i++)
   {
      std::cout << std::hex << static_cast<int>(hashes[i][0]) << " ";
      filterMap[hashes[i][0]] = 1;
   }
   std::cout << std::endl;
}

bool BloomFilter::has(const std::string& word) const
{
   std::cout << "has: " << word << ": " ;
   std::vector<ByteBuffer> hashes =
      hashSetCalculator.calculate(word.c_str(), word.length());

   for (size_t i = 0; i < hashes.size(); i++)
   {
      std::cout << std::hex << static_cast<int>(hashes[i][0]) << " ";
      if (0 == filterMap[hashes[i][0]])
         return false;
   }
   std::cout << std::endl;

   return true;
}
