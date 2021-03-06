#include <stdexcept>
#include <limits>
#include <climits>
#include "HashSetCalculatorMD5.hpp"

using namespace std;

HashSetCalculatorMD5::HashSetCalculatorMD5(size_t hashSize, size_t setSize)
   : _hashSize(hashSize)
   , _maxHashValue((1ULL << (CHAR_BIT*_hashSize)) - 1)
   , _setSize(setSize)
{
   if ((0 == _hashSize) ||
       (0 == _maxHashValue) ||
       (0 == _setSize) ||
       (_hashSize >= sizeof(size_t)) ||
       (_hashSize * _setSize > MD5_DIGEST_LENGTH))
   {
      throw logic_error("Bad hash parameters");
   }
}

HashSetCalculatorMD5::~HashSetCalculatorMD5()
{
   // nothing to do
}

size_t HashSetCalculatorMD5::getSetSize() const
{
   return _setSize;
}

size_t HashSetCalculatorMD5::getHashSize() const
{
   return _hashSize;
}

size_t HashSetCalculatorMD5::getMaxHashValue() const
{
   return _maxHashValue;
}

vector<size_t> HashSetCalculatorMD5::calculate(const void* buffer, size_t size) const
{
   MD5_CTX md5Context;

   unsigned char md5Digest[MD5_DIGEST_LENGTH];

   if ((0 == MD5_Init(&md5Context)) ||
       (0 == MD5_Update(&md5Context, buffer, size)) ||
       (0 == MD5_Final(md5Digest, &md5Context)))
   {
      throw runtime_error("hash calculate");
   }

   vector<size_t> result;

   // little-endian only

   unsigned char* start = md5Digest;
   for (size_t i = 0; i < _setSize; i++)
   {
      size_t index = *reinterpret_cast<size_t*>(start) & _maxHashValue;
      result.push_back(index);
      start += _hashSize;
   }

   return result;
}

vector<size_t> HashSetCalculatorMD5::calculate(const string& str) const
{
   return calculate(str.c_str(), str.length());
}



