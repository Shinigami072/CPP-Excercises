//
// Created by Joanna on 25.04.2018.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H

#include <iostream>
#include <vector>
#include <memory>
using namespace std;


namespace utility {

    class IterableIterator {
    public:
        virtual ~IterableIterator() = default;

        virtual std::pair<int, std::string> Dereference() const =0;

        virtual IterableIterator &Next()=0;

        virtual bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const = 0;


    };

    class IterableIteratorWrapper {
    public:
        explicit IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator) {iter = move(iterator);}



        bool operator!=(const IterableIteratorWrapper &other) const {
            return iter->NotEquals(other.iter);
        }

        std::pair<int, std::string> operator*() const{
            return iter->Dereference();
        };

        IterableIteratorWrapper &operator++(){
            this->iter->Next();
            return *this;
        }

    private:
        std::unique_ptr<IterableIterator> iter;
    };
    class ZipperIterator : public IterableIterator {
    private:
        std::vector<int>::const_iterator left, left_end;
        std::vector<std::string>::const_iterator right, right_end;
        size_t current;
    public:
        explicit ZipperIterator(const std::vector<int>::const_iterator& left,
                                const std::vector<std::string>::const_iterator& right,
                                const std::vector<int>::const_iterator& left_end,
                                const std::vector<std::string>::const_iterator& right_end);

        std::pair<int, std::string> Dereference() const override;

        IterableIterator &Next() override;

        bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const override;
    };


    class ProductIterator : public IterableIterator {
        const std::vector<int>::const_iterator left, left_end;
        const std::vector<std::string>::const_iterator right, right_end;
        size_t currentl;
        size_t currentr;

    public:
        ProductIterator(const std::vector<int>::const_iterator& left,
                        const std::vector<std::string>::const_iterator& right,
                        const std::vector<int>::const_iterator& left_end,
                        const std::vector<std::string>::const_iterator& right_end);

        std::pair<int, std::string> Dereference() const override;

        IterableIterator &Next() override;

        bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const override;
    };
    class EnumerateIterator : public IterableIterator {
    public:
        EnumerateIterator(
                const std::vector<std::string>::const_iterator& _left,
                const std::vector<std::string>::const_iterator& _left_end) :
                IterableIterator(),
                left(_left),
                left_end(_left_end),
                current(0) {}

        std::pair<int, std::string> Dereference() const override{
            return std::pair<int, std::string>(current+1, *(left + current));
        }

        IterableIterator &Next() override {
            if ((left + current) != left_end)
                current++;
            return *this;
        }

        bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const override{
            auto tmp = dynamic_cast<const EnumerateIterator&>(*other);
            return left+current != tmp.left + tmp.current;
        }

    private:
        const std::vector<std::string>::const_iterator left, left_end;
        int current;
    };
    class Iterable{
    protected:
        virtual std::unique_ptr<IterableIterator> ConstBegin()const=0;
        virtual std::unique_ptr<IterableIterator> ConstEnd() const=0;
    public:
        IterableIteratorWrapper cbegin() const{ return IterableIteratorWrapper(move(ConstBegin()));}
        IterableIteratorWrapper cend() const{ return IterableIteratorWrapper(move(ConstEnd()));}
        IterableIteratorWrapper begin() const{ return cbegin();}
        IterableIteratorWrapper end() const{  return cend();}

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
        std::unique_ptr<IterableIterator> ConstBegin()  const override
        {return move(std::make_unique<ZipperIterator>(left.cbegin(),right.begin(),left.end(),right.end()));}
        std::unique_ptr<IterableIterator> ConstEnd() const override {return move(std::make_unique<ZipperIterator>(left.end(),right.end(),left.end(),right.end()));}

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
        std::unique_ptr<IterableIterator> ConstBegin()const override
        {return move(std::make_unique<ProductIterator>(left.cbegin(),right.cbegin(),left.cend(),right.cend()));}
        std::unique_ptr<IterableIterator> ConstEnd() const override
        {return move(std::make_unique<ProductIterator>(left.cend(),right.cend(),left.cend(),right.cend()));}

    };
    class Enumerate: public Iterable{
    private:
        const std::vector<std::string> &left;

    public:
        explicit Enumerate(std::vector<std::string> &v1):
                left(v1){

        }
    protected:
        std::unique_ptr<IterableIterator> ConstBegin()const override
        {return move(std::make_unique<EnumerateIterator>(left.cbegin(),left.end()));}
        std::unique_ptr<IterableIterator> ConstEnd() const override
        {return move(std::make_unique<EnumerateIterator>(left.end(),left.end()));}

    };
}
#endif //JIMP_EXERCISES_ITERABLE_H