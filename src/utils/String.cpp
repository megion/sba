#include <utils/String.hpp>

namespace sba {
namespace utils {

typedef String::Srep Srep;

Srep::Srep(size_t len, const char *s) : length(len), req_count(1) {
    str = new char[length + 1]; // +1 for 0 ending
    std::strcpy(str, s);
}

Srep::~Srep() { delete[] str; }

Srep *Srep::get_own_copy() {
    if (req_count == 1) {
        return this;
    }
    req_count--;
    return new Srep(length, str);
}

void Srep::assign(size_t len, const char *s) {
    if (length != len) {
        delete[] str;
        length = len;
        str = new char[length + 1];
    }
    std::strcpy(str, s);
}

void Srep::append(size_t len, const char *s) {
    size_t new_len = length + len;
    char *new_str = new char[new_len + 1];

    std::strncpy(new_str, str, length);
    std::strncpy(new_str + length, s, len);
    delete[] str;
    str = new_str;
    length = new_len;
}

/**
 * default value is empty string
 */
String::String() { rep_ = new Srep(0, ""); }

String::String(const char *s) { rep_ = new Srep(std::strlen(s), s); }

String::String(const String &x) {
    x.rep_->req_count++;
    rep_ = x.rep_; // shared representation
}

String &String::operator=(const char *s) {
    if (rep_->req_count == 1) {
        rep_->assign(std::strlen(s), s);
    } else {
        rep_->req_count--;
        rep_ = new Srep(std::strlen(s), s);
    }
    return *this;
}

String &String::operator=(const String &x) {
    x.rep_->req_count++; // protection st=st
    if (--rep_->req_count == 0) {
        delete rep_;
    }
    rep_ = x.rep_;
    return *this;
}

String &String::operator+=(const String &x) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->append(x.rep_->length, x.rep_->str);
    return *this;
}

String &String::operator+=(const char *s) {
    rep_ = rep_->get_own_copy(); // copy on write
    rep_->append(std::strlen(s), s);
    return *this;
}

String operator+(const String &a, const String &b) {
    String r = a;
    return r += b;
}

String operator+(const String &a, const char *b) {
    String r = a;
    return r += b;
}

String::~String() {
    if (--rep_->req_count == 0) {
        delete rep_;
        rep_ = nullptr;
    }
}

} // namespace utils
} // namespace sba
