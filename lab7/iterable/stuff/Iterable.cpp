#include "Iterable.h"

namespace utility {

    ZipperIterator::ZipperIterator(const std::vector<int>::const_iterator& left,
                                   const std::vector<std::string>::const_iterator& right,
                                   const std::vector<int>::const_iterator& left_end,
                                   const std::vector<std::string>::const_iterator& right_end) {
        this->left = left;
        this->left_end = left_end;
        this->right = right;
        this->right_end = right_end;
    }



    std::pair<int, std::string> ZipperIterator::Dereference() const {
        return std::pair<int, std::string>(*(left + current), *(right + current));
    }

    IterableIterator &ZipperIterator::Next() {
        if((left+current)!=left_end && (right+current)!=right_end)
            current++;
        return *this;
    }

    bool ZipperIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
        return current != dynamic_cast<const ZipperIterator&>(*other).current;
    }

    ProductIterator::ProductIterator(const std::vector<int>::const_iterator& _left,
                                     const std::vector<std::string>::const_iterator& _right,
                                     const std::vector<int>::const_iterator& _left_end,
                                     const std::vector<std::string>::const_iterator& _right_end) :
            IterableIterator(),
            left(_left),
            left_end(_left_end),
            right(_right),
            right_end(_right_end),
            currentl(0),currentr(0) {}

    std::pair<int, std::string> ProductIterator::Dereference() const {
        return std::pair<int, std::string>(*(left + currentl), *(right + currentr));
    }

    IterableIterator &ProductIterator::Next() {
        if((right+currentr+1)!=right_end)
            currentr++;
        else if((left+currentl+1)!=left_end){
            currentl++;
            currentr=0;
        }
        return *this;
    }

    bool ProductIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
        const ProductIterator & p =static_cast<const ProductIterator&>(*other);
        return ((left+currentl) !=(p.left+p.currentl) ||(right+currentr)!=(p.right+p.currentr)) ;
    }
}