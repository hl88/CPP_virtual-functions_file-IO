/* --------------------------------------------
 Description: This implementation file reads in a date object from the std::istream and outputs to std::ostream in the following format YYYY/MM/DD where YYYY represents the year, MM represents the month and DD represents the day.
 ----------------------------------------------- */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "Date.h"

namespace AMA {
        
    // number of days in month mon_ and year year_
    int Date::mdays(int mon, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    
    // sets the value for error state variable
    void Date::errCode(int errorCode) {
        errorState = errorCode;
    }

    // compares date stored in current object with date stored in another Date object
    void Date::setComparatorValue() {
        comparatorValue = year * 372 + month * 13 + day;
    }
    
    // sets object to safe empty state
    void Date::setSafeEmptyState() {
        year = 0;
        month = 0;
        day = 0;
        setComparatorValue();
    }

    // boolean that checks if object is in a safe empty state
    bool Date::isSafeEmptyState() const {
        return comparatorValue == 0;
    }

    // boolean that checks if year, month and day are valid
    // if not, sets error states
    bool Date::isValid()  {
        if (!(year >= min_year && year <= max_year)) {
            errorState = YEAR_ERROR;
        } else if (!(month >= 1 && month <= 12)) {
            errorState = MON_ERROR;
        } else if (!(day >= 1 && day <= mdays(month, year))) {
            errorState = DAY_ERROR;
        } else {
            errorState = NO_ERROR;
            return true;
        }
        return false;
    }

    // default constructor sets object to safe empty state, and sets error state
    Date::Date() {
        setSafeEmptyState();
        errorState = NO_ERROR;
    }
    
    // overloaded constructor that checks valid input for year, month and day
    // if input is not valid, sets error state and sets safe empty state
    // if input is valid, assigns values to current object
    Date::Date(int newYear, int newMonth, int newDay) {
        if (!(newYear > min_year && newYear < max_year)) {
            setSafeEmptyState();
            errorState = YEAR_ERROR;
        } else if (!(newMonth >= 1 && newMonth <= 12)) {
            setSafeEmptyState();
            errorState = MON_ERROR;
        } else if (!(newDay >= 1 && newDay <= mdays(newMonth, newYear))) {
            setSafeEmptyState();
            errorState = DAY_ERROR;
        } else {
            this->year = newYear;
            this->month = newMonth;
            this->day = newDay;
            setComparatorValue();
            errorState = NO_ERROR;
        }
    }
    
    // boolean that returns result in comparison between current object and date object passed in using ==
    bool Date::operator==(const Date& rhs) const {
        if(!this->isSafeEmptyState() && !rhs.isSafeEmptyState()) {
            return this->comparatorValue==rhs.comparatorValue;
        } else {
            return false;
        }
    }
    
    // boolean that returns result in comparison between current object and date object passed in using !=
    bool Date::operator!=(const Date& rhs) const {
        if(!this->isSafeEmptyState() && !rhs.isSafeEmptyState()) {
            return this->comparatorValue!=rhs.comparatorValue;
        } else {
            return false;
        }
    }
    
    // boolean that returns result in comparison between current object and date object passed in using <
    bool Date::operator<(const Date& rhs) const {
        if(!this->isSafeEmptyState() && !rhs.isSafeEmptyState()) {
            return this->comparatorValue<rhs.comparatorValue;
        } else {
            return false;
        }
    }
    
    // boolean that returns result in comparison between current object and date object passed in using >
    bool Date::operator>(const Date& rhs) const {
        if(!this->isSafeEmptyState() && !rhs.isSafeEmptyState()) {
            return this->comparatorValue>rhs.comparatorValue;
        } else {
            return false;
        }
    }
    
    // boolean that returns result in comparison between current object and date object passed in using <=
    bool Date::operator<=(const Date& rhs) const {
        if(!this->isSafeEmptyState() && !rhs.isSafeEmptyState()) {
            return this->comparatorValue<=rhs.comparatorValue;
        } else {
            return false;
        }
    }
    
    // boolean that returns result in comparison between current object and date object passed in using >=
    bool Date::operator>=(const Date& rhs) const {
        if(!this->isSafeEmptyState() && !rhs.isSafeEmptyState()) {
            return this->comparatorValue>=rhs.comparatorValue;
        } else {
            return false;
        }
    }
    
    // returns the value of error state
    int Date::errCode() const {
        return errorState;
    }
    
    // boolean that returns true if error state is not NO_ERROR
    bool Date::bad() const {
        return errorState != NO_ERROR;
    }
    
    // boolean that checks if the input is a digit
    bool Date::isDigit(char character) const {
        return character >= '0' && character <= '9';
    }

    // reads date from std::istream in YYYY?MM?DD? format
    // if input is not an integer, sets to error state
    // if input is valid, stores it into year, month, day
    std::istream& Date::read(std::istream& istr) {

        char ch;
        
        // extract from input stream one integer and store it into variable year
        // extraction continues until it reads a non-integer input
        istr >> year;
    
        // checks to make sure that user types in an integer
        if (istr.fail() == 1) {
            errorState = CIN_FAILED;
            return istr;
        }
        
        // extract from input stream one character and store it into variable ch
        istr >> ch;
        
        // if ch is not a '-' and not a '/' then sets to error state
        if (ch != '-' && ch != '/') {
            istr.setstate(std::ios::failbit);
            errorState = CIN_FAILED;
            return istr;
        }
        
        // extract from input stream one integer and store it into variable month
        // extraction continues until it reads a non-integer input
        istr >> month;
        
        // checks to make sure that user types in an integer
        if (istr.fail() == 1) {
            errorState = CIN_FAILED;
            return istr;
        }
        
        // extract from input stream one character and store it into variable ch
        istr >> ch;
        
        // if ch is not a '-' and not a '/' then sets to error state
        if (ch != '-' && ch != '/') {
            istr.setstate(std::ios::failbit);
            errorState = CIN_FAILED;
            return istr;
        }
        
        // extract from input stream one integer and store it into variable day
        // extraction continues until it reads a non-integer input
        istr >> day;
        
        // checks to make sure that user types in an integer
        if (istr.fail() == 1) {
            errorState = CIN_FAILED;
            return istr;
        }
        
        // if input is valid, sets the comparator value
        // if input is not valid, sets object to safe empty state
        if(isValid()) {
            setComparatorValue();
        } else {
            setSafeEmptyState();
        }
        
        return istr;
      
    }

    // writes date to std::ostream object in YYYY/MM/DD format
    std::ostream& Date::write(std::ostream& ostr) const {
        
        ostr << year << '/';
        
        // adds padding if month is < 10
        if (month<10) {
            ostr << '0';
        }
        
        ostr << month << '/';
        
        // adds padding if day is < 10
        if (day<10) {
            ostr << '0';
        }
        
        ostr << day;
        
        return ostr;
    }
    
    // overloading >> operator to read/ input new date
    std::istream& operator>>(std::istream& istr, Date& newDate) {
        return newDate.read(istr);
    }
    
    // overloading << operator to write/ output new date
    std::ostream& operator<<(std::ostream& ostr, const Date& newDate){
        return newDate.write(ostr);
    }
    
    // overloaded = operator that copies day, month and date to current object
    Date& Date::operator=(const Date& rhs) {
        this->day = rhs.day;
        this->month = rhs.month;
        this->year = rhs.year;
        return *this;
    }

}









