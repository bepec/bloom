#include <stdexcept>
#include "HashSetCalculatorMD5.hpp"

HashSetCalculatorMD5::HashSetCalculatorMD5(std::size_t hashSize, std::size_t setSize)
   : _hashSize(hashSize)
   , _setSize(setSize)
{
   if ((_hashSize > sizeof(std::size_t)) ||
       (_hashSize * _setSize > MD5_DIGEST_LENGTH))
   {
      throw std::logic_error("Digest length overflow!");
   }
}

HashSetCalculatorMD5::~HashSetCalculatorMD5()
{
   // nothing to do
}

std::size_t HashSetCalculatorMD5::getSetSize() const
{
   return _setSize;
}

std::size_t HashSetCalculatorMD5::getHashSize() const
{
   return _hashSize;
}

std::vector<std::size_t> HashSetCalculatorMD5::calculate(const void* buffer, std::size_t size) const
{
   MD5_CTX md5Context;

   unsigned char md5Digest[MD5_DIGEST_LENGTH];
   size_t * indices = reinterpret_cast<size_t*>(md5Digest);

   if ((0 == MD5_Init(&md5Context)) ||
       (0 == MD5_Update(&md5Context, buffer, size)) ||
       (0 == MD5_Final(md5Digest, &md5Context)))
   {
      throw std::runtime_error("hash calculate");
   }

   std::vector<std::size_t> result;

   // below would work on little-endian only

   // make mask to trim indices to defined hash size
   size_t trimBitsMask = (1 << (8*_hashSize)) - 1;

   for (std::size_t i = 0; i < _setSize; i++)
   {
      unsigned char* start = md5Digest + i*_hashSize;
      size_t index = *reinterpret_cast<size_t*>(start) & trimBitsMask;
      result.push_back(index);
   }

   return result;
}

std::vector<std::size_t> HashSetCalculatorMD5::calculate(const std::string& str) const
{
   return calculate(str.c_str(), str.length());
}



