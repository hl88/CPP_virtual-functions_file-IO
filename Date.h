/* --------------------------------------------
 Description: This is the header file for Date.cpp. It contains definitions for macro directives, and declarations for instance variables, private functions, public functions, and helper functions.
 ----------------------------------------------- */


#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>


namespace AMA {

// macro directive definitions
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
    
    const int min_year = 2000;
    const int max_year = 2030;
    
    class Date {
        
        // instance variable definitions
        int year;
        int month;
        int day;
        
        int comparatorValue;
        int errorState;
        
        // private function declarations
        int mdays(int month, int year) const;
        void errCode(int errorCode);
        void setComparatorValue();
        void setSafeEmptyState();
        bool isSafeEmptyState() const;
        bool isDigit(char) const;
        bool isValid();
        
    public:
        
        // public function declarations
        Date();
        Date(int year, int month, int day);
        
        bool operator==(const Date& rhs) const;
        bool operator!=(const Date& rhs) const;
        bool operator<(const Date& rhs) const;
        bool operator>(const Date& rhs) const;
        bool operator<=(const Date& rhs) const;
        bool operator>=(const Date& rhs) const;
        
        Date& operator=(const Date& rhs);
                
        int errCode() const;
        bool bad() const;

        std::istream& read(std::istream& istr);
        std::ostream& write(std::ostream& ostr) const;
        
    };
   
    // helper function declarations
    std::istream& operator>>(std::istream&, Date&);
    std::ostream& operator<<(std::ostream&, const Date&);
    
}

#endif
