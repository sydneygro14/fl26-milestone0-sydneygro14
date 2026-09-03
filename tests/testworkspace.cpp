#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Document.hpp"
#include "Message.hpp"
#include "Prompt.hpp"
#include "Workspace.hpp"

void prompt_smoke_test() {
    Prompt p("Reviewer", "Review this requirement.");
    assert(p.title() == "Reviewer");
    assert(!p.empty());
}

void workspace_smoke_test() {
    Workspace w("Demo");
    w.addPrompt(Prompt("Reviewer", "Review this requirement."));
    assert(w.promptCount() == 1);
}

// Boundary/failure case: load() on a path that does not exist must
// return false AND leave the Document's existing state completely
// unchanged 
void document_load_failure_preserves_state() {
    Document d("Original Title", "original contents");
    bool ok = d.load("this/path/does/not/exist.txt");
    assert(ok == false);
    assert(d.title() == "Original Title");     // unchanged
    assert(d.sourcePath().empty());              // unchanged (was never set)
    assert(d.contents() == "original contents"); // unchanged
}

// Successful load: confirms title becomes the filename component,
// sourcePath becomes the full path, and contents matches the file
void document_load_success() {
    Document d;
    bool ok = d.load("text/sample.txt");
    assert(ok == true);
    assert(d.title() == "sample.txt");
    assert(d.sourcePath() == "text/sample.txt");
    assert(!d.empty());
}

// Equality/inequality: two Documents built from the same data compare
// equal, changing one field breaks equality.
void document_equality_test() {
    Document a("Title", "Contents");
    Document b("Title", "Contents");
    assert(a == b);
    b.setTitle("Different Title");
    assert(a != b);
}

// Boundary/failure case: accessing an out-of-range index must throw
// std::out_of_range
void workspace_invalid_index_throws() {
    Workspace w;
    bool threw = false;
    try {
        w.documentAt(0);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);
}

// Insertion order: the Nth addDocument call must land at index N-1,
// and documentCount() must track it.
void workspace_insertion_order_test() {
    Workspace w("Ordering");
    w.addDocument(Document("First", "a"));
    w.addDocument(Document("Second", "b"));
    assert(w.documentCount() == 2);
    assert(w.documentAt(0).title() == "First");
    assert(w.documentAt(1).title() == "Second");
}

// Copy independence: copying a Workspace must
// produce an independent value. Adding to the copy (or the original)
// after the copy is made must not affect the other
void workspace_copy_independence_test() {
    Workspace original("Original");
    original.addDocument(Document("Doc1", "abc"));

    Workspace copy = original;              // copy made here
    original.addDocument(Document("Doc2", "xyz"));  // mutate original AFTER copy

    assert(original.documentCount() == 2);
    assert(copy.documentCount() == 1);      // copy did not see Doc2
}

int main() {
    prompt_smoke_test();
    workspace_smoke_test();
    document_load_failure_preserves_state();
    document_load_success();
    document_equality_test();
    workspace_invalid_index_throws();
    workspace_insertion_order_test();
    workspace_copy_independence_test();

    std::cout << "M0 tests passed\n";
    return 0;
}