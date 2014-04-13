#pragma once

#include "IHashSetCalculator.hpp"
#include <openssl/md5.h>

class HashSetCalculatorMD5: public IHashSetCalculator
{
public:
   HashSetCalculatorMD5();
   ~HashSetCalculatorMD5();

   size_t getSetSize() const;
   size_t getHashSize() const;
   std::vector<ByteBuffer> calculate(const void* buffer, size_t size) const;
   ByteBuffer calculate(const ByteBuffer& ) const;
   ByteBuffer calculate(const std::string& ) const;

private:
   mutable MD5_CTX md5Context;
   mutable unsigned char md5Digest[MD5_DIGEST_LENGTH];
};
