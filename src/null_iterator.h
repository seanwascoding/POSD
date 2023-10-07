#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

#include "iterator.h"

class NullIterator : public Iterator
{
    bool isDone() const { return true; };
};

#endif // NULL_ITERATOR_H
