/* --------------------------------------------
 Description: This is the header file for Perishable.cpp. It derives the Perishable class from the Product class, and contains declarations.
 ----------------------------------------------- */

#ifndef AMA_PERISHABLE_H_
#define AMA_PERISHABLE_H_

#include "Date.h"
#include "Product.h"

namespace AMA {
    
    class Perishable : public Product {
        
        Date date;
        
    public:
        Perishable();
        Perishable(char type);
        std::fstream& store(std::fstream& file, bool newLine=true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        const Date& expiry() const;
        void setEmpty();
        
    };
    
}
#endif
