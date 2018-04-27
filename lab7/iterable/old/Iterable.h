//
// Created by shinigami on 21/04/18.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H

#include "IterableIterator.h"
#include "ZipperIterator.h"
#include "IterableIteratorWrapper.h"
#include "EnumerateIterator.h"
#include <ProductIterator.h>
#include <vector>
namespace utility{
class Iterable{
protected:
    virtual std::unique_ptr<IterableIterator> ConstBegin()const=0;
    virtual std::unique_ptr<IterableIterator> ConstEnd() const=0;
public:
    const IterableIteratorWrapper cbegin() const{ return IterableIteratorWrapper(ConstBegin());}
    const IterableIteratorWrapper cend() const{ return IterableIteratorWrapper(ConstEnd());}
    IterableIteratorWrapper begin() const{ return IterableIteratorWrapper(ConstBegin());}
    IterableIteratorWrapper end() const{ return IterableIteratorWrapper(ConstEnd());}

};
class Zipper: public Iterable{
private:
    const std::vector<int> &left;
    const std::vector<std::string> &right;

public:
    Zipper(const std::vector<int> &v1,const std::vector<std::string> &v2):
            left(v1),
            right(v2){

    }
protected:
    virtual std::unique_ptr<IterableIterator> ConstBegin()const {return move(std::make_unique<ZipperIterator>(left.cbegin(),right.begin(),left.end(),right.end()));}
    virtual std::unique_ptr<IterableIterator> ConstEnd() const {return move(std::make_unique<ZipperIterator>(left.end(),right.end(),left.end(),right.end()));}

};
    class Product: public Iterable{
    private:
        const std::vector<int> &left;
        const std::vector<std::string> &right;

    public:
        Product(const std::vector<int> &v1,const std::vector<std::string> &v2):
                left(v1),
                right(v2){

        }
    protected:
        virtual std::unique_ptr<IterableIterator> ConstBegin()const {return move(std::make_unique<ProductIterator>(left.cbegin(),right.cbegin(),left.cend(),right.cend()));}
        virtual std::unique_ptr<IterableIterator> ConstEnd() const {return move(std::make_unique<ProductIterator>(left.cend(),right.cend(),left.cend(),right.cend()));}

    };
class Enumerate: public Iterable{
private:
    const std::vector<std::string> &left;

public:
    Enumerate(const std::vector<std::string> &v1):
            left(v1){

    }
protected:
    virtual std::unique_ptr<IterableIterator> ConstBegin()const {return move(std::make_unique<EnumerateIterator>(left.cbegin(),left.end()));}
    virtual std::unique_ptr<IterableIterator> ConstEnd() const {return move(std::make_unique<EnumerateIterator>(left.end(),left.end()));}

};

};
#endif //JIMP_EXERCISES_ITERABLE_H
