#include <stdexcept>
#include "HashSetCalculatorMD5.hpp"

HashSetCalculatorMD5::HashSetCalculatorMD5(std::size_t hashSize, std::size_t setSize)
   : _hashSize(hashSize)
   , _setSize(setSize)
{
   if ((_hashSize > sizeof(size_t)) ||
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
   return 3;
}

std::size_t HashSetCalculatorMD5::getHashSize() const
{
   return 1;
}

std::vector<ByteBuffer> HashSetCalculatorMD5::calculate(const void* buffer, std::size_t size) const
{
   MD5_CTX md5Context;
   unsigned char md5Digest[MD5_DIGEST_LENGTH];

   if ((0 == MD5_Init(&md5Context)) ||
       (0 == MD5_Update(&md5Context, buffer, size)) ||
       (0 == MD5_Final(md5Digest, &md5Context)))
   {
      throw std::runtime_error("hash calculate");
   }

   std::vector<ByteBuffer> result;

   for (std::size_t i = 0; i < _setSize; i++)
   {
      unsigned char* start = md5Digest + i*_hashSize;
      unsigned char* end = start + _hashSize;
      result.push_back(ByteBuffer(start, end));
   }

   return result;
}

std::vector<ByteBuffer> HashSetCalculatorMD5::calculate(const ByteBuffer& ) const
{
}

std::vector<ByteBuffer> HashSetCalculatorMD5::calculate(const std::string& str) const
{
   return calculate(str.c_str(), str.length());
}



