#pragma once

#include "IHashSetCalculator.hpp"
#include <openssl/md5.h>

class HashSetCalculatorMD5: public IHashSetCalculator
{
public:
   HashSetCalculatorMD5(size_t hashSize, size_t setSize);
   ~HashSetCalculatorMD5();

   size_t getSetSize() const;
   size_t getHashSize() const;
   std::vector<ByteBuffer> calculate(const void* buffer, size_t size) const;
   std::vector<ByteBuffer> calculate(const ByteBuffer& ) const;
   std::vector<ByteBuffer> calculate(const std::string& ) const;

private:
   size_t _hashSize;
   size_t _setSize;
};
