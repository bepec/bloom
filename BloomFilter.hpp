#pragma once

#include "IHashSetCalculator.hpp"

class BloomFilter
{
public:
   BloomFilter(IHashSetCalculator& hashSetCalculator);
   void feed(const std::string& word);
   bool has(const std::string& word) const;

private:
   std::vector<bool> _filterMap;
   const IHashSetCalculator& _hashSetCalculator;
};
