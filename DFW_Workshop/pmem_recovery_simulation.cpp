#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

class Node;
std::ofstream pmem_simulation;
const std::string pmem_name = "pmem.txt";
std::vector<std::vector<std::string>> read_from_pmem;
std::unordered_map<std::string, Node*> recovered_node;

class Node {
public:
    Node* next;
    int val;
    std::string name;
    Node (int val, std::string name) : val (val), next (nullptr), name (name) {}
};

void printMyAccount (Node* head) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->val == -1) {
            // this is head node
            std::cout << "Head -> ";
        } else {
            std::cout << cur->val << " -> ";
        }
        cur = cur->next;
    }
    std::cout << "nullptr";
    std::cout << std::endl;
}

Node* recoverFromPmem () {
    Node* head = new Node (-1, "head");
    recovered_node[head->name] = head;
    for (auto& vec : read_from_pmem) {
        std::string key, value;
        int kval, vval;
        key = vec[0];
        kval = std::stoi (vec[1]);
        value = vec[2];
        if (vec[3] == "NULL") {
            vval = 0;
        } else {
            vval = std::stoi (vec[3]);
        }

        Node* keyNode = nullptr;
        Node* valNode = nullptr;
        if (recovered_node.count (key) == 0) {
            // not recovered, ready to recover
            keyNode = new Node (kval, key);
            recovered_node[key] = keyNode;
        } else {
            // already recovered
            keyNode = recovered_node[key];
        }
        if (value != "NULL") {
            if (recovered_node.count (value) == 0) {
                // not recovered, ready to recover
                valNode = new Node (vval, value);
                recovered_node[value] = valNode;
            } else {
                // already recovered
                valNode = recovered_node[value];
            }
        }
        keyNode->next = valNode;
    }
    return head;
}

void readPmem () {
    std::string line;
    std::ifstream rpmem (pmem_name);
    if (rpmem.is_open ()) {
        while (getline (rpmem, line)) {
            std::string delimiter = " ";
            size_t last = 0;
            size_t next = 0;
            std::string key, kval, value, vval;
            next = line.find (delimiter, last);
            key = line.substr (last, next - last);

            last = next + 1;
            next = line.find (delimiter, last);
            kval = line.substr (last, next - last);

            last = next + 1;
            next = line.find (delimiter, last);
            value = line.substr (last, next - last);

            last = next + 1;
            next = line.find (delimiter, last);
            vval = line.substr (last, next - last);

            // std::cout << "[READ]" << key << " " << kval << " " << value << " " << vval;

            read_from_pmem.push_back ({key, kval, value, vval});
        }
        rpmem.close ();
        std::cout << "======== Read from Pmem ========" << std::endl;
    } else {
        std::cout << "Unable to open pmem\n";
    }
}

int main () {
    // ============================================
    // Use for recovery
    readPmem ();
    Node* rhead = recoverFromPmem ();
    printMyAccount (rhead);
    // ============================================
    return 1;
}