#if !defined(GADGET_QUERYSTRING_HPP)
#define GADGET_QUERYSTRING_HPP

#include <Arduino.h>

class QueryKeyValue {

public:
    String key;
    String value;

    QueryKeyValue() {
        key.reserve(32);
        value.reserve(64);
    }

    int parse(const String& query, int index) {
        if(query[index] == '?' || query[index] == '&') {
            index++;
            auto start = index;
            while(query[index] != '=') {
                index++;
            }
            key = query.substring(start, index);
            Serial.print("Key found: ");
            Serial.println(key);
            //
            index++;
            start = index;
            while(query[index] != '&' && query[index] != '\0') {
                index++;
            }
            Serial.print("Value found: ");
            Serial.println(value);
            value = query.substring(start, index);
            return index;
        }
        return -1;
    }

};

class QueryString{

public:
    int count;
    QueryKeyValue kvs[16];

    QueryString() = default;

    int parse(const String& query) {
        int index = 0;
        count = 0;
        for(size_t i = 0; i < 16; i++) {
            if((index = kvs[i].parse(query, index)) == -1) {
                break;
            }
            count++;
        }
        return count;
    }

};

#endif // GADGET_QUERYSTRING_HPP
