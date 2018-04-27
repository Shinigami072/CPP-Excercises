//
// Created by shinigami on 21/04/18.
//

#ifndef JIMP_EXERCISES_ZIPPERITERATOR_H
#define JIMP_EXERCISES_ZIPPERITERATOR_H

#include <IterableIterator.h>
#include <vector>
namespace utility {
    class ZipperIterator : public IterableIterator {
        const std::vector<int>::const_iterator left, left_end;
        const std::vector<std::string>::const_iterator right, right_end;
        size_t current;
    public:
        explicit ZipperIterator(std::vector<int>::const_iterator left,
                                std::vector<std::string>::const_iterator right,
                                std::vector<int>::const_iterator left_end,
                                std::vector<std::string>::const_iterator right_end);

        virtual std::pair<int, std::string> Dereference() const;

        virtual IterableIterator &Next();

        virtual bool NotEquals(const IterableIterator &other) const;


    };

}
#endif //JIMP_EXERCISES_ZIPPERITERATOR_H
