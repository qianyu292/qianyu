#include <string>
#include <vector>
using namespace std;
class TrieMap {
private:
    // ASCII 码个数
    static const int R = 256;
    // 当前存在 Map 中的键值对个数
    int _size = 0;

    struct TrieNode {
        int val = -1;  // -1 表示无值 / en: -1 means no value
        TrieNode* children[R] = { nullptr };
        ~TrieNode() {
            for (int i = 0; i < R; i++) {
                delete children[i];
            }
        }
    };

    // Trie 树的根节点
    TrieNode* root = nullptr;

    // 定义：向以 node 为根的 Trie 树中插入 key[i..]，返回插入完成后的根节点
    TrieNode* put(TrieNode* node, const string& key, int val, int i) {
        if (node == nullptr) {
            // 如果树枝不存在，新建
            node = new TrieNode();
        }
        if (i == key.length()) {
            // key 的路径已插入完成，将值 val 存入节点
            node->val = val;
            return node;
        }
        char c = key[i];
        // 递归插入子节点，并接收返回值
        node->children[(int)c] = put(node->children[(int)c], key, val, i + 1);
        return node;
    }

    // 定义：在以 node 为根的 Trie 树中删除 key[i..]，返回删除后的根节点
    TrieNode* remove(TrieNode* node, const string& key, int i) {
        if (node == nullptr) {
            return nullptr;
        }
        if (i == key.length()) {
            // 找到了 key 对应的 TrieNode，删除 val
            node->val = -1;
        }
        else {
            char c = key[i];
            // 递归去子树进行删除
            node->children[(int)c] = remove(node->children[(int)c], key, i + 1);
        }
        // 后序位置，递归路径上的节点可能需要被清理
        if (node->val != -1) {
            // 如果该 TireNode 存储着 val，不需要被清理
            return node;
        }
        // 检查该 TrieNode 是否还有后缀
        for (int c = 0; c < R; c++) {
            if (node->children[c] != nullptr) {
                // 只要存在一个子节点（后缀树枝），就不需要被清理
                return node;
            }
        }
        // 既没有存储 val，也没有后缀树枝，则该节点需要被清理
        delete node;
        return nullptr;
    }

    // 从节点 node 开始搜索 key，如果存在返回对应节点，否则返回 null
    TrieNode* getNode(TrieNode* node, const string& key) {
        TrieNode* p = node;
        // 从节点 node 开始搜索 key
        for (int i = 0; i < key.length(); i++) {
            if (p == nullptr) {
                // 无法向下搜索
                return nullptr;
            }
            // 向下搜索
            char c = key[i];
            p = p->children[(int)c];
        }
        return p;
    }

    // 遍历以 node 节点为根的 Trie 树，找到所有键
    void traverse(TrieNode* node, string& path, vector<string>& res) {
        if (node == nullptr) {
            // 到达 Trie 树底部叶子结点
            return;
        }
        if (node->val != -1) {
            // 找到一个 key，添加到结果列表中
            res.push_back(path);
        }
        // 回溯算法遍历框架
        for (int c = 0; c < R; c++) {
            // 做选择
            path.push_back((char)c);
            traverse(node->children[c], path, res);
            // 撤销选择
            path.pop_back();
        }
    }

    // 遍历函数，尝试在「以 node 为根的 Trie 树中」匹配 pattern[i..]
    void traverse(TrieNode* node, string& path, const string& pattern, int i, vector<string>& res) {
        if (node == nullptr) {
            // 树枝不存在，即匹配失败
            return;
        }
        if (i == pattern.length()) {
            // pattern 匹配完成
            if (node->val != -1) {
                // 如果这个节点存储着 val，则找到一个匹配的键
                res.push_back(path);
            }
            return;
        }
        char c = pattern[i];
        if (c == '.') {
            // pattern[i] 是通配符，可以变化成任意字符
            for (int j = 0; j < R; j++) {
                path.push_back((char)j);
                traverse(node->children[j], path, pattern, i + 1, res);
                path.pop_back();
            }
        }
        else {
            // pattern[i] 是普通字符 c
            path.push_back(c);
            traverse(node->children[(int)c], path, pattern, i + 1, res);
            path.pop_back();
        }
    }

    // 函数定义：从 node 节点开始匹配 pattern[i..]，返回是否成功匹配
    bool hasKeyWithPattern(TrieNode* node, const string& pattern, int i) {
        if (node == nullptr) {
            // 树枝不存在，即匹配失败
            return false;
        }
        if (i == pattern.length()) {
            // 模式串走到头了，看看匹配到的是否是一个键
            return node->val != -1;
        }
        char c = pattern[i];
        // 没有遇到通配符
        if (c != '.') {
            // 从 node->children[c] 节点开始匹配 pattern[i+1..]
            return hasKeyWithPattern(node->children[(int)c], pattern, i + 1);
        }
        // 遇到通配符
        for (int j = 0; j < R; j++) {
            // pattern[i] 可以变化成任意字符，尝试所有可能，只要遇到一个匹配成功就返回
            if (hasKeyWithPattern(node->children[j], pattern, i + 1)) {
                return true;
            }
        }
        // 都没有匹配
        return false;
    }

public:
    ~TrieMap() {
        delete root;
    }

    // **** 增/改 ****

    // 在 map 中添加或修改键值对
    void put(const string& key, int val) {
        if (!containsKey(key)) {
            // 新增键值对
            _size++;
        }
        // 需要一个额外的辅助函数，并接收其返回值
        root = put(root, key, val, 0);
    }

    // **** 删 ****

    // 在 Map 中删除 key
    void remove(const string& key) {
        if (!containsKey(key)) {
            return;
        }
        // 递归修改数据结构要接收函数的返回值
        root = remove(root, key, 0);
        _size--;
    }

    // **** 查 ****

    // 搜索 key 对应的值，不存在则返回 -1
    int get(const string& key) {
        // 从 root 开始搜索 key
        TrieNode* x = getNode(root, key);
        if (x == nullptr || x->val == -1) {
            // x 为空或 x 的 val 字段为空都说明 key 没有对应的值
            return -1;
        }
        return x->val;
    }

    // 判断 key 是否存在在 Map 中
    bool containsKey(const string& key) {
        return get(key) != -1;
    }

    // 判断是和否存在前缀为 prefix 的键
    bool hasKeyWithPrefix(const string& prefix) {
        // 只要能找到一个节点，就是存在前缀
        return getNode(root, prefix) != nullptr;
    }

    // 在所有键中寻找 query 的最短前缀
    string shortestPrefixOf(const string& query) {
        TrieNode* p = root;
        // 从节点 node 开始搜索 key
        for (int i = 0; i < query.length(); i++) {
            if (p == nullptr) {
                // 无法向下搜索
                return "";
            }
            if (p->val != -1) {
                // 找到一个键是 query 的前缀
                return query.substr(0, i);
            }
            // 向下搜索
            char c = query[i];
            p = p->children[(int)c];
        }
        if (p != nullptr && p->val != -1) {
            // 如果 query 本身就是一个键
            return query;
        }
        return "";
    }

    // 在所有键中寻找 query 的最长前缀
    string longestPrefixOf(const string& query) {
        TrieNode* p = root;
        // 记录前缀的最大长度
        int max_len = 0;
        // 从节点 node 开始搜索 key
        for (int i = 0; i < query.length(); i++) {
            if (p == nullptr) {
                // 无法向下搜索
                break;
            }
            if (p->val != -1) {
                // 找到一个键是 query 的前缀，更新前缀的最大长度
                max_len = i;
            }
            // 向下搜索
            char c = query[i];
            p = p->children[(int)c];
        }
        if (p != nullptr && p->val != -1) {
            // 如果 query 本身就是一个键
            return query;
        }
        return query.substr(0, max_len);
    }

    // 搜索前缀为 prefix 的所有键
    vector<string> keysWithPrefix(const string& prefix) {
        vector<string> res;
        // 找到匹配 prefix 在 Trie 树中的那个节点
        TrieNode* x = getNode(root, prefix);
        if (x == nullptr) {
            return res;
        }
        // DFS 遍历以 x 为根的这棵 Trie 树
        string path = prefix;
        traverse(x, path, res);
        return res;
    }

    // 通配符 . 匹配任意字符
    vector<string> keysWithPattern(const string& pattern) {
        vector<string> res;
        string path;
        traverse(root, path, pattern, 0, res);
        return res;
    }

    // 判断是和否存在前缀为 prefix 的键
    bool hasKeyWithPattern(const string& pattern) {
        // 从 root 节点开始匹配 pattern[0..]
        return hasKeyWithPattern(root, pattern, 0);
    }

    int size() {
        return _size;
    }
};
