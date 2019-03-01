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

/**
 * default value is empty string
 */
String::String() { rep = new Srep(0, ""); }

String::String(const char *s) { rep = new Srep(std::strlen(s), s); }

String::String(const String &x) {
    x.rep->req_count++;
    rep = x.rep; // shared representation (call assign operator)
}

String &String::operator=(const char *s) {
    if (rep->req_count == 1) {
        rep->assign(std::strlen(s), s);
    } else {
        rep->req_count--;
        rep = new Srep(std::strlen(s), s);
    }
    return *this;
}

String &String::operator=(const String &x) {
    x.rep->req_count++; // protection st=st
    if (--rep->req_count == 0) {
        delete rep;
    }
    rep = x.rep;
    return *this;
}

String::~String() {
    if (--rep->req_count == 0) {
        delete rep;
    }
}

} // namespace utils
} // namespace sba
