#pragma once

#include <vector>
#include <string>

class BloomFilter
{
public:

   class IHashSetCalculator
   {
   public:
      virtual ~IHashSetCalculator() {}
      virtual std::size_t getSetSize() const = 0;
      virtual std::size_t getHashSize() const = 0;
      virtual std::size_t getMaxHashValue() const = 0;
      virtual std::vector<std::size_t> calculate(const std::string& ) const = 0;
   };

   BloomFilter(IHashSetCalculator& hashSetCalculator);
   void feed(const std::string& word);
   bool has(const std::string& word) const;

private:
   const IHashSetCalculator& _hashSetCalculator;
   std::vector<bool> _filterMap;
};
