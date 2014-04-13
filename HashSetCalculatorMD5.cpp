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
   return 3;
}

std::size_t HashSetCalculatorMD5::getHashSize() const
{
   return 1;
}

std::vector<std::size_t> HashSetCalculatorMD5::calculate(const void* buffer, std::size_t size) const
{
   MD5_CTX md5Context;
   unsigned char md5Digest[MD5_DIGEST_LENGTH];
   size_t indices[MD5_DIGEST_LENGTH/sizeof(size_t)];

   if ((0 == MD5_Init(&md5Context)) ||
       (0 == MD5_Update(&md5Context, buffer, size)) ||
       (0 == MD5_Final(indices, &md5Context)))
   {
      throw std::runtime_error("hash calculate");
   }

   std::vector<std::size_t> result;

   size_t trimBits = 8*(sizeof(size_t)-_hashSize);

   for (std::size_t i = 0; i < _setSize; i++)
   {
      size_t index = indices[i] >> trimBits;
      result.push_back(index);
   }

   return result;
}

std::vector<std::size_t> HashSetCalculatorMD5::calculate(const std::string& str) const
{
   return calculate(str.c_str(), str.length());
}



