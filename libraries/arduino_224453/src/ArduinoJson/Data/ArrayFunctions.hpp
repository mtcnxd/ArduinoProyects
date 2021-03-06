// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonVariantData.hpp"
#include "SlotFunctions.hpp"

namespace ARDUINOJSON_NAMESPACE {

inline JsonVariantData* arrayAdd(JsonArrayData* arr, MemoryPool* pool) {
  if (!arr) return 0;

  VariantSlot* slot = pool->allocVariant();
  if (!slot) return 0;

  slot->next = 0;
  slot->value.type = JSON_NULL;

  if (arr->tail) {
    slot->prev = arr->tail;
    arr->tail->next = slot;
    arr->tail = slot;
  } else {
    slot->prev = 0;
    arr->head = slot;
    arr->tail = slot;
  }

  slot->value.keyIsOwned = false;
  return &slot->value;
}

inline VariantSlot* arrayGetSlot(const JsonArrayData* arr, size_t index) {
  if (!arr) return 0;
  return slotAdvance(arr->head, index);
}

inline JsonVariantData* arrayGet(const JsonArrayData* arr, size_t index) {
  VariantSlot* slot = arrayGetSlot(arr, index);
  return slot ? &slot->value : 0;
}

inline void arrayRemove(JsonArrayData* arr, VariantSlot* slot,
                        MemoryPool* pool) {
  if (!arr || !slot) return;

  if (slot->prev)
    slot->prev->next = slot->next;
  else
    arr->head = slot->next;
  if (slot->next)
    slot->next->prev = slot->prev;
  else
    arr->tail = slot->prev;

  slotFree(slot, pool);
}

inline void arrayRemove(JsonArrayData* arr, size_t index, MemoryPool* pool) {
  arrayRemove(arr, arrayGetSlot(arr, index), pool);
}

inline void arrayClear(JsonArrayData* arr) {
  if (!arr) return;
  arr->head = 0;
  arr->tail = 0;
}

bool variantCopy(JsonVariantData*, const JsonVariantData*, MemoryPool*);

inline bool arrayCopy(JsonArrayData* dst, const JsonArrayData* src,
                      MemoryPool* pool) {
  if (!dst || !src) return false;
  arrayClear(dst);
  for (VariantSlot* s = src->head; s; s = s->next) {
    if (!variantCopy(arrayAdd(dst, pool), &s->value, pool)) return false;
  }
  return true;
}

bool variantEquals(const JsonVariantData*, const JsonVariantData*);

inline bool arrayEquals(const JsonArrayData* a1, const JsonArrayData* a2) {
  if (a1 == a2) return true;
  if (!a1 || !a2) return false;
  VariantSlot* s1 = a1->head;
  VariantSlot* s2 = a2->head;
  for (;;) {
    if (s1 == s2) return true;
    if (!s1 || !s2) return false;
    if (!variantEquals(&s1->value, &s2->value)) return false;
    s1 = s1->next;
    s2 = s2->next;
  }
}

inline size_t arraySize(const JsonArrayData* arr) {
  if (!arr) return 0;
  return slotSize(arr->head);
}

inline void arrayFree(JsonArrayData* arr, MemoryPool* pool) {
  ARDUINOJSON_ASSERT(arr);

  VariantSlot* cur = arr->head;
  while (cur) {
    VariantSlot* next = cur->next;
    slotFree(cur, pool);
    cur = next;
  }
}
}  // namespace ARDUINOJSON_NAMESPACE
