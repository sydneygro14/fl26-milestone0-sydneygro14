#include "Document.hpp"
#include <fstream> // needed for reading files
#include <sstream> // needed for buffering file contents


Document::Document(std::string title, std::string contents) {
    : title_(std::move(title)), contents_(std::move(contents)) {
        // std::move avoids making extra copies
        //title/contents are local copies inside the function
    }
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
    std::ifstream file(path, std::ios::binanry); // open file

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
    : path.substr(lastSlash + 1) // slash found, take everything after

// NOW, update object state (no failures)
sourcePath_ = path;
title_ = filename;
contents_ = buffer.str();
return true;

}

const std::string& Document::title() const noexcept {
    // TODO

}

const std::string& Document::sourcePath() const noexcept {
    // TODO

}

const std::string& Document::contents() const noexcept {
    // TODO
  
}

void Document::setTitle(std::string title) {
    
  
}

std::size_t Document::characterCount() const noexcept {
    // TODO
    
}

bool Document::empty() const noexcept {
    // TODO
   
}
