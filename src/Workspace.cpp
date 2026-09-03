#include "Workspace.hpp"

// Workspace is the container type for m0, it represents one named 
// work session and owns three private collections
// Later it will be the central objects that other subsystems operate on like
// UI and processing

Workspace::Workspace(std::string name)
    : name_(std::move(name)) {
    // name's buffer pointer is moved into name_. documents_, prompts_, and
    // messages_ are NOT listed in this initializer list
}

bool Workspace::operator==(const Workspace& other) const {
    return name_ == other.name_                // std::string comparison
        && documents_ == other.documents_       
        && prompts_ == other.prompts_           
        && messages_ == other.messages_;        
    // std::vector::operator== first compares this->size() to other.size();
    // if they differ, it returns false immediately (O(1), no elements touched
    // If sizes match, it compares element[0] to element[0], etc. in that exact index order, calling THAT element  type's own operator== each time
}


bool Workspace::operator!=(const Workspace& other) const {
    return !(*this == other);  // negates operator=='s result
}

const std::string& Workspace::name() const noexcept { 
    return name_; }  // reference to name_, zero-copy

void Workspace::setName(std::string name) {
    name_ = std::move(name);  // name_'s old buffer released and name's buffer pointer moved in
}


void Workspace::addDocument(Document document) {
    documents_.push_back(std::move(document));
    // push_back constructs a new element at index documents_.size(), increments documents_'s size by 1
    //  If documents capacity was already full, push_back first allocates a new, larger buffer, move-constructs all EXISTING elements in, 
    //destroys the old elements, and frees the old buffer 


}


void Workspace::addPrompt(Prompt prompt) {
    prompts_.push_back(std::move(prompt));  // adding prompts_
}
void Workspace::addMessage(Message message) {
    messages_.push_back(std::move(message));  // adding messages_
}


std::size_t Workspace::documentCount() const noexcept {
     return documents_.size(); 
}

std::size_t Workspace::promptCount() const noexcept { 
    return prompts_.size(); 
}

std::size_t Workspace::messageCount() const noexcept {
     return messages_.size();
}


Document& Workspace::documentAt(std::size_t index) { 
    return documents_.at(index);
 } // .at(index) first checks (index < documents_.size()); if false, it throws
// std::out_of_range(),  if true, it returns a reference to
// the Document object stored at that index, bu still no copy is made.



const Document& Workspace::documentAt(std::size_t index) const { return documents_.at(index); }
// the `const` means the compiler selects THIS version when called through



Prompt& Workspace::promptAt(std::size_t index) { 
    return prompts_.at(index); 
}

const Prompt& Workspace::promptAt(std::size_t index) const { 
    return prompts_.at(index); 
}

Message& Workspace::messageAt(std::size_t index) { 
    return messages_.at(index); 
}
const Message& Workspace::messageAt(std::size_t index) const { 
    return messages_.at(index); 
}


// the compiler automatically picks which doc/prompt/message to use based on whether the workspace instance
// // being called is const 

// also push back vector runs out of room to copy everything occasionally but happens rarely enough
// so the average cost is still O(1)


