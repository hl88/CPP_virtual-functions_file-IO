/* --------------------------------------------
 Description: This is the header file for ErrorState.cpp. It contains declarations for instance variable, public functions, and helper function.
 ----------------------------------------------- */

#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include <iostream>
#include <stdio.h>

using namespace std;

namespace AMA {
    
    class ErrorState {
        
        // instance variable
        char* errorMessage;
        
    public:
        
        // public function declarations
        explicit ErrorState(const char* errorMessage = nullptr);
        ErrorState(const ErrorState& em) = delete;
        ErrorState& operator=(const ErrorState& em) = delete;
        virtual ~ErrorState();
        
        void setEmpty();
        void clear();
        bool isClear() const;
        void message(const char* str);  // setter
        const char* message() const;   // getter
        
    };
    
    // helper function declaration
    std::ostream& operator<<(std::ostream& ostr, const ErrorState& em);
    
}



#endif 
