#pragma once

#include <openssl/md5.h>
#include "BloomFilter.hpp"

class HashSetCalculatorMD5: public BloomFilter::IHashSetCalculator
{
public:
   HashSetCalculatorMD5(std::size_t hashSize, std::size_t setSize);
   ~HashSetCalculatorMD5();

   std::size_t getSetSize() const;
   std::size_t getHashSize() const;
   std::vector<std::size_t> calculate(const void* buffer, std::size_t size) const;
   std::vector<std::size_t> calculate(const std::string& ) const;

private:
   std::size_t _hashSize;
   std::size_t _setSize;
};
