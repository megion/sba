/**
 * Example of string realization from Ctraustrup C++ book (head 11.12)
 *
 * class BasicString has value semantic. It is means that after assign (s1=s2)
 * changing s1 is not affected s2 also changing s2 is not affected s1.
 *
 * BasicString is simple realization of std::basic_string
 */
#pragma once

#include <cstring>
#include <iostream>

namespace sba {
namespace utils {

template <typename Char>
class BasicString; // forward declare to make function declaration possible

template <typename Char>
std::ostream &operator<<(std::ostream &, const BasicString<Char> &);

template <typename Char>
std::istream &operator>>(std::istream &, BasicString<Char> &);

template <typename Char>
bool operator==(const BasicString<Char> &, const Char *);

template <typename Char>
bool operator==(const BasicString<Char> &, const BasicString<Char> &);

template <typename Char>
bool operator!=(const BasicString<Char> &, const Char *);

template <typename Char>
bool operator!=(const BasicString<Char> &, const BasicString<Char> &);

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
    BasicString(const Char *);        // x = "abc";
    BasicString(const BasicString &); // x = other_string

    BasicString &operator=(const Char *);
    BasicString &operator=(const BasicString &);
    BasicString &operator=(BasicString &&) = delete;

    BasicString &operator+=(const BasicString &);
    BasicString &operator+=(const Char *);

    ~BasicString();

    // refers to a full specialization for this particular T
    // one-to-one relationship with class BasicString
    friend std::ostream &operator<<<>(std::ostream &, const BasicString &);
    friend std::istream &operator>><>(std::istream &, BasicString &);

    friend bool operator==<>(const BasicString &, const Char *);
    friend bool operator==<>(const BasicString &, const BasicString &);
    friend bool operator!=<>(const BasicString &, const Char *);
    friend bool operator!=<>(const BasicString &, const BasicString &);

private:
    void check(size_t i) const;
    Char read(size_t i) const;
    void write(size_t i, Char c);

public:
    Cref operator[](size_t i);       // s.operator[i] === s[i] => s[i] = 'a'
    Char operator[](size_t i) const; // s[i] where s is const object

    size_t size() const;
    size_t get_request_count() const; // get this value for debug or test
};

/*
 * string representation share one string for several instances of String
 * with equals values.
 */
template <typename Char>
struct BasicString<Char>::Srep {
    Char *str;        // string
    size_t length;    // string size
    size_t req_count; // string request count

    Srep(size_t len, const Char *s);

    ~Srep();

    Srep() = delete;

    /*
     * create copy if it need
     */
    Srep *get_own_copy();

    void assign(size_t len, const Char *s);
    void append(size_t len, const Char *s);

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
    operator Char() const { return s_.read(i_); }
    /* cref.operator=('a') */
    void operator=(Char c) { s_.write(i_, c); }
};

template <typename Char>
inline void BasicString<Char>::check(size_t i) const {
    if (i < 0 || rep_->length <= i) {
        throw Range();
    }
}

template <typename Char>
inline void BasicString<Char>::write(size_t i, Char c) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->str[i] = c;
}

template <typename Char>
inline Char BasicString<Char>::read(size_t i) const {
    return rep_->str[i];
}

template <typename Char>
inline
    typename BasicString<Char>::Cref BasicString<Char>::operator[](size_t i) {
    return Cref(*this, i);
}

template <typename Char>
inline Char BasicString<Char>::operator[](size_t i) const {
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

template <typename Char>
BasicString<Char>::Srep::Srep(size_t len, const Char *s)
    : length(len), req_count(1) {
    str = new Char[length + 1]; // +1 for 0 ending
    std::strcpy(str, s);
}

template <typename Char>
BasicString<Char>::Srep::~Srep() {
    delete[] str;
}

template <typename Char>
typename BasicString<Char>::Srep *BasicString<Char>::Srep::get_own_copy() {
    if (req_count == 1) {
        return this;
    }
    req_count--;
    return new Srep(length, str);
}

template <typename Char>
void BasicString<Char>::Srep::assign(size_t len, const Char *s) {
    if (length != len) {
        delete[] str;
        length = len;
        str = new Char[length + 1];
    }
    std::strcpy(str, s);
}

template <typename Char>
void BasicString<Char>::Srep::append(size_t len, const Char *s) {
    size_t new_len = length + len;
    Char *new_str = new Char[new_len + 1];

    std::strncpy(new_str, str, length);
    std::strncpy(new_str + length, s, len);
    delete[] str;
    str = new_str;
    length = new_len;
}

/**
 * default value is empty string
 */
template <typename Char>
BasicString<Char>::BasicString() {
    rep_ = new Srep(0, "");
}

template <typename Char>
BasicString<Char>::BasicString(const Char *s) {
    rep_ = new Srep(std::strlen(s), s);
}

template <typename Char>
BasicString<Char>::BasicString(const BasicString &x) {
    x.rep_->req_count++;
    rep_ = x.rep_; // shared representation
}

template <typename Char>
BasicString<Char> &BasicString<Char>::operator=(const Char *s) {
    if (rep_->req_count == 1) {
        rep_->assign(std::strlen(s), s);
    } else {
        rep_->req_count--;
        rep_ = new Srep(std::strlen(s), s);
    }
    return *this;
}

template <typename Char>
BasicString<Char> &BasicString<Char>::operator=(const BasicString &x) {
    x.rep_->req_count++; // protection st=st
    if (--rep_->req_count == 0) {
        delete rep_;
    }
    rep_ = x.rep_;
    return *this;
}

template <typename Char>
BasicString<Char> &BasicString<Char>::operator+=(const BasicString &x) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->append(x.rep_->length, x.rep_->str);
    return *this;
}

template <typename Char>
BasicString<Char> &BasicString<Char>::operator+=(const Char *s) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->append(std::strlen(s), s);
    return *this;
}

template <typename Char>
BasicString<Char> operator+(const BasicString<Char> &a,
                            const BasicString<Char> &b) {
    BasicString<Char> r = a;
    return r += b;
}

template <typename Char>
BasicString<Char> operator+(const BasicString<Char> &a, const Char *b) {
    BasicString<Char> r = a;
    return r += b;
}

template <typename Char>
std::ostream &operator<<(std::ostream &os, const BasicString<Char> &s) {
    os << s.rep_->str;
    return os;
}

template <typename Char>
std::istream &operator>>(std::istream &is, BasicString<Char> &s) {
    is >> s.rep_->str;
    return is;
}

template <typename Char>
bool operator==(const BasicString<Char> &x, const Char *s) {
    return std::strcmp(x.rep_->str, s) == 0;
}

template <typename Char>
bool operator==(const BasicString<Char> &x, const BasicString<Char> &y) {
    return std::strcmp(x.rep_->str, y.rep_->str) == 0;
}

template <typename Char>
bool operator!=(const BasicString<Char> &x, const Char *s) {
    return std::strcmp(x.rep_->str, s) != 0;
}

template <typename Char>
bool operator!=(const BasicString<Char> &x, const BasicString<Char> &y) {
    return std::strcmp(x.rep_->str, y.rep_->str) != 0;
}

template <typename Char>
BasicString<Char>::~BasicString() {
    if (--rep_->req_count == 0) {
        delete rep_;
        rep_ = nullptr;
    }
}

/*
 * define String type
 */
typedef BasicString<char> String;

} // namespace utils
} // namespace sba
