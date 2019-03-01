#pragma once

#include <iostream>
//#include <cstdio>
#include <cstring>

namespace sba {
namespace utils {

/**
 * Example of string realization from Ctraustrup C++ book (head 11.12)
 *
 * class String has value semantic. It is means that after assign (s1=s2)
 * changing s1 is not affected s2 also changing s2 is not affected s1.
 */
class String {
public:
    struct Srep;
    Srep *rep;

    class Cref;

    String();               // x = "";
    String(const char *);   // x = "abc";
    String(const String &); // x = other_string

    String &operator=(const char *);
    String &operator=(const String &);
    String &operator=(String &&) = delete;

    ~String();
};

/*
 * string representation share one string for several instances of String
 * with equals values.
 */
struct String::Srep {
    char *str;        // string
    size_t length;    // string size
    size_t req_count; // string request count

    Srep(size_t len, const char *s);

    ~Srep();

    Srep() = delete;

    /*
     * create copy if it need
     */
    Srep *get_own_copy();

    void assign(size_t len, const char *s);

    // private:
    Srep(const Srep &) = delete;
    Srep &operator=(const Srep &) = delete;
    Srep &operator=(const Srep &&) = delete;
};

} // namespace utils
} // namespace sba
