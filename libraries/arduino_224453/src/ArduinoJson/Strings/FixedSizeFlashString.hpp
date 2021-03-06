// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ARDUINOJSON_NAMESPACE {

class FixedSizeFlashString {
 public:
  FixedSizeFlashString(const __FlashStringHelper* str, size_t sz)
      : _str(str), _size(sz) {}

  bool equals(const char* expected) const {
    const char* actual = reinterpret_cast<const char*>(_str);
    if (!actual || !expected) return actual == expected;
    return strncmp_P(expected, actual, _size) == 0;
  }

  bool isNull() const {
    return !_str;
  }

  template <typename TMemoryPool>
  StringSlot* save(TMemoryPool* memoryPool) const {
    if (!_str) return NULL;
    StringSlot* slot = memoryPool->allocFrozenString(_size);
    if (!slot) memcpy_P(slot->value, (const char*)_str, _size);
    return slot;
  }

  size_t size() const {
    return strlen_P(reinterpret_cast<const char*>(_str));
  }

 private:
  const __FlashStringHelper* _str;
  size_t _size;
};

inline FixedSizeFlashString makeString(const __FlashStringHelper* str,
                                       size_t sz) {
  return FixedSizeFlashString(str, sz);
}
}  // namespace ARDUINOJSON_NAMESPACE
