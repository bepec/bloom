#pragma once

class BloomFilter
{
public:

   class IHashSetCalculator
   {
   public:
      virtual ~IHashSetCalculator() {}
      virtual size_t getSetSize() const = 0;
      virtual size_t getHashSize() const = 0;
      virtual std::vector<size_t> calculate(const std::string& ) const = 0;
   };

   BloomFilter(IHashSetCalculator& hashSetCalculator);
   void feed(const std::string& word);
   bool has(const std::string& word) const;

private:
   std::vector<bool> _filterMap;
   const IHashSetCalculator& _hashSetCalculator;
};
