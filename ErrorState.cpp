/* --------------------------------------------
 Description: This implementation file contains definitions for the ErrorState class which manages the error state of client code as well as encapsulates the last error message.
 ----------------------------------------------- */

#include <iostream>
#include <string.h>

#include "ErrorState.h"

using namespace std;

namespace AMA {
    
    // sets object to safe empty state
    void ErrorState::setEmpty() {
        errorMessage = nullptr;
    }
    
    // if address is nullptr, sets object to safe empty state
    ErrorState::ErrorState(const char* errorMessage) {
        if(errorMessage == nullptr) {
            setEmpty();
        } else {
            this->errorMessage = new char [strlen(errorMessage) + 1];
            strcpy(this->errorMessage, errorMessage);
        }
    }
    
    // deallocates memory that has been dynamically allocated by current object
    ErrorState::~ErrorState() {
        if(errorMessage != nullptr) {
            delete [] errorMessage;
        }
    }
    
    // clears messages stored in current object
    // initializes object to safe empty state
    void ErrorState::clear() {
        delete [] errorMessage;
        setEmpty();
    }
    
    // checks if object is in safe empty state
    bool ErrorState::isClear() const {
        return errorMessage == nullptr;
    }
    
    // deallocates memory for previously stored messages
    // allocates dynamic memory and copies string str to new allocated memory
    void ErrorState::message(const char* str) {
        clear();
        errorMessage = new char [strlen(str) + 1];
        strcpy(errorMessage, str);
    }
    
    // returns address of message stored in current object
    const char* ErrorState::message() const {
        return errorMessage;
    }
    
    // sends error state message to ostream ostr and returns reference to ostream ostr if message exists
    // if message does not exist, returns reference to ostream ostr
    std::ostream& operator<<(std::ostream& ostr, const ErrorState& em) {
        if(!em.isClear()) {
            ostr << em.message();
            return ostr;
        } else {
            return ostr;
        }
    }
}
