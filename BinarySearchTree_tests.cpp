// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

TEST(test_tree_dimensions){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(6);
    tree.insert(4);
    
    
    ASSERT_TRUE(tree.size() == 3);
    ASSERT_TRUE(tree.height() == 2);
    ASSERT_TRUE(*tree.min_greater_than(5) == 6);
    ASSERT_TRUE(*tree.max_element() == 6);
    ASSERT_TRUE(*tree.min_element() == 4);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(*tree.min_greater_than(3) == 4);
    ASSERT_EQUAL(tree.min_greater_than(7), tree.end());
    
    BinarySearchTree<int> treee;
    treee.insert(-4);
    treee.insert(-6);
    treee.insert(0);
    
    ASSERT_TRUE(treee.height() == 2);
    ASSERT_TRUE(tree.size() == 3);
    ASSERT_FALSE(tree.empty());
    
}
TEST(copy_and_destroy){
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);

    BinarySearchTree<int> copyTree(tree);
    
    ASSERT_EQUAL(*copyTree.max_element(), *tree.max_element());
    ASSERT_EQUAL(*copyTree.find(6), 6);
    
    BinarySearchTree<int> treee;
    treee.insert(-60);
    treee.insert(6);
    treee.insert(60);
    treee.insert(0);
    treee.insert(30000);
    treee = BinarySearchTree<int>();
    ASSERT_TRUE(treee.empty());
    
}

TEST(Traversal_test){
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);
    
    std::ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder.str() == "6 5 7 ");
    
    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder.str() == "5 6 7 ");
    
}

TEST(traverse_inorder) {
    BinarySearchTree<int> empty_tree;
    std::ostringstream oss_empty;
    empty_tree.traverse_inorder(oss_empty);
    ASSERT_TRUE(oss_empty.str().empty());
    
    BinarySearchTree<int> one_node_tree;
    one_node_tree.insert(1);
    std::ostringstream oss_one_node;
    one_node_tree.traverse_inorder(oss_one_node);
    ASSERT_TRUE(oss_one_node.str() == "1 ");

    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);
    std::ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_TRUE(oss.str() == "5 6 7 ");
    
    BinarySearchTree<int> treeemp;
    std::ostringstream treeemp_inorder;
    treeemp.traverse_inorder(treeemp_inorder);
    ASSERT_TRUE(treeemp_inorder.str() == "");
    ASSERT_FALSE(treeemp_inorder.str() == " ");
}
TEST(traverse_preorder) {
    BinarySearchTree<int> empty_tree;
    std::ostringstream oss_empty;
    empty_tree.traverse_preorder(oss_empty);
    ASSERT_TRUE(oss_empty.str().empty());
    
    BinarySearchTree<int> one_node_tree;
    one_node_tree.insert(1);
    std::ostringstream oss_one_node;
    one_node_tree.traverse_preorder(oss_one_node);
    ASSERT_TRUE(oss_one_node.str() == "1 ");

    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);
    std::ostringstream oss;
    tree.traverse_preorder(oss);
    ASSERT_TRUE(oss.str() == "6 5 7 ");
}

TEST(operator1) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    
    BinarySearchTree<int>::Iterator it1 = bst.begin();
    BinarySearchTree<int>::Iterator it2 = bst.begin();
    bool result1 = (it1 == it2);
    bool result2 = (it1 != it2);

    ASSERT_TRUE(result1 == true);
    ASSERT_TRUE(result2 == false);

}

TEST(operator2) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(8);
    bst.insert(12);
    bst.insert(18);
    
    BinarySearchTree<int>::Iterator it = bst.begin();
    ++it;
    ASSERT_TRUE(*it == 5);
}
TEST(operator4) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    
    BinarySearchTree<int>::Iterator it1 = bst.begin();
    BinarySearchTree<int>::Iterator it2 = ++bst.begin();

    bool result1 = (it1 != it2);
    bool result2 = (it1 == it2);
    
    ASSERT_TRUE(result1 == true);
    ASSERT_TRUE(result2 == false);

}
TEST(sorting_invariant) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());

    BinarySearchTree<int> treee;
    treee.insert(574378);
    ASSERT_TRUE(treee.check_sorting_invariant());

    BinarySearchTree<int> bsttt;
    bsttt.insert(0);
    bsttt.insert(1);
    bsttt.insert(2);
    bsttt.insert(3);
    bsttt.insert(4);
    ASSERT_TRUE(bsttt.check_sorting_invariant());
    BinarySearchTree<int>::Iterator j = bsttt.find(2);
    *j = -300;
    ASSERT_FALSE(bsttt.check_sorting_invariant());
    
    BinarySearchTree<int> bst;
    bst.insert(2);
    bst.insert(1);
    bst.insert(5);
    ASSERT_TRUE(bst.check_sorting_invariant());
    BinarySearchTree<int>::Iterator i = bst.find(5);
    *i = -5;
    ASSERT_FALSE(bst.check_sorting_invariant());

    BinarySearchTree<int> bstt;
    bstt.insert(5);
    bstt.insert(1);
    bstt.insert(6);
    bstt.insert(8);
    bstt.insert(17);
    ASSERT_TRUE(bstt.check_sorting_invariant());
    BinarySearchTree<int>::Iterator k = bstt.find(6);
    *k = 4;
    ASSERT_FALSE(bstt.check_sorting_invariant());
}

TEST_MAIN()
