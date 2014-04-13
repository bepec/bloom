#include <cstdio>
#include <cassert>
#include "HashSetCalculatorMD5.hpp"
#include "BloomFilter.hpp"

void testHashSetCalculatorMD5()
{
   HashSetCalculatorMD5 hasher(1, 3);

   const std::vector<ByteBuffer>& hashSet =
      hasher.calculate("hello world");

   assert(hashSet.size() == 3);
   assert(hashSet[0].size() == 1);
   assert(hashSet[0][0] == 0x5e);
   assert(hashSet[1].size() == 1);
   assert(hashSet[1][0] == 0xb6);
   assert(hashSet[2].size() == 1);
   assert(hashSet[2][0] == 0x3b);


   // next data set
   {
      const std::vector<ByteBuffer>& hashSet =
         hasher.calculate("hello");

      assert(hashSet.size() == 3);
      assert(hashSet[0].size() == 1);
      assert(hashSet[0][0] == 0x5d);
      assert(hashSet[1].size() == 1);
      assert(hashSet[1][0] == 0x41);
      assert(hashSet[2].size() == 1);
      assert(hashSet[2][0] == 0x40);
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
   for (unsigned char c = 0; c < 256; c++)
   {
      std::string str(&c, 1);
      assert(!filter.has(str));
      filter.feed(str);
   }
}

int main()
{
   testHashSetCalculatorMD5();
   testBloomFilter();
   puts("OK!");
   return 0;
}
