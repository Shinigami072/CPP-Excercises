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
        current=0;
    }



    std::pair<int, std::string> ZipperIterator::Dereference() const {
        auto r = right+current;
        if(r >= right_end)
             r = right_end-1;


        auto l = left + current;
        if (l>= left_end)
                    l =left_end-1;

        auto p =std::pair<int, std::string>(*(l), *(r));;
        return p;
    }

    IterableIterator &ZipperIterator::Next() {
        //if((left+current)!=left_end && (right+current)!=right_end)
            current++;
        return *this;
    }

    bool ZipperIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
        auto z = dynamic_cast<const ZipperIterator&>(*other);
        auto l = left+current;
        if(left+current>=left_end)
            l=left_end;
        auto r = left+current;
        if(left+current>=left_end)
            l=left_end;
        auto zl = left+current;
        if(left+current>=left_end)
            l=left_end;
        auto zr = left+current;
        if(left+current>=left_end)
            l=left_end;

        return l !=zl || r != zr;
    }
//====================================================================================================

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
        auto p= std::pair<int, std::string>(*(left + currentl), *(right + currentr));
        return p;
    }

    IterableIterator &ProductIterator::Next() {
        if((right+currentr)!=right_end-1)
            currentr++;
        else{
            currentl++;
            if(left+currentl!=left_end)
                currentr=0;
            else
                currentr++;
        }
        return *this;
    }

    bool ProductIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
        auto p=dynamic_cast<const ProductIterator&>(*other);
        return ((left+currentl) !=(p.left+p.currentl) ||(right+currentr)!=(p.right+p.currentr)) ;
    }
}