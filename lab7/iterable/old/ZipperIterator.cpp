//
// Created by shinigami on 21/04/18.
//

#include "ZipperIterator.h"
namespace utility {

    ZipperIterator::ZipperIterator(std::vector<int>::const_iterator _left,
                                   std::vector<std::string>::const_iterator _right,
                                   std::vector<int>::const_iterator _left_end,
                                   std::vector<std::string>::const_iterator _right_end) :
            IterableIterator(),
            left(_left),
            right(_right),
            right_end(_right_end),
            left_end(_left_end),
            current(0) {}

    std::pair<int, std::string> ZipperIterator::Dereference() const {
        return std::pair<int, std::string>(*(left + current), *(right + current));
    }

    IterableIterator &ZipperIterator::Next() {
        if((left+current)!=left_end && (right+current)!=right_end)
            current++;
        return *this;
    }

    bool ZipperIterator::NotEquals(const IterableIterator &other) const {
        return current != dynamic_cast<const ZipperIterator&>(other).current;
    }
}