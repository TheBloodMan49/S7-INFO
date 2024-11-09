#include "string.h"

namespace mystring {
    string::string(unsigned int size) {
        _data = new char[size];
        _physic_size = size;
    }

    string::string(char c) {
        _data = new char[2];
        _data[0] = c;
        _data[1] = '\0';
        _physic_size = 2;
    }

    string::string() // constructeur par défaut
    {
        _physic_size = 1;
        _data = new char[_physic_size];
        _data[0] = '\0';
    }

    string::string(const char *s) {
        unsigned int i = 0;
        for (i = 0; s[i] != '\0'; i++);
        _physic_size = i + 1;
        _data = new char[_physic_size];
        for (i = 0; s[i] != '\0'; i++) {
            _data[i] = s[i];
        }
    }

    string::string(const string &s) // constructeur par copie
    {
        _physic_size = s._physic_size;
        _data = new char[_physic_size];
        for (unsigned int i = 0; i < _physic_size; i++) {
            _data[i] = s._data[i];
        }
    }

    string::string(string &&s) noexcept // constructeur par déplacement
    {
        _physic_size = s._physic_size;
        _data = s._data;
        s._data = nullptr;
        s._physic_size = 0;
    }

    string::~string() {
        delete[] _data;
    }

    string string::operator+(const string &s) const {
        unsigned int size = _physic_size + s._physic_size - 1;
        string res(size);
        for (unsigned int i = 0; i < _physic_size - 1; i++) {
            res._data[i] = _data[i];
        }
        for (unsigned int i = 0; i < s._physic_size; i++) {
            res._data[i + _physic_size - 1] = s._data[i];
        }
        return res;
    }

    char string::operator[](unsigned int i) const {
        return _data[i];
    }

    char &string::operator[](unsigned int i) {
        return _data[i];
    }

    bool string::operator==(const string &s) const {
        if (this == &s) return true;
        if (_physic_size != s._physic_size) {
            return false;
        }

        unsigned int i = 0;
        for (i = 0; _data[i] != '\0'; i++) {
            if (_data[i] != s._data[i]) {
                return false;
            }
        }
        return true;
    }

    bool string::operator==(const char *s) const {
        unsigned int i = 0;
        for (i = 0; _data[i] != '\0' && s[i] != '\0'; i++) {
            if (_data[i] != s[i]) {
                return false;
            }
        }
        return s[i] == '\0';
    }

    string &string::operator=(const string &s) {
        if (this == &s) return *this;
        delete[] _data;
        _physic_size = s._physic_size;
        _data = new char[_physic_size];
        for (unsigned int i = 0; i < _physic_size; i++) {
            _data[i] = s._data[i];
        }
        return *this;
    }

    bool string::operator<(const string &s) const {
        unsigned int min_size = _physic_size < s._physic_size ? _physic_size : s._physic_size;
        unsigned int i = 0;
        for (i = 0; i < min_size; i++) {
            if (_data[i] < s._data[i]) {
                return true;
            } else if (_data[i] > s._data[i]) {
                return false;
            }
        }
        return _physic_size < s._physic_size;
    }

    bool string::operator>(const string &s) const {
        unsigned int min_size = _physic_size < s._physic_size ? _physic_size : s._physic_size;
        unsigned int i = 0;
        for (i = 0; i < min_size; i++) {
            if (_data[i] > s._data[i]) {
                return true;
            } else if (_data[i] < s._data[i]) {
                return false;
            }
        }
        return _physic_size > s._physic_size;
    }

    string &string::operator+=(const string &s) {
        unsigned int size = _physic_size + s._physic_size - 1;
        char *tmp = new char[size];
        for (unsigned int i = 0; i < _physic_size - 1; i++) {
            tmp[i] = _data[i];
        }
        for (unsigned int i = 0; i < s._physic_size; i++) {
            tmp[i + _physic_size - 1] = s._data[i];
        }
        delete[] _data;
        _data = tmp;
        _physic_size = size;
        return *this;
    }

    unsigned int string::find(const char *s) const {
        unsigned int i = 0;
        unsigned int j = 0;
        for (i = 0; i < _physic_size - 1; i++) {
            if (_data[i] == s[j]) {
                j++;
                if (s[j] == '\0') {
                    return i - j + 1;
                }
            } else {
                j = 0;
            }
        }
        return _physic_size;
    }

    string string::substr(unsigned int pos, unsigned int len) const {
        char *tmp = new char[len + 1];
        for (unsigned int i = 0; i < len; i++) {
            tmp[i] = _data[pos + i];
        }
        tmp[len] = '\0';
        return {tmp};
    }

    std::ostream &operator<<(std::ostream &os, const string &s) {
        for (unsigned int i = 0; i < s.size(); i++) {
            os << s._data[i];
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, string &s) {
        char c;
        s = "";
        is.get(c);
        while (c != '\n' && c != ' ' && c != EOF) {
            s += {c};
            is.get(c);
        }
        return is;
    }

}