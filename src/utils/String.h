#pragma once

#include <cstring>
#include <iostream>

namespace sba {
namespace utils {

/**
 * Example of string realization from Ctraustrup C++ book (head 11.12)
 *
 * class BasicString has value semantic. It is means that after assign (s1=s2)
 * changing s1 is not affected s2 also changing s2 is not affected s1.
 *
 * BasicString is simple realization of std::basic_string
 */
template <typename Char>
class BasicString {
public:
    class Range {};
    struct Srep;
    class Cref;

private:
    Srep *rep_;

public:
    BasicString();                    // x = "";
    BasicString(const char *);        // x = "abc";
    BasicString(const BasicString &); // x = other_string

    BasicString &operator=(const char *);
    BasicString &operator=(const BasicString &);
    BasicString &operator=(BasicString &&) = delete;

    BasicString &operator+=(const BasicString &);
    BasicString &operator+=(const char *);

    ~BasicString();

    friend std::ostream &operator<<(std::ostream &, const BasicString &);
    friend std::istream &operator>>(std::istream &, BasicString &);

    friend bool operator==(const BasicString &, const char *);
    friend bool operator==(const BasicString &, const BasicString &);

    friend bool operator!=(const BasicString &, const char *);
    friend bool operator!=(const BasicString &, const BasicString &);

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

template <typename Char>
BasicString<Char> operator+(const BasicString<Char> &,
                            const BasicString<Char> &);
template <typename Char>
BasicString<Char> operator+(const BasicString<Char> &, const char *);

/*
 * string representation share one string for several instances of String
 * with equals values.
 */
template <typename Char>
struct BasicString<Char>::Srep {
    Char *str;        // string
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

template <typename Char>
class BasicString<Char>::Cref {
    friend class BasicString;

private:
    BasicString &s_; // link to String value
    size_t i_;       // char index

    // public:
    Cref(BasicString &s, size_t i) : s_(s), i_(i) {}

public:
    /* conversion operator Cref to char */
    operator char() const { return s_.read(i_); }
    /* cref.operator=('a') */
    void operator=(char c) { s_.write(i_, c); }
};

template <typename Char>
inline void BasicString<Char>::check(size_t i) const {
    if (i < 0 || rep_->length <= i) {
        throw Range();
    }
}

template <typename Char>
inline void BasicString<Char>::write(size_t i, char c) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->str[i] = c;
}

template <typename Char>
inline char BasicString<Char>::read(size_t i) const {
    return rep_->str[i];
}

template <typename Char>
inline
    typename BasicString<Char>::Cref BasicString<Char>::operator[](size_t i) {
    return Cref(*this, i);
}

template <typename Char>
inline char BasicString<Char>::operator[](size_t i) const {
    return rep_->str[i];
}

template <typename Char>
inline size_t BasicString<Char>::size() const {
    return rep_->length;
}

template <typename Char>
inline size_t BasicString<Char>::get_request_count() const {
    return rep_->req_count;
}

// typedef BasicString<char> String;

} // namespace utils
} // namespace sba
