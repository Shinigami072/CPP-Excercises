//
// Created by shinigami on 21/04/18.
//

#ifndef JIMP_EXERCISES_ITERABLEITERATOR_H
#define JIMP_EXERCISES_ITERABLEITERATOR_H
#include <string>
#include <memory>
namespace utility {

    class IterableIterator {
    public:
        virtual ~IterableIterator() = default;

        virtual std::pair<int, std::string> Dereference() const =0;

        virtual IterableIterator &Next()=0;

        virtual bool NotEquals(const IterableIterator &other) const =0;

    };
}


#endif //JIMP_EXERCISES_ITERABLEITERATOR_H
