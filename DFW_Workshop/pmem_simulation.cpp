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

void persist (std::ofstream& fstm, Node* a, Node* b) {
    if (a == nullptr) {
        // missing key
        perror ("Bad persist\n");
        exit (0);
    }
    fstm << a->name << " " << a->val << " ";
    if (b == nullptr) {
        // missing value
        fstm << "NULL"
             << " "
             << "NULL";
    } else {
        fstm << b->name << " " << b->val << " ";
    }

    fstm << "\n";
}

void createLinkedlistWithBarrier (Node* head, int isCrash) {
    // Initial
    std::cout << "============ Node A ============" << std::endl;
    // 1. Create a node, deposit 100 dollors to the bank
    Node* A = new Node (100, "A");
    std::cout << "Create Node A" << std::endl;
    persist (pmem_simulation, A, nullptr);
    // 2. link head node to the Node A
    head->next = A;
    std::cout << "Link head to A" << std::endl;
    persist (pmem_simulation, head, A);
    // ============================================================
    std::cout << "============ Node B ============" << std::endl;
    // 1. Create a node B, deposit 200 dollors to the bank
    Node* B = new Node (200, "B");
    std::cout << "Create Node B" << std::endl;
    persist (pmem_simulation, B, nullptr);
    // 2. link Node B to the Node A
    B->next = A;
    std::cout << "Link B to  A" << std::endl;
    persist (pmem_simulation, B, A);
    // 3. link head node to the Node B
    head->next = B;
    std::cout << "Link head to B" << std::endl;
    persist (pmem_simulation, head, B);
    // ============================================================
    std::cout << "============ Node C ============" << std::endl;
    // 1. Create a node C, deposit 300 dollors to the bank
    Node* C = new Node (300, "C");
    std::cout << "Create Node C" << std::endl;
    persist (pmem_simulation, C, nullptr);
    // 2. link Node C to the Node B
    C->next = B;
    std::cout << "Link C to B" << std::endl;
    persist (pmem_simulation, C, B);

    // ============================================================
    // barrier! Always can make sure step3 happened after step2
    // ============================================================

    // 3. link head node to the Node C
    head->next = C;
    std::cout << "Link head to C" << std::endl;
    if (isCrash) {
        std::cout << ">>>> The system crashes <<<<\n";
        return;
    }
    persist (pmem_simulation, head, C);
}

void createLinkedlistWithoutBarrier (Node* head, int isCrash) {
    // Initial
    std::cout << "============ Node A ============" << std::endl;
    // 1. Create a node, deposit 100 dollors to the bank
    Node* A = new Node (100, "A");
    std::cout << "Create Node A" << std::endl;
    persist (pmem_simulation, A, nullptr);
    // 2. link head node to the Node A
    head->next = A;
    std::cout << "Link head to A" << std::endl;
    persist (pmem_simulation, head, A);
    // ============================================================
    std::cout << "============ Node B ============" << std::endl;
    // 1. Create a node B, deposit 200 dollors to the bank
    Node* B = new Node (200, "B");
    std::cout << "Create Node B" << std::endl;
    persist (pmem_simulation, B, nullptr);
    // 2. link Node B to the Node A
    B->next = A;
    std::cout << "Link B to  A" << std::endl;
    persist (pmem_simulation, B, A);
    // 3. link head node to the Node B
    head->next = B;
    std::cout << "Link head to B" << std::endl;
    persist (pmem_simulation, head, B);
    // ============================================================
    std::cout << "============ Node C ============" << std::endl;
    // 1. Create a node C, deposit 300 dollors to the bank
    Node* C = new Node (300, "C");
    std::cout << "Create Node C" << std::endl;
    persist (pmem_simulation, C, nullptr);

    // ============================================================
    // No barrier! create a situation that reverse the link order
    // ============================================================

    // 3. link head node to the Node C
    head->next = C;
    std::cout << "Link head to C" << std::endl;
    persist (pmem_simulation, head, C);
    // 2. link Node C to the Node B
    C->next = B;
    std::cout << "Link C to B" << std::endl;
    if (isCrash) {
        std::cout << ">>>> The system crashes <<<<\n";
        return;
    }
    persist (pmem_simulation, C, B);
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
    Node* head = new Node (-1, "head");
    persist (pmem_simulation, head, nullptr);
    pmem_simulation.open (pmem_name);
    pmem_simulation.clear ();
    createLinkedlistWithoutBarrier (head, true);
    pmem_simulation.close ();

    // Use for recovery
    readPmem ();
    Node* rhead = recoverFromPmem ();
    printMyAccount (rhead);
    return 1;
}