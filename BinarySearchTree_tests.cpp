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
    
}
TEST(copy_and_destroy){
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);

    BinarySearchTree<int> copyTree(tree);
    
    ASSERT_EQUAL(*copyTree.max_element(), *tree.max_element());
    ASSERT_EQUAL(*copyTree.find(6), 6);
    
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
TEST_MAIN()
