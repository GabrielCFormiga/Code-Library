// Indexed Set
// 

// These lines are needed for the policy-based data structures.
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <class T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Definition:
template<
    typename Key, // Key type
    typename Mapped, // Mapped-policy
    typename Cmp_Fn = std::less<Key>, // Key comparison function
    typename Tag = rb_tree_tag, // Inner Data structure
    typename Node_Update = null_node_update, // Node update policy
    typename Allocator = std::allocator<char> // Allocator type
    > class tree;

// Methods:
// 1. insert(x): Inserts x into the set.
// 2. erase(x): Removes x from the set.
// 3. find(x): Returns an iterator to the element x if it exists, or end() if it doesn't.
// 4. find_by_order(k): Returns an iterator to the k-th smallest element (0-based index).
// 5. order_of_key(x): Returns the number of elements in the set that are strictly less than x.
// 6. lower_bound(x): Returns an iterator to the first element that is not less than x.
// 7. upper_bound(x): Returns an iterator to the first element that is greater than x.