//
// Created by Kuba on 23-04-18.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H


#include <string>
#include <vector>
#include <memory>

namespace utility
{


    class IterableIterator
    {
    public:
        IterableIterator()=default;
        ~IterableIterator()=default;
        IterableIterator(const IterableIterator& ii);
        IterableIterator & operator=(const IterableIterator& ii);
        virtual std::pair<int, std::string> Dereference() const =0;
        virtual IterableIterator &Next()=0;
        virtual bool NotEquals(const std::unique_ptr<IterableIterator> &other) const =0;
        std::vector<int>::const_iterator left_begin_;
        std::vector<std::string>::const_iterator right_begin_;
        std::vector<int>::const_iterator left_;
        std::vector<std::string>::const_iterator right_;
        std::vector<int>::const_iterator left_end_;
        std::vector<std::string>::const_iterator right_end_;
    };

    class ZipperIterator : public IterableIterator
    {
    public:
        ZipperIterator()=default;
        explicit ZipperIterator(std::vector<int>::const_iterator left, std::vector<std::string>::const_iterator right,
                                std::vector<int>::const_iterator left_end, std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override ;
        IterableIterator &Next() override ;
        bool NotEquals(const std::unique_ptr<IterableIterator> &other) const override ;
    };

    class EnumerateIterator : public IterableIterator
    {
    public:
        EnumerateIterator()=default;
        explicit EnumerateIterator(std::vector<std::string>::const_iterator right, std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override ;
        IterableIterator &Next() override ;
        bool NotEquals(const std::unique_ptr<IterableIterator> &other) const override ;

    };

    class ProductIterator : public IterableIterator
    {
    public:
        ProductIterator()=default;
        explicit ProductIterator(std::vector<int>::const_iterator left, std::vector<std::string>::const_iterator right,
                                 std::vector<int>::const_iterator left_end, std::vector<std::string>::const_iterator right_end);
        std::pair<int, std::string> Dereference() const override ;
        IterableIterator &Next() override ;
        bool NotEquals(const std::unique_ptr<IterableIterator> &other) const override ;

    };

    //==================================================================================================================

    class IterableIteratorWrapper
    {
    public:
        IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator);
        bool operator!=(const IterableIteratorWrapper &other);
        std::pair<int, std::string> operator*();
        IterableIteratorWrapper &operator++();
        std::unique_ptr<IterableIterator> iter_;
    };

    class Iterable
    {
    public:
        virtual std::unique_ptr<IterableIterator> ConstBegin() const =0;
        virtual std::unique_ptr<IterableIterator> ConstEnd() const =0;
        IterableIteratorWrapper cbegin() const;
        IterableIteratorWrapper cend() const;
        IterableIteratorWrapper begin() const;
        IterableIteratorWrapper end() const;

    };

    class Zipper : public Iterable
    {
    public:
        Zipper(std::vector<int> &vi, std::vector<std::string> &vs);

        std::unique_ptr<IterableIterator> ConstBegin() const override ;
        std::unique_ptr<IterableIterator> ConstEnd() const override;

    private:
        std::unique_ptr<std::vector<int>> vi_;
        std::unique_ptr<std::vector<std::string>> vs_;
        ZipperIterator zipit_;
    };

    class Enumerate : public Iterable
    {
    public:
        Enumerate(std::vector<std::string> vs);

        std::unique_ptr<IterableIterator> ConstBegin() const override ;
        std::unique_ptr<IterableIterator> ConstEnd() const override;
    private:
        std::unique_ptr<std::vector<std::string>> vs_;
        EnumerateIterator enumit_;
    };

    class Product : public Iterable
    {
    public:
        Product(std::vector<int> vi, std::vector<std::string> vs);

        std::unique_ptr<IterableIterator> ConstBegin() const override ;
        std::unique_ptr<IterableIterator> ConstEnd() const override;
    private:
        std::unique_ptr<std::vector<int>> vi_;
        std::unique_ptr<std::vector<std::string>> vs_;
        ProductIterator prodit_;
    };
}


#endif //JIMP_EXERCISES_ITERABLE_H
//Jak ma wyglądać klasa Zipper (i jej podobne) w zadaniu? Ona ma dziedziczyć po Iterable, tak? Ma implementować ConstBegin i ConstEnd? Musi do tego mieć jakieś swoje pole?
