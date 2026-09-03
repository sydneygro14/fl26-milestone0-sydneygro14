#include "Prompt.hpp"

// Prompt is a small value type that is a reusable named block of instruction
// text for later AI-assisted work. In m0, it only holds data and doesn't send anything
// to a llm


Prompt::Prompt(std::string title, std::string text)
    : title_(std::move(title)),  // title's heap buffer pointer transferred into title_
      text_(std::move(text)) {   // text's heap buffer pointer transferred into text_
}

bool Prompt::operator==(const Prompt& other) const {
    return title_ == other.title_  // char-by-char string comparison
        && text_ == other.text_;   // char-by-char string comparison
}

bool Prompt::operator!=(const Prompt& other) const {
    return !(*this == other); // negates bool returned by the operator==
}

const std::string& Prompt::title() const noexcept { 
    return title_; 
}  // reference, not a copy

const std::string& Prompt::text() const noexcept { // reference, no copy
    return text_;
    
 }    

void Prompt::setTitle(std::string title) {
    title_ = std::move(title);  // title's old buffer freed, new one moved in

}

void Prompt::setText(std::string text) {
    text_ = std::move(text); 

}

bool Prompt::empty() const noexcept {
    return text_.empty();  // title_ deliberately excluded 
    // // matches Message's empty() pattern
}

// - Prompt and Message share an identical shape (title/role + text, with
//   empty() gated only on text). No shared base class exists because the
//   spec defines them as independent values. 