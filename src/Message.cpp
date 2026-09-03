#include "Message.hpp"


// Message = one turn in an actual back and forth conversation with LLM
// AKA this code is part of the dialogue and represents who is talking in 
// an AI conversation



Message::Message(MessageRole role, std::string text)
    : role_(role), text_(std::move(text)) {  // move text and copy trivial enum
}

bool Message::operator==(const Message& other) const {
    return role_ == other.role_ && text_ == other.text_;  // compare role and text
}

bool Message::operator!=(const Message& other) const {
    return !(*this == other);
}

MessageRole Message::role() const noexcept { return role_; }
const std::string& Message::text() const noexcept { return text_; }

void Message::setRole(MessageRole role) noexcept {
    role_ = role;  // trivial copy, enum is just an int under the hood
}

void Message::setText(std::string text) {
    text_ = std::move(text);  // move-assign
}

bool Message::empty() const noexcept {
    return text_.empty();  // depends only on text, not role


}

// messagerole is an enum class so == is native and no custom comparator needed
// default role (messagerole:user) and default empty are handles in the header
