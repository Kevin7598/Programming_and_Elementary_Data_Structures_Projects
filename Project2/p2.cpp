#include "p2.h"
#include <iostream>
using namespace std;

//list part
int size(list_t list){
    if (list_isEmpty(list)) return 0;
    else return size(list_rest(list)) + 1;
}

int sum(list_t list){
    if (list_isEmpty(list)) return 0;
    else return sum(list_rest(list)) + list_first(list);
}

int product(list_t list){
    if (list_isEmpty(list)) return 1;
    else return product(list_rest(list)) * list_first(list);
}

static list_t reverse_helper(list_t original_list, list_t new_list){
    if (list_isEmpty(original_list)) return new_list;
    else return reverse_helper(list_rest(original_list),
                               list_make(list_first(original_list), new_list));
}
// A reverse helper is to put the elements in the original list into the new list in a reverse order.
// As in this process, a new list need to be created in advance, a helper function is needed.

list_t reverse(list_t list){
    list_t new_list = list_make();
    return reverse_helper(list, new_list);
}

static list_t append_helper(list_t list2, list_t reverse_list1){
    if (list_isEmpty(reverse_list1)) return list2;
    else return append_helper(list_make(list_first(reverse_list1), list2),
                              list_rest(reverse_list1));
}
// An append helper is to put the elements in the first list (list1) into the second list (list2) in a reverse order.
// As list_make can only put the elements at the first position, list1 needs to be reversed.
// Therefore, a helper function is needed.

list_t append(list_t first, list_t second){
    list_t reverse_list1 = reverse(first);
    return append_helper(second, reverse_list1);
}

static list_t filter_helper(list_t list, list_t new_list, int property) {
    if (list_isEmpty(list)) return new_list;
    else {
        if (abs(list_first(list)) % 2 == property)
            return filter_helper(list_rest(list),list_make(list_first(list),new_list), property);
        else return filter_helper(list_rest(list), new_list, property);
    }
}
// A filter helper is to put the elements in the original list that satisfies the property (the remainder) into
// the new list. As in this process, a new list need to be created in advance, a helper function is needed.

list_t filter_odd(list_t list){
    list_t new_list = list_make();
    return reverse(filter_helper(list, new_list, 1));
}

list_t filter_even(list_t list){
    list_t new_list = list_make();
    return reverse(filter_helper(list, new_list, 0));
}

static list_t new_filter_helper(list_t list, list_t new_list, bool (*fn)(int)) {
    if (list_isEmpty(list)) return new_list;
    else {
        if (fn(list_first(list))) return new_filter_helper(list_rest(list),
                                                           list_make(list_first(list),new_list), fn);
        else return new_filter_helper(list_rest(list), new_list, (*fn));
    }
}
// A new filter helper is to put the elements in the original list that satisfies the demand of the function (fn) into
// the new list. As in this process, a new list need to be created in advance, a helper function is needed.

list_t filter(list_t list, bool (*fn)(int)){
    list_t new_list = list_make();
    return reverse(new_filter_helper(list, new_list, (*fn)));
}

static list_t separation_helper1(list_t first, list_t left_reservation, unsigned int n){
    if (n == 0) return first;
    else return separation_helper1(list_rest(first),
                                   list_make(list_first(first), left_reservation), n - 1);
}
// This helper function helps to store the remaining elements from the first list, whose length is n.

static list_t separation_helper2(list_t first, list_t left_reservation, unsigned int n){
    if (n == 0) return reverse(left_reservation);
    else return separation_helper2(list_rest(first),
                                   list_make(list_first(first), left_reservation), n - 1);
}
// This helper function helps to store the list seperated from the first list.

list_t insert_list(list_t first, list_t second, unsigned int n){
    list_t left_reservation = list_make();
    list_t taken = separation_helper1(first, left_reservation, n);
    list_t reservation = separation_helper2(first, left_reservation, n);
    return append(append(reservation, second),taken);
}

static list_t chop_helper(list_t list, list_t collected, unsigned int n){
    if (size(list) - n == 0) return reverse(collected);
    else return chop_helper(list_rest(list), list_make(list_first(list), collected), n);
}
// This helper function helps to store the list with collected elements from the first list,
// with the number of remaining elements be n.

list_t chop(list_t list, unsigned int n){
    list_t collected = list_make();
    return chop_helper(list, collected, n);
}


//binary tree part
int tree_sum(tree_t tree){
    if (tree_isEmpty(tree)) return 0;
    return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

bool tree_search(tree_t tree, int key){
    if (tree_isEmpty(tree)) return false;
    else if (tree_elt(tree) == key) return true;
    return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
}

int depth(tree_t tree){
    int depth1, depth2;
    if (tree_isEmpty(tree)) return 0;
    else{
        depth1 = depth(tree_right(tree)) + 1;
        depth2 = depth(tree_left(tree)) + 1;
    }
    if (depth1 > depth2) return depth1;
    else return depth2;
}
// In this function, there are two values of depth, which refers to the right and left leaves of the upper binary tree,
// and they are compared to find the largest one.

static int tree_min_helper(tree_t tree, int first){
    if (tree_isEmpty(tree)) return first;
    int min = tree_elt(tree), left_min = tree_min_helper(tree_left(tree), first),
    right_min = tree_min_helper(tree_right(tree), first);
    if (left_min < min) min = left_min;
    if (right_min < min) min = right_min;
    return min;
}
// In this helper function, the values of the elements of the tree are compared from the lower level to the upper level,
// to the root, in order to find the minimum.

int tree_min(tree_t tree){
    int first = tree_elt(tree);
    return tree_min_helper(tree, first);
}

void traversal_helper(tree_t tree, list_t &list){
    if (tree_isEmpty(tree)) return;
    traversal_helper(tree_left(tree), list);
    list = list_make(tree_elt(tree), list);
    traversal_helper(tree_right(tree), list);
}
// In this function, a list is made to traverse the binary in the order of left subtree, root, and right subtree.

list_t traversal(tree_t tree){
    list_t list = list_make();
    traversal_helper(tree, list);
    return reverse(list);
}

bool tree_hasPathSum(tree_t tree, int sum){
    if (tree_isEmpty(tree)) return false;
    else {
        int remaining = sum - tree_elt(tree);
        bool state;
        if ((tree_isEmpty(tree_left(tree))) && (tree_isEmpty(tree_right(tree)))) {
            if (remaining == 0) return true;
            else return false;
        }
        if (!tree_isEmpty(tree_left(tree))) {
            state = tree_hasPathSum(tree_left(tree), remaining);
            if (state) return state;
        }
        if (!tree_isEmpty(tree_right(tree))) {
            state = tree_hasPathSum(tree_right(tree), remaining);
            if (state) return state;
        }
        return state;
    }
}
// In this function, every time when the function meets a node,
// the remaining of the sum is cut by the value of the node.
// It will check the sum of every path until the remaining is 0, which shows that there is a suitable path sum.
// Once there is a suitable one, it will return true immediately so that it can't be affected by the remaining parts.
// If all paths are checked and the needed "0" does not reach, it will return false.

bool covered_by_helper(tree_t A, tree_t B){
    if (tree_isEmpty(B) && !tree_isEmpty(A)) return false;
    else if (tree_isEmpty(A)) return true;
    if (tree_elt(A) == tree_elt(B)) {
        return covered_by_helper(tree_right(A), tree_right(B))
        && covered_by_helper(tree_left(A), tree_left(B));
    }
    else return false;
}
// This function helps to compare the elements of the two trees from the top to lower levels
// to find whether A is covered by B.

bool covered_by(tree_t A, tree_t B){
    if (tree_isEmpty(A)) return true;
    else if (tree_isEmpty(B)) return false;
    if (tree_elt(A) != tree_elt(B)) return false;
    else return covered_by_helper(A, B);
}

bool contained_by(tree_t A, tree_t B){
    if (tree_isEmpty(A)) return true;
    else if (tree_isEmpty(B)) return false;
    else if (tree_elt(A) != tree_elt(B))
        return (contained_by(A, tree_right(B)) || contained_by(A, tree_left(B)));
    return covered_by_helper(A, B);
}

tree_t insert_tree(int elt, tree_t tree){
    if (tree_isEmpty(tree)) return tree_make(elt, tree_make(), tree_make());
    if (((tree_isEmpty(tree_left(tree)))) && (elt < tree_elt(tree))){
        tree_t tree_insert = tree_make(elt, tree_make(), tree_make());
        return tree_make(tree_elt(tree), tree_insert, tree_right(tree));
    }
    if (((tree_isEmpty(tree_right(tree)))) && (elt >= tree_elt(tree))){
        tree_t tree_insert = tree_make(elt, tree_make(), tree_make());
        return tree_make(tree_elt(tree), tree_left(tree), tree_insert);
    }
    if (((!tree_isEmpty(tree_left(tree)))) && (elt < tree_elt(tree))){
        return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
    }
    if (((!tree_isEmpty(tree_right(tree)))) && (elt >= tree_elt(tree))){
        return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
    }
}
// In this function, according to the rules of a well-formed sorted binary tree,
// the element to be inserted will continuously look for the right place to insert.
// After that, it will continuously make trees with elements or subtrees near it, creating new subtrees,
// until the whole tree is created.