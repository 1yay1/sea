#ifndef SEALIB_COLLECTION_SEQUENCE_H_
#define SEALIB_COLLECTION_SEQUENCE_H_
#include "sealib/_types.h"

namespace Sealib {
/**
 * An sequence interface to be used by several classes in this library.
 * @author Simon Heuser
 * 
 * @tparam T type used for getting and inserting values
 * @tparam I type used for indexing
 */
template <class T, class I = uint64_t>
class Sequence {
 public:
    /**
     * Get an element from the sequence.
     * @param i index
     * @return the element at the given index
     */
    virtual T get(I i) const = 0;

    /**
     * Insert an element into the sequence.
     * @param i index
     * @param v element to insert
     */
    virtual void insert(I i, T v) = 0;

 protected:
    Sequence() = default;
    Sequence(Sequence const &) = default;
    Sequence &operator=(Sequence const &) = default;
    Sequence(Sequence &&) = default;
    Sequence &operator=(Sequence &&) = default;
    virtual ~Sequence() = default;
};
}  // namespace Sealib
#endif  // SEALIB_COLLECTION_SEQUENCE_H_
