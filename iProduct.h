/* --------------------------------------------
 Description: This header file is the interface to the hierarchy. It contains virtual functions and helper functions.
 ----------------------------------------------- */

#ifndef _IPRODUCT_H_
#define _IPRODUCT_H_

#include <fstream>

namespace AMA {
    
    class iProduct {
        
    public:
        
        // stores the record to file
        virtual std::fstream& store(std::fstream& file, bool newLine=true) const = 0;
        
        // loads the record from file
        virtual std::fstream& load(std::fstream& file) = 0;
        
        // inserts record for current object into ostream object
        virtual std::ostream& write(std::ostream& os, bool linear) const = 0;
        
        //  extracts record for the current object from istream object
        virtual std::istream& read(std::istream& is) = 0;
        
        // compares stock unit to the string that's passed in
        virtual bool operator==(const char*) const = 0;
        
        // returns the cost of a single unit with taxes included
        virtual double total_cost() const = 0;
        
        // returns name of object
        virtual const char* name() const = 0;
        
        // sets number of units available
        virtual void quantity(int) = 0;
        
        // returns number of units that are needed
        virtual int qtyNeeded() const = 0;
        
        // returns units that are currently available
        virtual int quantity() const = 0;
        
        // returns updated number of units currently available
        virtual int operator+=(int) = 0;
        
        // returns true if current object is greater than referenced object
        virtual bool operator>(const iProduct&) const = 0;
        
    };
    
    // helper functions
    
    // inserts the iProduct record for the referenced object into ostream object
    std::ostream& operator<<(std::ostream&, const iProduct&);
    
    // extracts the iProduct record for the referenced object from istream object
    std::istream& operator>>(std::istream&, iProduct&);
    
    // adds total cost of iProduct object to the double received
    // returns the updated value of the double
    double operator+=(double&, const iProduct&);
    
    // returns the address of Product object
    iProduct* CreateProduct();
    
    // returns the address of Perishable object
    iProduct* CreatePerishable();
    
}

#endif

