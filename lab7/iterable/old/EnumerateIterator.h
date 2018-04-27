//
// Created by shinigami on 21/04/18.
//

#ifndef JIMP_EXERCISES_ENUMERATEITERATOR_H
#define JIMP_EXERCISES_ENUMERATEITERATOR_H

#include <IterableIterator.h>
#include <vector>
namespace utility {
    class EnumerateIterator : public IterableIterator {
    public:
        EnumerateIterator(
                          std::vector<std::string>::const_iterator _left,
                          std::vector<std::string>::const_iterator _left_end) :
                IterableIterator(),
                left(_left),
                left_end(_left_end),
                current(0) {}

        std::pair<int, std::string> Dereference() const {
            return std::pair<int, std::string>(current, *(left + current));
        }

        IterableIterator &Next() {
            if ((left + current) != left_end)
                current++;
            return *this;
        }

        bool NotEquals(const IterableIterator &other) const {
            return current != static_cast<const EnumerateIterator &>(other).current;
        }

    private:
        const std::vector<std::string>::const_iterator left, left_end;
        size_t current;
    };
}

#endif //JIMP_EXERCISES_ENUMERATEITERATOR_H
