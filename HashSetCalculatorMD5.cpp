#include <stdexcept>
#include "HashSetCalculatorMD5.hpp"

HashSetCalculatorMD5::HashSetCalculatorMD5()
{
   //
}

HashSetCalculatorMD5::~HashSetCalculatorMD5()
{
   // nothing to do
}

size_t HashSetCalculatorMD5::getSetSize() const
{
   return 3;
}

size_t HashSetCalculatorMD5::getHashSize() const
{
   return 1;
}

std::vector<ByteBuffer> HashSetCalculatorMD5::calculate(const void* buffer, size_t size) const
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

   result.push_back(ByteBuffer(md5Digest, md5Digest+1));
   result.push_back(ByteBuffer(md5Digest+1, md5Digest+2));
   result.push_back(ByteBuffer(md5Digest+2, md5Digest+3));

   return result;
}

std::vector<ByteBuffer> HashSetCalculatorMD5::calculate(const ByteBuffer& ) const
{
}

std::vector<ByteBuffer> HashSetCalculatorMD5::calculate(const std::string& str) const
{
   return calculate(str.c_str(), str.length());
}



