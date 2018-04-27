//
// Created by shinigami on 22/04/18.
//

#ifndef JIMP_EXERCISES_PRODUCTITERATOR_H
#define JIMP_EXERCISES_PRODUCTITERATOR_H

#include <vector>
#include <string>
#include <IterableIterator.h>
namespace utility {
    class ProductIterator : public IterableIterator {
        const std::vector<int>::const_iterator left, left_end;
        const std::vector<std::string>::const_iterator right, right_end;
        size_t currentl;
        size_t currentr;

    public:
        explicit ProductIterator(std::vector<int>::const_iterator left,
                                std::vector<std::string>::const_iterator right,
                                std::vector<int>::const_iterator left_end,
                                std::vector<std::string>::const_iterator right_end);

        virtual std::pair<int, std::string> Dereference() const;

        virtual IterableIterator &Next();

        virtual bool NotEquals(const IterableIterator &other) const;
    };

}


#endif //JIMP_EXERCISES_PRODUCTITERATOR_H
