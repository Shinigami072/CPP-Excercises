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

        virtual std::pair<int, std::string> Dereference() const;

        virtual IterableIterator &Next();

        virtual bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const;
    };
    class IterableIteratorWrapper {
    public:
        IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator):iter(move(iterator)) {}



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

        virtual std::pair<int, std::string> Dereference() const;

        virtual IterableIterator &Next();

        virtual bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const;
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

        std::pair<int, std::string> Dereference() const {
            return std::pair<int, std::string>(current, *(left + current));
        }

        IterableIterator &Next() {
            if ((left + current) != left_end)
                current++;
            return *this;
        }

        bool NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
            return current != static_cast<const EnumerateIterator&>(*other).current;
            //auto tmp = static_cast<const EnumerateIterator &>(other);
            //return left+current != tmp.left + tmp.current;
        }

    private:
        const std::vector<std::string>::const_iterator left, left_end;
        size_t current;
    };
    class Iterable{
    protected:
        virtual std::unique_ptr<IterableIterator> ConstBegin()const=0;
        virtual std::unique_ptr<IterableIterator> ConstEnd() const=0;
    public:
        const IterableIteratorWrapper cbegin() const{ return IterableIteratorWrapper(move(ConstBegin()));}
        const IterableIteratorWrapper cend() const{ return IterableIteratorWrapper(move(ConstEnd()));}
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
        virtual std::unique_ptr<IterableIterator> ConstBegin()const
        {return move(std::make_unique<ZipperIterator>(left.cbegin(),right.begin(),left.end(),right.end()));}
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
        virtual std::unique_ptr<IterableIterator> ConstBegin()const
        {return move(std::make_unique<ProductIterator>(left.cbegin(),right.cbegin(),left.cend(),right.cend()));}
        virtual std::unique_ptr<IterableIterator> ConstEnd() const
        {return move(std::make_unique<ProductIterator>(left.cend(),right.cend(),left.cend(),right.cend()));}

    };
    class Enumerate: public Iterable{
    private:
        const std::vector<std::string> &left;

    public:
        Enumerate(std::vector<std::string> &v1):
                left(v1){

        }
    protected:
        virtual std::unique_ptr<IterableIterator> ConstBegin()const
        {return move(std::make_unique<EnumerateIterator>(left.cbegin(),left.end()));}
        virtual std::unique_ptr<IterableIterator> ConstEnd() const
        {return move(std::make_unique<EnumerateIterator>(left.end(),left.end()));}

    };
    /*class EnumerateIterator : public IterableIterator {
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
            //auto tmp = static_cast<const EnumerateIterator &>(other);
            //return left+current != tmp.left + tmp.current;
        }

    private:
        const std::vector<std::string>::const_iterator left, left_end;
        size_t current;
    }; */
}
#endif //JIMP_EXERCISES_ITERABLE_H