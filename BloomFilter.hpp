#pragma once

#include "IHashSetCalculator.hpp"

class BloomFilter
{
public:
   BloomFilter(IHashSetCalculator& );
   void feed(const std::string& word);
   bool has(const std::string& word) const;

private:
   std::vector<unsigned char> filterMap;
   const IHashSetCalculator& hashSetCalculator;
};
