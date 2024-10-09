#ifndef TP03_ENSEMBLE_H
#define TP03_ENSEMBLE_H

#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

namespace implementation2 {
  template<class T>
  class Ensemble;
}

namespace implementation1 {

  template<class T>
  class Ensemble {
  private:
    std::set<T> elements;
  public:
    Ensemble() = default;
    explicit inline Ensemble(unsigned int size) : elements(size) {}
    inline Ensemble(const T* tab, size_t size) : elements(tab, tab + size) {}
    explicit inline Ensemble(const std::vector<T>& vec) : elements(vec.begin(), vec.end()) {}

    inline Ensemble(const Ensemble& e) : elements(e.elements) {}
    explicit inline Ensemble(const implementation2::Ensemble<T>& e) : elements(e.elements.begin(), e.elements.end()) {}

    inline void clear() { elements.clear(); }
    inline void add(const T& e) { elements.insert(e); }

    Ensemble<T> operator+(const Ensemble& e) const {
      Ensemble<T> res;
      std::set_union(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                     std::inserter(res.elements, res.elements.begin()));
      return res;
    }

    Ensemble<T> operator-(const Ensemble& e) const {
      Ensemble<T> res;
      std::set_difference(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                          std::inserter(res.elements, res.elements.begin()));
      return res;
    }

    Ensemble<T> operator*(const Ensemble& e) const {
      Ensemble<T> res;
      std::set_intersection(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                            std::inserter(res.elements, res.elements.begin()));
      return res;
    }

    Ensemble<T> operator/(const Ensemble& e) const {
      Ensemble<T> res;
      std::set_symmetric_difference(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                                    std::inserter(res.elements, res.elements.begin()));
      return res;
    }

    bool operator==(const Ensemble& e) const {
      return elements == e.elements;
    }

    friend std::istream& operator>>(std::istream& is, Ensemble<T>& e) {
      T elem;
      while (is >> elem) {
        e.add(elem);
      }
      return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ensemble<T>& e) {
      for (const auto& elem : e.elements) {
        os << elem << " ";
      }
      return os;
    }

    bool operator==(const implementation2::Ensemble<T>& e) const {
      return elements == std::set(e.elements.begin(), e.elements.end());
    }

    friend class implementation2::Ensemble<T>;
  };

} // implementation1

namespace implementation2 {

    template<class T>
    class Ensemble {
    private:
      std::unordered_set<T> elements;
    public:
      Ensemble() = default;
      explicit inline Ensemble(unsigned int size) : elements(size) {}
      inline Ensemble(const T* tab, size_t size) : elements(tab, tab + size) {}
      explicit inline Ensemble(const std::vector<T>& vec) : elements(vec.begin(), vec.end()) {}

      inline Ensemble(const Ensemble& e) : elements(e.elements) {}
      explicit inline Ensemble(const implementation1::Ensemble<T>& e) : elements(e.elements.begin(), e.elements.end()) {}

      inline void clear() { elements.clear(); }
      inline void add(const T& e) { elements.insert(e); }

      Ensemble<T> operator+(const Ensemble& e) const {
        Ensemble<T> res;
        std::set_union(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                       std::inserter(res.elements, res.elements.begin()));
        return res;
      }

      Ensemble<T> operator-(const Ensemble& e) const {
        Ensemble<T> res;
        std::set_difference(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                            std::inserter(res.elements, res.elements.begin()));
        return res;
      }

      Ensemble<T> operator*(const Ensemble& e) const {
        Ensemble<T> res;
        std::set_intersection(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                              std::inserter(res.elements, res.elements.begin()));
        return res;
      }

      Ensemble<T> operator/(const Ensemble& e) const {
        Ensemble<T> res;
        std::set_symmetric_difference(elements.begin(), elements.end(), e.elements.begin(), e.elements.end(),
                                      std::inserter(res.elements, res.elements.begin()));
        return res;
      }

      bool operator==(const Ensemble& e) const {
        return elements == e.elements;
      }

      friend std::istream& operator>>(std::istream& is, Ensemble<T>& e) {
        T elem;
        while (is >> elem) {
          e.add(elem);
        }
        return is;
      }

      friend std::ostream& operator<<(std::ostream& os, const Ensemble<T>& e) {
        for (const auto& elem : e.elements) {
          os << elem << " ";
        }
        return os;
      }

      bool operator==(const implementation1::Ensemble<T>& e) const {
        return std::set(elements.begin(), elements.end()) == e.elements;
      }

      friend class implementation1::Ensemble<T>;
    };

} // implementation2


#endif //TP03_ENSEMBLE_H
