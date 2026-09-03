#include "Document.hpp"
#include <fstream> // needed for reading files
#include <sstream> // needed for buffering file contents


// this code's function is to hold a display title, the filesystem path, and its raw
// text contents and if reading the file fails, the document remains unchanged



Document::Document(std::string title, std::string contents)
    : title_(std::move(title)), contents_(std::move(contents)) {
        // std::move avoids making extra copies
        //title/contents are local copies inside the function
}

bool Document::operator==(const Document& other) const {
    return title_ == other.title_ && sourcePath_ == other.sourcePath_ 
    && contents_ == other.contents_;
// two docs are only equal if all three of these match
}

bool Document::operator!=(const Document& other) const {
    return !(*this == other); // not matching


}

bool Document::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary); // open file

    if (!file.is_open()) {  // if load fails, contents remain untouched
        return false;
    }

// read whole file into a local buffer
std::ostringstream buffer;
buffer << file.rdbuf();

// find filename in path
std::size_t lastSlash = path.find_last_of("/\\"); // have to include both in case linux/mac vs windows slash
std::string filename = (lastSlash == std::string::npos)
    ? path // no slash found, then whole path is filename (? is another way for if else)
    : path.substr(lastSlash + 1); // slash found, take everything after

// NOW, update object state (no failures)
sourcePath_ = path;
title_ = filename;
contents_ = buffer.str();
return true;

}

const std::string& Document::title() const noexcept {
    return title_;

}

const std::string& Document::sourcePath() const noexcept {
    return sourcePath_;

}

const std::string& Document::contents() const noexcept {
    return contents_;
  
}

void Document::setTitle(std::string title) {
    title_ = std::move(title); // move, avoid extra copy
  
}

std::size_t Document::characterCount() const noexcept {
    return contents_.size(); // 0(1), std:: string tracks its own lenght
    
}

bool Document::empty() const noexcept {
    return contents_.empty();
 // defined purely by contents as the spec says to   
}


// - load() reads into LOCAL variables (file, bugger, filename) before
// touching anything. This gaurentees failure leaves the doc unchanged
// all string parameters are taken by value and moved into members
