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

int main () {
    // If you want to write the data to file, please comment the recovery part
    // If you want to recover the data from file, please comment the write data part

    // ============================================
    // This code block for writing the data to the file
    Node* head = new Node (-1, "head");
    persist (pmem_simulation, head, nullptr);
    pmem_simulation.open (pmem_name);
    pmem_simulation.clear ();

    // manually reverse the linking order.
    createLinkedlistWithoutBarrier (head, false);

    // Do not reverse the linking order
    // createLinkedlistWithBarrier (head, true);
    pmem_simulation.close ();
    // ============================================
    return 1;
}