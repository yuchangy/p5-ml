// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

TEST(test_tree_dimensions){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(6);
    tree.insert(4);
    
    std::cout << tree.to_string() << std::endl;
    
    ASSERT_TRUE(tree.size() == 3);
    ASSERT_TRUE(tree.height() == 2);
    std::cout << *tree.min_greater_than(5) << std::endl;
    ASSERT_TRUE(*tree.min_greater_than(5) == 6)
    
}

TEST_MAIN()
