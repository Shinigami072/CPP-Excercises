//
// Created by shinigami on 21/04/18.
//

#ifndef JIMP_EXERCISES_ITERABLEITERATORWRAPPER_H
#define JIMP_EXERCISES_ITERABLEITERATORWRAPPER_H

#include "IterableIterator.h"
#include <memory>
namespace utility {
    class IterableIteratorWrapper {
    public:
        explicit IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator):iter(move(iterator)) {}


            bool operator!=(const IterableIteratorWrapper &other) const{
            return iter->NotEquals(*other.iter);
        }

        std::pair<int, std::string> operator*() const{
            return iter->Dereference();
        };

        IterableIteratorWrapper &operator++(){
            iter->Next();
            return *this;
        }

    private:
        std::unique_ptr<IterableIterator> iter;
    };
}

#endif //JIMP_EXERCISES_ITERABLEITERATORWRAPPER_H
