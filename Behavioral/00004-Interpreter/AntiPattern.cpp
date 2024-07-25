#include <iostream>
#include <stack>
#include <print>
#include <ranges>
#include <algorithm>

std::string name{"ahmed"};

template <typename T>
struct BinaryTreeNode {
        T data;
        BinaryTreeNode *leftNode;
        BinaryTreeNode *rightNode;
};

template <typename T>
class BinaryTree {
        BinaryTreeNode<T> *base{};
public:
        BinaryTree() : base(nullptr) {}

        void insert(T data) {
                BinaryTreeNode<T> *node = new BinaryTreeNode<T>;
                node->data = data;
                node->leftNode = node->rightNode = nullptr;

                if (base == nullptr) {
                        base = node;
                } else {
                        BinaryTreeNode<T> *current = base;
                        BinaryTreeNode<T> *parent = nullptr;

                        while (true) {
                                parent = current;
                                if (data < parent->data) {
                                        current = current->leftNode;
                                        if (current == nullptr) {
                                                parent->leftNode = node;
                                                return;
                                        }
                                } else {
                                        current = current->rightNode;
                                        if (current == nullptr) {
                                                parent->rightNode = node;
                                                return;
                                        }
                                }
                        }
                }
        }

        BinaryTreeNode<T>* getBase() {
                return base;
        }

        class iterator {
                std::stack<BinaryTreeNode<T>*> stack;

        public:
                iterator(BinaryTreeNode<T>* root) {
                        while (root) {
                                stack.push(root);
                                root = root->leftNode;
                        }
                }

                T& operator*() {
                        BinaryTreeNode<T>* topNode = stack.top();
                        return topNode->data;
                }

                iterator& operator++() {
                        if (!stack.empty()) {
                                BinaryTreeNode<T>* node = stack.top();
                                stack.pop();
                                node = node->rightNode;

                                while (node) {
                                        stack.push(node);
                                        node = node->leftNode;
                                }
                        }

                        return *this;
                }

                bool operator!=(const iterator& other) {
                        return !stack.empty();
                }
        };

        iterator begin() {
                return iterator(base);
        }

        iterator end() {
                return iterator(nullptr);
        }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, BinaryTreeNode<T>& node) {
        return os << node.data;
}

auto function() ->void {}

auto namasdfsdaf{10};

int main() {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(1);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        std::cout << "ahmed" << std::endl;
        function();
        std::cout << "ahmed" << std::endl;
                        function();
        std::cout << "ahmed" << std::endl;
                                function();
        std::cout << "ahmed" << std::endl;

        // this is just a test for the comment.
        //
        auto string {"this is a test for the strings"};
        if (true)  {

        } else {

        }

        class TestClass{
        public:
                TestClass() = default;
                TestClass(TestClass &) = delete;
                inline virtual auto fnction() -> bool = 0; 
        };

        class TestClass2 : public TestClass {
                inline virtual auto function() -> bool {
                        return true;
                }
                auto functions() -> bool {
                        return true;
                }
        };

        char x;
        switch (x) {
                case 'b':
                        break;
                case 'a':
                case 'c':
                        break;
        }
        for (;;) {
        }
        auto ahmed = 1'000'000;
        
        for (auto const & data : tree) {
                std::cout << data << " ";
        }

        return 0;
}
