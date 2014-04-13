#pragma once

#include <vector>
#include <string>

typedef std::vector<unsigned char> ByteBuffer;


class IHashSetCalculator
{
public:
   virtual ~IHashSetCalculator() {}
   virtual size_t getSetSize() const = 0;
   virtual size_t getHashSize() const = 0;
   virtual std::vector<ByteBuffer> calculate(const void* buffer, size_t size) const = 0;
   virtual std::vector<ByteBuffer> calculate(const std::string& ) const = 0;
   //virtual ByteBuffer calculate(const ByteBuffer& ) const = 0;
};
