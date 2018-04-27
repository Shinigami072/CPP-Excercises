//
// Created by shinigami on 22/04/18.
//

#include <iostream>
#include "ProductIterator.h"
namespace utility {

    ProductIterator::ProductIterator(std::vector<int>::const_iterator _left,
                                   std::vector<std::string>::const_iterator _right,
                                   std::vector<int>::const_iterator _left_end,
                                   std::vector<std::string>::const_iterator _right_end) :
            IterableIterator(),
            left(_left),
            right(_right),
            right_end(_right_end),
            left_end(_left_end),
            currentl(0),currentr(0) {}

    std::pair<int, std::string> ProductIterator::Dereference() const {
        return std::pair<int, std::string>(*(left + currentl), *(right + currentr));
    }

    IterableIterator &ProductIterator::Next() {
        if((right+currentr)!=right_end)
            currentr++;
        if((right+currentr)==right_end&&(left+currentl)!=left_end){
            currentl++;
           if((left+currentl)!=left_end)
           currentr=0;
        }


        return *this;
    }

    bool ProductIterator::NotEquals(const IterableIterator &other) const {
        const ProductIterator & p =dynamic_cast<const ProductIterator&>(other);
        bool  b =(left+currentl) !=(p.left+p.currentl);
        bool a=(right+currentr)!=(p.right+p.currentr);

        return a||b;
    }
}
