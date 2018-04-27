//
// Created by Kuba on 23-04-18.
//

#include "Iterable.h"

namespace utility
{
    IterableIterator::IterableIterator(const IterableIterator &ii)
    {
        left_=ii.left_;
        right_=ii.right_;
        left_end_=ii.left_end_;
        right_end_=ii.right_end_;
    }

    IterableIterator & IterableIterator::operator=(const IterableIterator &ii)
    {
        if (this == &ii) {
            return *this;
        }

        left_=ii.left_;
        right_=ii.right_;
        left_end_=ii.left_end_;
        right_end_=ii.right_end_;
    }

    //-------------------------------------------------------------------------------------------------------------------

    ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left, std::vector<std::string>::const_iterator right,
                                   std::vector<int>::const_iterator left_end, std::vector<std::string>::const_iterator right_end)
    {
        left_=left;
        right_=right;
        left_end_=left_end;
        right_end_=right_end;
    }

    std::pair<int, std::string> ZipperIterator::Dereference() const
    {
        std::pair<int, std::string> values;
        values.first=*left_;
        values.second=*right_;
        return values;
    }

    IterableIterator & ZipperIterator::Next()
    {
        if(left_==left_end_-1 && right_==right_end_-1)
        {
            left_++;
            right_++;
            return *this;
        }
        if(left_!=left_end_-1)
            left_++;
        if(right_!=right_end_-1)
            right_++;
        return *this;
    }

    bool ZipperIterator::NotEquals(const std::unique_ptr<IterableIterator> &other) const
    {
        bool logic1=other->left_==left_, logic2=other->right_==right_;
        bool conj=logic1 && logic2;
        return !conj;
    }

    //--------------------------------------------------------------------------------------------------------------------

    EnumerateIterator::EnumerateIterator(std::vector<std::string>::const_iterator right, std::vector<std::string>::const_iterator right_end)
    {
        right_begin_=right;
        right_=right;
        right_end_=right_end;
    }

    std::pair<int, std::string> EnumerateIterator::Dereference() const
    {
        std::pair<int, std::string> values;
        values.first=right_-right_begin_+1;
        values.second=*right_;
        return values;
    }

    IterableIterator &EnumerateIterator::Next()
    {
        right_++;
        return *this;
    }

    bool EnumerateIterator::NotEquals(const std::unique_ptr<IterableIterator> &other) const
    {
        return (right_!=other->right_);
    }

    //--------------------------------------------------------------------------------------------------------------------

    ProductIterator::ProductIterator(std::vector<int>::const_iterator left, std::vector<std::string>::const_iterator right,
                                     std::vector<int>::const_iterator left_end, std::vector<std::string>::const_iterator right_end)
    {
        right_begin_=right;
        left_begin_=left;
        left_=left;
        right_=right;
        left_end_=left_end;
        right_end_=right_end;
    }

    std::pair<int, std::string> ProductIterator::Dereference() const
    {
        std::pair<int, std::string> values;
        values.first=*left_;
        values.second=*right_;
        return values;
    }

    IterableIterator &ProductIterator::Next()
    {
        if(right_!=right_end_-1)
        {
            right_++;
            return *this;
        }
        if(left_!=left_end_-1) // && right_==right_end_-1)
        {
            left_++;
            right_=right_begin_;
            return *this;
        }
        //if(left_==left_end_-1 && right_==right_end_-1)
        left_++;
        right_++;
        return *this;
    }

    bool ProductIterator::NotEquals(const std::unique_ptr<IterableIterator> &other) const
    {
        return !(right_==other->right_ && left_==other->left_);
    }

    //====================================================================================================================

    IterableIteratorWrapper::IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator)
    {
        iter_=move(iterator);
    }

    bool IterableIteratorWrapper::operator!=(const IterableIteratorWrapper &other)
    {
        return iter_->NotEquals(other.iter_);
    }

    std::pair<int, std::string> IterableIteratorWrapper::operator*()
    {
        return iter_->Dereference();
    }

    IterableIteratorWrapper & IterableIteratorWrapper::operator++()
    {
        iter_->Next();
        return *this;
    }

    //====================================================================================================================

    IterableIteratorWrapper Iterable::cbegin() const
    {
        IterableIteratorWrapper tmp(move(this->ConstBegin()));
        return tmp;
    }

    IterableIteratorWrapper Iterable::cend() const
    {
        IterableIteratorWrapper tmp(move(this->ConstEnd()));
        return tmp;
    }

    IterableIteratorWrapper Iterable::begin() const
    {
        return this->cbegin();
    }

    IterableIteratorWrapper Iterable::end() const
    {
        return this->cend();
    }

    //---------------------------------------------------------------------------------------------------------------------

    Zipper::Zipper(std::vector<int> &vi, std::vector<std::string> &vs) :zipit_(vi.begin(), vs.begin(), vi.end(), vs.end())
    {
        vi_=std::make_unique<std::vector<int>>(vi);
        vs_=std::make_unique<std::vector<std::string>>(vs);
    }

    std::unique_ptr<IterableIterator> Zipper::ConstBegin() const
    {
        ZipperIterator x;
        std::unique_ptr<IterableIterator> tmp=std::make_unique<ZipperIterator>(x);
        tmp->left_=vi_->begin();
        tmp->right_=vs_->begin();
        tmp->left_end_=vi_->end();
        tmp->right_end_=vs_->end();
        return move(tmp);
    }

    std::unique_ptr<IterableIterator> Zipper::ConstEnd() const
    {
        ZipperIterator x;
        std::unique_ptr<IterableIterator> tmp=std::make_unique<ZipperIterator>(x);
        tmp->left_=vi_->end();
        tmp->right_=vs_->end();
        tmp->left_end_=vi_->end();
        tmp->right_end_=vs_->end();
        return move(tmp);
    }

    //-------------------------------------------------------------------------------------------------------------------

    Enumerate::Enumerate(std::vector<std::string> vs) : enumit_(vs.begin(), vs.end())
    {
        vs_=std::make_unique<std::vector<std::string>>(vs);
    }
    std::unique_ptr<IterableIterator> Enumerate::ConstBegin() const
    {
        EnumerateIterator x;
        std::unique_ptr<IterableIterator> tmp=std::make_unique<EnumerateIterator>(x);
        tmp->right_begin_=vs_->begin();
        tmp->right_=vs_->begin();
        tmp->right_end_=vs_->end();
        return move(tmp);
    }

    std::unique_ptr<IterableIterator> Enumerate::ConstEnd() const
    {
        EnumerateIterator x;
        std::unique_ptr<IterableIterator> tmp=std::make_unique<EnumerateIterator>(x);
        tmp->right_begin_=vs_->begin();
        tmp->right_=vs_->end();
        tmp->right_end_=vs_->end();
        return move(tmp);
    }

    //-------------------------------------------------------------------------------------------------------------------

    Product::Product(std::vector<int> vi, std::vector<std::string> vs) : prodit_(vi.begin(), vs.begin(), vi.end(), vs.end())
    {
        vi_=std::make_unique<std::vector<int>>(vi);
        vs_=std::make_unique<std::vector<std::string>>(vs);
    }

    std::unique_ptr<IterableIterator> Product::ConstBegin() const
    {
        ProductIterator x;
        std::unique_ptr<IterableIterator> tmp=std::make_unique<ProductIterator>(x);
        tmp->left_begin_=vi_->begin();
        tmp->right_begin_=vs_->begin();
        tmp->left_=vi_->begin();
        tmp->right_=vs_->begin();
        tmp->left_end_=vi_->end();
        tmp->right_end_=vs_->end();
        return move(tmp);
    }

    std::unique_ptr<IterableIterator> Product::ConstEnd() const
    {
        ProductIterator x;
        std::unique_ptr<IterableIterator> tmp=std::make_unique<ProductIterator>(x);
        tmp->left_begin_=vi_->begin();
        tmp->right_begin_=vs_->begin();
        tmp->left_=vi_->end();
        tmp->right_=vs_->end();
        tmp->left_end_=vi_->end();
        tmp->right_end_=vs_->end();
        return move(tmp);
    }
}