#include <cstdio>
#include <cassert>
#include "HashSetCalculatorMD5.hpp"
#include "BloomFilter.hpp"

void testHashSetCalculatorMD5()
{
   HashSetCalculatorMD5 hasher(1, 3);

   const std::vector<size_t>& hashSet =
      hasher.calculate("hello world");

   assert(hashSet.size() == 3);
   assert(hashSet[0] == 0x5e);
   assert(hashSet[1] == 0xb6);
   assert(hashSet[2] == 0x3b);


   // next data set
   {
      const std::vector<size_t>& hashSet =
         hasher.calculate("hello");

      assert(hashSet.size() == 3);
      assert(hashSet[0] == 0x5d);
      assert(hashSet[1] == 0x41);
      assert(hashSet[2] == 0x40);
   }
}

void testBloomFilter()
{
   HashSetCalculatorMD5 hasher(1, 3);

   BloomFilter filter(hasher);

   filter.feed("hello");
   filter.feed("world");
   
   assert(filter.has("hello"));
   assert(filter.has("world"));
   assert(!filter.has("hell"));
}

void testBloomFilterFail()
{
   HashSetCalculatorMD5 hasher(1, 1);
   BloomFilter filter(hasher);

   filter.feed("-");
   assert(filter.has("*"));
}

void testBiggerTable()
{
   hashSetCalculatorMD5 hasher(4, 4);
   BloomFilter filter(hasher);

   filter.feed("hello");
   filter.feed("world");
   filter.feed("crazy");
   filter.feed("boy");

   assert(filter.has("hello"));
   assert(filter.has("world"));
   assert(filter.has("crazy"));
   assert(filter.has("boy"));
}

int main()
{
   testHashSetCalculatorMD5();
   testBloomFilter();
   testBloomFilterFail();
   puts("OK!");
   return 0;
}
