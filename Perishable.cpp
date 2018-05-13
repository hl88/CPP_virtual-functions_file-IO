/* --------------------------------------------
 Description: This implementation file contains definitions for the Perishable class which encapsulates information for perishable products.
 It stores a single file record, extracts data fields for a single file record, outputs data to ostream, and populates the current object with data extracted from istream.
 ----------------------------------------------- */

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include "Perishable.h"


namespace AMA {

    // calls constructor in Product and sets type to 'P'
    Perishable::Perishable() : Product('P') {

    }
    
    // stores a single file record for the current object
    std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
        Product::store(file, false);
        file << ',' << date;
        if(newLine) {
            file << std::endl;
        }
        return file;
    }
    
    // extracts data fields for a single file record from the fstream object
    std::fstream& Perishable::load(std::fstream& file) {
        
        // if fail, sets failbit and sets object to safe empty state
        if (file.fail()) {
            file.setstate(std::ios::failbit);
            Product::setEmpty();
            return file;
        }
        
        // calls load() function from Product
        Product::load(file);
        
        // calls read() function on date object
        date.read(file);
        return file;
    }
    
    // if current object is not in an error or safe empty state, inserts expiry date into ostream object
    // if linear is false, function adds new line character followed by the string “Expiry date: "
    std::ostream& Perishable::write(std::ostream& os, bool linear) const {
        
        if(message().length() > 0) {
            os << message();
        } else {
            Product::write(os, linear);
            
            if(linear) {
                os << date;
            } else {
                os << '\n' << " Expiry date: " << date;  //calls date.write()
            }

        }
        return os;
    }
    
    // populates the current object with data extracted from istream
    std::istream& Perishable::read(std::istream& is) {

        Product::read(is);
                
        char discard[30];
        
        // discards semicolon
        is.getline(discard, 30, ':');
        
        // discards space
        is.ignore(1);
        
        // creates temporary date object
        Date dateTemp;
        
        // extracts date from is and stores it into temporary date object
        is >> dateTemp;
        
//        is.ignore(1000, '\n');
        
        if(dateTemp.bad()) {
            
            is.setstate(std::ios::failbit);
            
            // sets error messages
            if(dateTemp.errCode() == CIN_FAILED) {
                message("Invalid Date Entry");
            } else if(dateTemp.errCode() == YEAR_ERROR) {
                message("Invalid Year in Date Entry");
            } else if(dateTemp.errCode() == MON_ERROR) {
                message("Invalid Month in Date Entry");
            } else if (dateTemp.errCode() == DAY_ERROR) {
                message("Invalid Day in Date Entry");
            }
        } else {
            date = dateTemp;
        }
        
        return is;

    }
    
    // returns expiry date
    const Date& Perishable::expiry() const {
        return date;
    }

}
