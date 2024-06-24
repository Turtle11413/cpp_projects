#ifndef S21_CONTAINERS_S21_RBTREE_RBTREE_H_
#define S21_CONTAINERS_S21_RBTREE_RBTREE_H_

#include <climits>
#include <utility>

namespace rbtree {
template <typename key_type, typename value_type>
class Node {
 public:
  Node(){};
  Node(key_type key, value_type value, char color)
      : key_(key), value_(value), color_(color){};
  Node(key_type key, value_type value)
      : key_(key), value_(value), color_('R'){};

  Node<key_type, value_type> *GetChildren(
      char direction, bool is_reverse = false) const noexcept {
    bool is_left = direction == 'L';
    if (is_reverse ^ is_left) {
      return left_;
    } else {
      return right_;
    }
  }

  key_type key_ = key_type();
  value_type value_ = value_type();
  char color_ = 'B';
  Node<key_type, value_type> *left_ = nullptr;
  Node<key_type, value_type> *right_ = nullptr;
  Node<key_type, value_type> *parent_ = nullptr;

  Node<key_type, value_type> *getBrother() const noexcept {
    if (this == this->parent_->left_) return this->parent_->right_;
    return this->parent_->left_;
  }
};

template <typename key_type, typename value_type = key_type>
class TreeIterator {
 public:
  using size_type = std::size_t;

  TreeIterator() noexcept : current_(nullptr), end_(nullptr) {}
  TreeIterator(Node<key_type, value_type> *current) noexcept
      : current_(current), end_(nullptr) {}
  TreeIterator(Node<key_type, value_type> *current,
               Node<key_type, value_type> *end) noexcept
      : current_(current), end_(end) {}
  void SetNode(Node<key_type, value_type> *node) noexcept { current_ = node; }
  void SetEnd(Node<key_type, value_type> *node) noexcept { end_ = node; }
  TreeIterator operator+(const size_type rhs) const noexcept {
    TreeIterator it(*this);
    return it.MoveIterator(rhs, true);
  }
  TreeIterator operator-(const size_type rhs) const noexcept {
    TreeIterator it(*this);
    return it.MoveIterator(rhs, false);
  }
  value_type &operator*() const noexcept { return current_->value_; }
  Node<key_type, value_type> *operator->() const noexcept { return current_; }
  operator void *() const noexcept { return current_; }
  bool operator>(const TreeIterator &other) const noexcept {
    return current_ > other.current_;
  }
  bool operator<(const TreeIterator &other) const noexcept {
    return current_ < other.current_;
  }
  TreeIterator &operator+=(const size_type rhs) noexcept {
    *this = *this + rhs;
    return *this;
  }
  TreeIterator &operator-=(const size_type rhs) noexcept {
    *this = *this - rhs;
    return *this;
  }
  TreeIterator &operator++() noexcept { return *this += 1; }
  TreeIterator &operator--() noexcept { return *this -= 1; }
  bool operator==(const TreeIterator &other) const noexcept {
    return other.current_ == current_;
  }
  bool operator!=(const TreeIterator &other) const noexcept {
    return other.current_ != current_;
  }

  Node<key_type, value_type> *current_;
  Node<key_type, value_type> *end_;

 protected:
  TreeIterator(std::pair<Node<key_type, value_type> *, bool> res) noexcept
      : current_(res.first->current_) {}

  std::pair<Node<key_type, value_type> *, bool> GetNext(
      bool reverse = false) const noexcept {
    Node<key_type, value_type> *next = nullptr;
    bool found = false;
    if (current_ == end_) {
      return std::pair<Node<key_type, value_type> *, bool>(current_->parent_,
                                                           true);
    } else if (current_->GetChildren('R', reverse)) {
      next = current_->GetChildren('R', reverse);
      while (next->GetChildren('L', reverse)) {
        next = next->GetChildren('L', reverse);
      }
      found = true;
    } else {
      next = current_->parent_;
      Node<key_type, value_type> *prev = current_;
      while (next && next->GetChildren('L', reverse) != prev) {
        prev = next;
        next = next->parent_;
      }
      if (next != nullptr) found = true;
    }
    if (!found) next = end_;
    return std::pair<Node<key_type, value_type> *, bool>(next, found);
  }

  TreeIterator MoveIterator(const size_type count, bool forward) noexcept {
    std::pair<Node<key_type, value_type> *, bool> p = GetNext(!forward);
    for (size_type i = 1; i < count && p.second; i++) {
      current_ = p.first;
      p = GetNext(!forward);
    }
    TreeIterator it(*this);
    it.SetNode(p.first);
    return it;
  }
};

template <typename key_type, typename value_type = key_type>
class TreeConstIterator : public TreeIterator<key_type, value_type> {
 public:
  TreeConstIterator() noexcept : TreeIterator<key_type, value_type>() {}
  TreeConstIterator(const Node<key_type, value_type> *root) noexcept
      : TreeIterator<key_type, value_type>((Node<key_type, value_type> *)root) {
  }
  const Node<key_type, value_type> *operator->() const noexcept {
    return current_;
  }
  const Node<key_type, value_type> *current_;
};

template <typename key_type, typename value_type>
class RBTree {
 public:
  RBTree() noexcept : root_(nullptr), end_node_(), size_(0){};
  RBTree(key_type key) {
    root_ = new Node<key_type, value_type>(key);
    root_->color_ = 'B';
  }
  RBTree(key_type key, value_type value) {
    root_ = new Node<key_type, value_type>(key, value);
    root_->color_ = 'B';
  }

  RBTree(const RBTree &other) { *this = other; }

  RBTree(RBTree &&other) noexcept { *this = std::move(other); }

  RBTree &operator=(const RBTree &other) {
    if (this != &other) {
      clear();
      size_ = other.size_;
      CopyNodeRecursively(root_, other.root_, nullptr);
      UpdateEnd();
    }
    return *this;
  }

  RBTree &operator=(RBTree &&other) noexcept {
    if (this != &other) {
      clear();
      root_ = other.root_;
      size_ = other.size_;
      end_node_ = other.end_node_;

      other.root_ = nullptr;
      other.size_ = 0;
      other.end_node_ = Node<key_type, value_type>();
    }
    return *this;
  }

  ~RBTree() noexcept {
    clear();
    UpdateEnd();
    size_ = 0;
  }

  std::pair<Node<key_type, value_type> *, bool> insert(
      key_type key, value_type value, bool add_only_unique_values) {
    Node<key_type, value_type> *root = root_;
    Node<key_type, value_type> *new_node_father = nullptr;

    while (root != nullptr) {
      new_node_father = root;
      if (add_only_unique_values) {
        if (key < root->key_) {
          root = root->left_;
        } else if (key > root->key_) {
          root = root->right_;
        } else {
          return std::pair<Node<key_type, value_type> *, bool>(nullptr, false);
        }
      } else {
        if (key <= root->key_) {
          root = root->left_;
        } else {
          root = root->right_;
        }
      }
    }

    Node<key_type, value_type> *new_node =
        new Node<key_type, value_type>(key, value);

    ++size_;

    new_node->parent_ = new_node_father;
    if (new_node->parent_ == nullptr)
      root_ = new_node;
    else if (new_node->key_ <= new_node_father->key_)
      new_node_father->left_ = new_node;
    else
      new_node_father->right_ = new_node;

    makeBalancedAfterInsert(new_node);
    UpdateEnd();
    return std::pair<Node<key_type, value_type> *, bool>(new_node, true);
  }

  void erase(const key_type &key) {
    Node<key_type, value_type> *node = FindNode(key);
    if (node) {
      eraseNode(node);
    }
  }

  void erase(TreeIterator<key_type, value_type> pos) {
    if (pos.current_ != &end_node_) {
      eraseNode(pos.current_);
    }
  }

  void clear() noexcept {
    ClearRecursively(root_);
    root_ = nullptr;
    UpdateEnd();
  }

  std::size_t size() const noexcept { return size_; }
  std::size_t max_size() const noexcept {
    return LONG_MAX / sizeof(Node<key_type, value_type>);
  }

  void UpdateEnd() noexcept {
    end_node_.parent_ = findMax(root_);
    end_node_.left_ = end_node_.parent_;
    end_node_.right_ = end_node_.parent_;
  }

  TreeIterator<key_type, value_type> find(const key_type &key) noexcept {
    Node<key_type, value_type> *node = FindNode(key);
    node = node ? FindFirstOccurrence(node) : &end_node_;
    TreeIterator<key_type, value_type> it(node, &end_node_);
    return it;
  }

  TreeIterator<key_type, value_type> lower_bound(const key_type &key) {
    auto it = begin();
    for (; it != end() && *it < key; ++it)
      ;
    return it;
  }

  TreeIterator<key_type, value_type> upper_bound(const key_type &key) {
    auto it = begin();
    for (; it != end() && *it <= key; ++it)
      ;
    return it;
  }

  Node<key_type, value_type> *FindFirstOccurrence(
      Node<key_type, value_type> *node) {
    key_type key = node->key_;
    TreeIterator<key_type, value_type> temp(node, &end_node_);
    for (; temp != begin() && temp.current_->key_ == key; --temp)
      ;
    if (temp.current_->key_ == key) {
      node = temp.current_;
    } else {
      node = (temp + 1).current_;
    }
    return node;
  }

  std::size_t count(const key_type &key) {
    std::size_t result = 0;
    auto it = find(key);

    for (; it != end() && *it == key; ++it, ++result)
      ;

    return result;
  }

  bool contains(const key_type &key) const noexcept {
    Node<key_type, value_type> *node = FindNode(key);
    return node != nullptr;
  }

  TreeIterator<key_type, value_type> begin() noexcept {
    Node<key_type, value_type> *min = findMin(root_);
    min = min == nullptr ? &end_node_ : min;
    return TreeIterator(min, &end_node_);
  }

  TreeIterator<key_type, value_type> end() noexcept {
    return TreeIterator(&end_node_, &end_node_);
  }

  void swap(RBTree &other) noexcept {
    Node<key_type, value_type> *tmp_node = root_;
    Node<key_type, value_type> tmp_end = end_node_;
    std::size_t tmp_size = size_;

    root_ = other.root_;
    other.root_ = tmp_node;

    size_ = other.size_;
    other.size_ = tmp_size;

    end_node_ = other.end_node_;
    other.end_node_ = tmp_end;
  }

  Node<key_type, value_type> *root_ = nullptr;
  Node<key_type, value_type> end_node_;

 private:
  void CopyNodeRecursively(Node<key_type, value_type> *&dst,
                           const Node<key_type, value_type> *src,
                           Node<key_type, value_type> *parent) {
    if (src) {
      dst = new Node<key_type, value_type>(*src);
      dst->parent_ = parent;
      CopyNodeRecursively(dst->left_, src->left_, dst);
      CopyNodeRecursively(dst->right_, src->right_, dst);
    }
  }

  void leftRotate(Node<key_type, value_type> *node) noexcept {
    Node<key_type, value_type> *child = node->right_;
    if (child != nullptr) child->parent_ = node->parent_;

    if (node->parent_ != nullptr) {
      if (node->parent_->left_ == node) {
        node->parent_->left_ = child;
      } else {
        node->parent_->right_ = child;
      }
    }
    node->right_ = child != nullptr ? child->left_ : nullptr;
    if (child != nullptr && child->left_ != nullptr)
      child->left_->parent_ = node;

    node->parent_ = child;
    if (child != nullptr) child->left_ = node;
    if (child != nullptr && child->parent_ == nullptr) root_ = child;
  }

  void rightRotate(Node<key_type, value_type> *node) noexcept {
    Node<key_type, value_type> *child = node->left_;

    if (child != nullptr) child->parent_ = node->parent_;

    if (node->parent_ != nullptr) {
      if (node->parent_->left_ == node) {
        node->parent_->left_ = child;
      } else {
        node->parent_->right_ = child;
      }
    }

    node->left_ = child != nullptr ? child->right_ : nullptr;
    if (child != nullptr && child->right_ != nullptr) {
      child->right_->parent_ = node;
    }

    node->parent_ = child;
    if (child != nullptr) child->right_ = node;
    if (child != nullptr && child->parent_ == nullptr) root_ = child;
  }

  // rebalance insert
  void makeBalancedAfterInsert(Node<key_type, value_type> *node) noexcept {
    while (node->parent_ != nullptr && node->parent_->color_ == 'R') {
      // left subtree
      if (node->parent_ == node->parent_->parent_->left_) {
        Node<key_type, value_type> *uncle = node->parent_->parent_->right_;
        // case 1: uncle(R)
        if (uncle != nullptr && uncle->color_ == 'R') {
          node->parent_->color_ = 'B';
          uncle->color_ = 'B';
          node->parent_->parent_->color_ = 'R';
          node = node->parent_->parent_;
        } else {  // case 2: uncle(B) or uncle is not exists
          if (node == node->parent_->right_) {
            // case 2.1: node is right child -> leftRotate subtree
            node = node->parent_;
            leftRotate(node);
          }  // case 2 main part -> rightRotate subtree
          node->parent_->color_ = 'B';
          node->parent_->parent_->color_ = 'R';
          rightRotate(node->parent_->parent_);
        }
      } else {  // right subtree (leftRotate <-> rightRotate)
        Node<key_type, value_type> *uncle = node->parent_->parent_->left_;
        if (uncle != nullptr && uncle->color_ == 'R') {
          node->parent_->color_ = 'B';
          uncle->color_ = 'B';
          node->parent_->parent_->color_ = 'R';
          node = node->parent_->parent_;
        } else {
          if (node == node->parent_->left_) {
            node = node->parent_;
            rightRotate(node);
          }
          node->parent_->color_ = 'B';
          node->parent_->parent_->color_ = 'R';
          leftRotate(node->parent_->parent_);
        }
      }
    }
    root_->color_ = 'B';
  }

  void swapNodes(Node<key_type, value_type> *node1,
                 Node<key_type, value_type> *node2) noexcept {
    if (node1->parent_ == nullptr)
      root_ = node2;
    else if (node1 == node1->parent_->left_) {
      node1->parent_->left_ = node2;
    } else {
      node1->parent_->right_ = node2;
    }
    if (node2 != nullptr) {
      node2->parent_ = node1->parent_;
    }
  }

  void eraseNode(Node<key_type, value_type> *&node) noexcept {
    Node<key_type, value_type> *new_root_subtree = node;
    Node<key_type, value_type> *new_root_subtree_child = nullptr;

    char erased_node_color = node->color_;

    if (node->left_ == nullptr) {
      new_root_subtree_child = node->right_;
      swapNodes(node, node->right_);
    } else if (node->right_ == nullptr) {
      new_root_subtree_child = node->left_;
      swapNodes(node, node->left_);
    } else {
      if (node->right_ != nullptr)
        new_root_subtree = findMin(node->right_);
      else
        new_root_subtree = findMax(node->left_);
      erased_node_color = new_root_subtree->color_;
      new_root_subtree_child = new_root_subtree->right_;
      if (new_root_subtree->parent_ == node &&
          new_root_subtree_child != nullptr) {
        new_root_subtree_child->parent_ = new_root_subtree;
      } else {
        swapNodes(new_root_subtree, new_root_subtree->right_);
        new_root_subtree->right_ = node->right_;
        if (new_root_subtree->right_ != nullptr)
          new_root_subtree->right_->parent_ = new_root_subtree;
      }
      swapNodes(node, new_root_subtree);
      new_root_subtree->left_ = node->left_;
      if (new_root_subtree->left_ != nullptr)
        new_root_subtree->left_->parent_ = new_root_subtree;
      new_root_subtree->color_ = node->color_;
    }

    delete node;
    --size_;
    if (erased_node_color == 'B') {
      if (new_root_subtree_child != nullptr)
        makeBalancedAfterErase(new_root_subtree_child);
    }
    UpdateEnd();
  }

  void makeBalancedAfterErase(Node<key_type, value_type> *&node) noexcept {
    while (node != root_ && node->color_ == 'B') {
      rebalanceCase1(node);
    }
    if (node != nullptr) node->color_ = 'B';
  }

  void rebalanceCase1(
      Node<key_type, value_type> *&node) noexcept {  // brother is red
    Node<key_type, value_type> *brother = node->getBrother();
    if (brother != nullptr && brother->color_ == 'R') {
      brother->color_ = 'B';
      if (node->parent_ != nullptr) node->parent_->color_ = 'R';
      if (node == node->parent_->left_) {
        leftRotate(node);
        brother = node->parent_->right_;
      } else {
        rightRotate(node);
        brother = node->parent_->left_;
      }
    }
    rebalanceCase2(node);
  }

  void rebalanceCase2(Node<key_type, value_type> *&node) noexcept {
    Node<key_type, value_type> *brother = node->getBrother();
    char P = node->parent_->color_;
    char N = node->color_;
    char S = brother != nullptr ? brother->color_ : 'B';

    char Sl = 'N';
    if (brother != nullptr) {
      if (brother->left_ != nullptr)
        Sl = brother->left_->color_;
      else
        Sl = 'B';
    }
    char Sr = 'N';
    if (brother != nullptr) {
      if (brother->right_ != nullptr)
        Sr = brother->right_->color_;
      else
        Sr = 'B';
    }

    if (P == 'B' && N == 'B' && S == 'B' && Sl == 'B' && Sr == 'B') {
      if (brother != nullptr) brother->color_ = 'R';
      node = node->parent_;
    } else
      rebalanceCase3(node);
  }

  void rebalanceCase3(Node<key_type, value_type> *&node) noexcept {
    Node<key_type, value_type> *brother = node->getBrother();
    if (brother != nullptr && brother->left_ != nullptr) {
      brother->left_->color_ = 'B';
      brother->color_ = 'R';
    }
    if (node == node->parent_->left_)
      rightRotate(brother);
    else
      leftRotate(brother);
    brother = node->parent_->right_;
    rebalanceCase4(node);
  }

  void rebalanceCase4(Node<key_type, value_type> *&node) noexcept {
    Node<key_type, value_type> *brother = node->getBrother();
    if (brother != nullptr) brother->color_ = node->parent_->color_;
    if (node->parent_ != nullptr) node->parent_->color_ = 'B';
    if (brother != nullptr && brother->right_ != nullptr)
      brother->right_->color_ = 'B';

    if (node == node->parent_->left_)
      leftRotate(node->parent_);
    else
      rightRotate(node->parent_);
  }

  Node<key_type, value_type> *FindNode(const key_type &key) const noexcept {
    Node<key_type, value_type> *node = root_;

    while (node && node->key_ != key) {
      if (key > node->key_) {
        node = node->right_;
      } else {
        node = node->left_;
      }
    }

    return node;
  }

  void ClearRecursively(Node<key_type, value_type> *node) noexcept {
    if (node) {
      ClearRecursively(node->left_);
      ClearRecursively(node->right_);
      delete node;
    }
  }

  Node<key_type, value_type> *findMin(
      Node<key_type, value_type> *root) noexcept {
    while (root && root->left_ != nullptr) {
      root = root->left_;
    }
    return root;
  }

  Node<key_type, value_type> *findMax(
      Node<key_type, value_type> *root) noexcept {
    while (root && root->right_ != nullptr) {
      root = root->right_;
    }
    return root;
  }

  std::size_t size_;
};
};  // namespace rbtree

#endif  // S21_CONTAINERS_S21_RBTREE_RBTREE_H_
