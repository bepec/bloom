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

      // get the number of hashes calculated for each request
      virtual std::size_t getSetSize() const = 0;

      // get the size (in bytes) of each hash calculated
      virtual std::size_t getHashSize() const = 0;

      // get the max possible value of the hash
      virtual std::size_t getMaxHashValue() const = 0;

      // calculate the set of hashes for a given string
      virtual std::vector<std::size_t> calculate(const std::string& ) const = 0;
   };

   // pass the pre-configured calculator object
   BloomFilter(IHashSetCalculator& hashSetCalculator);

   // add the word to the filter dictionary
   void feed(const std::string& word);

   // check if the dictionary (possibly) contains the given word
   // false positive answer is possible due to a Bloom Filter nature
   bool has(const std::string& word) const;

private:
   const IHashSetCalculator& _hashSetCalculator;
   std::vector<bool> _filterMap;
};

