#include <cstdio>
#include <cassert>
#include "HashSetCalculatorMD5.hpp"
#include "BloomFilter.hpp"

void testHashSetCalculatorMD5()
{
   HashSetCalculatorMD5 hasher;

   const std::string data("hello world");

   const std::vector<ByteBuffer>& hashSet = hasher.calculate(data.c_str(), data.length());

   assert(hashSet.size() == 3);
   assert(hashSet[0].size() == 1);
   assert(hashSet[0][0] == 0x5e);
   assert(hashSet[1].size() == 1);
   assert(hashSet[1][0] == 0xb6);
   assert(hashSet[2].size() == 1);
   assert(hashSet[2][0] == 0x3b);
}

void testBloomFilter()
{
   HashSetCalculatorMD5 hasher;

   BloomFilter filter(hasher);

   filter.feed("hello");
   filter.feed("world");
   
   assert(filter.has("hello"));
   assert(filter.has("world"));
   assert(!filter.has("hell"));
}

int main()
{
   testHashSetCalculatorMD5();
   testBloomFilter();
   puts("OK!");
   return 0;
}
