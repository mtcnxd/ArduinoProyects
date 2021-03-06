// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <string>

TEST_CASE("JsonObject::remove()") {
  DynamicJsonDocument doc;
  JsonObject obj = doc.to<JsonObject>();
  obj["a"] = 0;
  obj["b"] = 1;
  obj["c"] = 2;
  std::string result;

  SECTION("remove(key)") {
    SECTION("Remove first") {
      obj.remove("a");
      serializeJson(obj, result);
      REQUIRE("{\"b\":1,\"c\":2}" == result);
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(2));
    }

    SECTION("Remove middle") {
      obj.remove("b");
      serializeJson(obj, result);
      REQUIRE("{\"a\":0,\"c\":2}" == result);
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(2));
    }

    SECTION("Remove last") {
      obj.remove("c");
      serializeJson(obj, result);
      REQUIRE("{\"a\":0,\"b\":1}" == result);
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(2));
    }

    SECTION("Release value string memory") {
      obj["c"] = std::string("Copy me!");
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(3) + JSON_STRING_SIZE(9));

      obj.remove("c");
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(2));
    }

    SECTION("Release key string memory") {
      obj[std::string("Copy me!")] = 42;
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(4) + JSON_STRING_SIZE(9));

      obj.remove("Copy me!");

      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(3));
    }

    SECTION("Release raw string memory") {
      obj["c"] = serialized(std::string("Copy me!"));
      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(3) + JSON_STRING_SIZE(8));

      obj.remove("c");

      REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(2));
    }
  }

  SECTION("remove(iterator)") {
    JsonObject::iterator it = obj.begin();

    SECTION("Remove first") {
      obj.remove(it);
      serializeJson(obj, result);
      REQUIRE("{\"b\":1,\"c\":2}" == result);
    }

    SECTION("Remove middle") {
      ++it;
      obj.remove(it);
      serializeJson(obj, result);
      REQUIRE("{\"a\":0,\"c\":2}" == result);
    }

    SECTION("Remove last") {
      it += 2;
      obj.remove(it);
      serializeJson(obj, result);
      REQUIRE("{\"a\":0,\"b\":1}" == result);
    }
  }

#ifdef HAS_VARIABLE_LENGTH_ARRAY
  SECTION("key is a vla") {
    int i = 16;
    char vla[i];
    strcpy(vla, "b");
    obj.remove(vla);

    serializeJson(obj, result);
    REQUIRE("{\"a\":0,\"c\":2}" == result);
  }
#endif
}
