#include <gtest/gtest.h>
#include "../src/binary_tree/binary_tree.h"
#include <sstream>

// Functionality Tests
TEST(BinaryTreeFunctionalityTests, AddAndFind) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20);
    bst.Add(5);

    EXPECT_TRUE(bst.Find(10));
    EXPECT_TRUE(bst.Find(20));
    EXPECT_TRUE(bst.Find(5));
    EXPECT_FALSE(bst.Find(15)); // Element not added
}

TEST(BinaryTreeFunctionalityTests, RemoveAndFind) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20);
    bst.Add(5);
    bst.Remove(10);

    EXPECT_FALSE(bst.Find(10));
    EXPECT_TRUE(bst.Find(20));
    EXPECT_TRUE(bst.Find(5));
}

TEST(BinaryTreeFunctionalityTests, InorderTraversal) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20);
    bst.Add(5);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    bst.InorderTraverse();
    std::cout.rdbuf(oldCoutBuffer); // Reset cout

    EXPECT_EQ(output.str(), "5 10 20 \n");
}

TEST(BinaryTreeFunctionalityTests, MaximumValue) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20);
    bst.Add(5);

    EXPECT_EQ(bst.Maximum(), 20);

    BinaryTree singleNodeTree;
    singleNodeTree.Add(15);
    EXPECT_EQ(singleNodeTree.Maximum(), 15);
}

TEST(BinaryTreeFunctionalityTests, RemoveNodeWithNoChildren) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20); // Leaf node
    bst.Add(5);

    bst.Remove(20); // Remove a node with no children

    EXPECT_FALSE(bst.Find(20));
    EXPECT_TRUE(bst.Find(10));
    EXPECT_TRUE(bst.Find(5));
}

TEST(BinaryTreeFunctionalityTests, RemoveNodeWithOneChild) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20);
    bst.Add(5);
    bst.Add(25); // Right child of 20

    bst.Remove(20); // Remove a node with one child

    EXPECT_FALSE(bst.Find(20));
    EXPECT_TRUE(bst.Find(25)); // Child of the removed node remains
    EXPECT_TRUE(bst.Find(10));
    EXPECT_TRUE(bst.Find(5));
}

TEST(BinaryTreeFunctionalityTests, RemoveNodeWithTwoChildren) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(20);
    bst.Add(5);
    bst.Add(15); // Left child of 20
    bst.Add(25); // Right child of 20

    bst.Remove(20); // Remove a node with two children

    EXPECT_FALSE(bst.Find(20));
    EXPECT_TRUE(bst.Find(15)); // Inorder successor
    EXPECT_TRUE(bst.Find(25));
    EXPECT_TRUE(bst.Find(10));
    EXPECT_TRUE(bst.Find(5));
}

// Edge Case Tests
TEST(BinaryTreeEdgeCaseTests, EmptyTreeOperations) {
    BinaryTree bst;

    EXPECT_THROW(bst.Maximum(), std::out_of_range);
    EXPECT_FALSE(bst.Find(10));

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    bst.InorderTraverse();
    std::cout.rdbuf(oldCoutBuffer); // Reset cout

    EXPECT_EQ(output.str(), "\n"); // No output for empty tree
}

TEST(BinaryTreeEdgeCaseTests, DuplicateElements) {
    BinaryTree bst;
    bst.Add(10);
    bst.Add(10); // Attempt to add duplicate

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    bst.InorderTraverse();
    std::cout.rdbuf(oldCoutBuffer); // Reset cout

    EXPECT_EQ(output.str(), "10 \n"); // No duplicates in output
}

TEST(BinaryTreeEdgeCaseTests, SingleNodeTree) {
    BinaryTree bst;
    bst.Add(10);

    EXPECT_TRUE(bst.Find(10));
    EXPECT_EQ(bst.Maximum(), 10);

    bst.Remove(10);
    EXPECT_FALSE(bst.Find(10));
}

TEST(BinaryTreeEdgeCaseTests, UnbalancedTree) {
    BinaryTree bst;
    for (int i = 1; i <= 5; ++i) {
        bst.Add(i);
    }

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    bst.InorderTraverse();
    std::cout.rdbuf(oldCoutBuffer); // Reset cout

    EXPECT_EQ(output.str(), "1 2 3 4 5 \n");
}
