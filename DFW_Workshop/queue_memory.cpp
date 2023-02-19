// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2015-2020, Intel Corporation */

/*
 * queue.cpp -- queue example implemented using pmemobj cpp bindings
 *
 * Please see pmem.io blog posts for more details.
 */

#include <sys/stat.h>

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj_cpp_examples_common.hpp>
#include <stdexcept>
#include <string>

#define LAYOUT "queue"

/* available queue operations */
enum queue_op {
    UNKNOWN_QUEUE_OP,
    QUEUE_PUSH,
    QUEUE_POP,
    QUEUE_SHOW,

    MAX_QUEUE_OP,
};

/* queue operations strings */
const char* ops_str[MAX_QUEUE_OP] = {"", "push", "pop", "show"};

/*
 * parse_queue_op -- parses the operation string and returns matching queue_op
 */
queue_op parse_queue_op (const char* str) {
    for (int i = 0; i < MAX_QUEUE_OP; ++i)
        if (strcmp (str, ops_str[i]) == 0) return (queue_op)i;

    return UNKNOWN_QUEUE_OP;
}

/*
 * Persistent memory list-based queue
 *
 * A simple, not template based, implementation of queue using
 * libpmemobj C++ API. It demonstrates the basic features of persistent_ptr<>
 * and p<> classes.
 */
class pmem_queue {
    /* entry in the list */
    struct pmem_entry {
        pmem_entry* next;
        int value;
    };

public:
    /*
     * Inserts a new element at the end of the queue.
     */
    void push (uint64_t value) {
        auto start = std::chrono::high_resolution_clock::now ();
        pmem_entry* n = new pmem_entry ();
        n->value = value;
        n->next = nullptr;
        if (head == nullptr && tail == nullptr) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }

        auto stop = std::chrono::high_resolution_clock::now ();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds> (stop - start);
        std::cout << duration.count () << " nanoseconds" << std::endl;
    }

    void show (void) const {
        for (auto n = head; n != nullptr; n = n->next) std::cout << n->value << std::endl;
    }

private:
    pmem_entry* head;
    pmem_entry* tail;
};

int main (int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << "[push [value]|pop|show]" << std::endl;
        return 1;
    }

    queue_op op = parse_queue_op (argv[1]);

    pmem_queue* q = new pmem_queue ();

    switch (op) {
        case QUEUE_PUSH:
            try {
                q->push (std::stoull (argv[2]));
            } catch (const std::runtime_error& e) {
                std::cerr << "Exception: " << e.what () << std::endl;
                return 1;
            }
            break;
        default:
            std::cerr << "Invalid queue operation" << std::endl;
            return 1;
    }
    q->show ();
    return 0;
}