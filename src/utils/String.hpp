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
    class Range {};
    struct Srep;
    class Cref;

private:
    Srep *rep_;

public:
    String();               // x = "";
    String(const char *);   // x = "abc";
    String(const String &); // x = other_string

    String &operator=(const char *);
    String &operator=(const String &);
    String &operator=(String &&) = delete;

    String &operator+=(const String &);
    String &operator+=(const char*);

    ~String();

private:
    void check(size_t i) const;
    char read(size_t i) const;
    void write(size_t i, char c);

public:
    Cref operator[](size_t i);       // s.operator[i] === s[i]
    char operator[](size_t i) const; // s[i] where s is const object

    size_t size() const;
    size_t get_request_count() const; // get this value for debug or test
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
    void append(size_t len, const char *s);

    // private:
    Srep(const Srep &) = delete;
    Srep &operator=(const Srep &) = delete;
    Srep &operator=(const Srep &&) = delete;
};

class String::Cref {
    friend class String;

private:
    String &s_; // link to String value
    size_t i_;  // char index

    // public:
    Cref(String &s, size_t i) : s_(s), i_(i) {}

public:
    /* conversion operator Cref to char */
    operator char() const { return s_.read(i_); }
    /* cref.operator=('a') */
    void operator=(char c) { s_.write(i_, c); }
};

inline void String::check(size_t i) const {
    if (i < 0 || rep_->length <= i) {
        throw Range();
    }
}
inline void String::write(size_t i, char c) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->str[i] = c;
}
inline char String::read(size_t i) const { return rep_->str[i]; }
inline String::Cref String::operator[](size_t i) { return Cref(*this, i); }
inline char String::operator[](size_t i) const { return rep_->str[i]; }
inline size_t String::size() const { return rep_->length; }
inline size_t String::get_request_count() const { return rep_->req_count; }

} // namespace utils
} // namespace sba
