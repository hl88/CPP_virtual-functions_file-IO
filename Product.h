/* --------------------------------------------
 Description: This is the header file for Product.cpp. It contains declarations for instance variables, protected functions, public functions and helper functions.
 ----------------------------------------------- */

#ifndef Product_hpp
#define Product_hpp

#include <iostream>
#include "iProduct.h"

namespace AMA {
    
    const int max_sku_length = 7;
    const int max_name_length = 10;
    const int max_unit_length = 75;
    const float tax = .13;  
    
    class Product : public iProduct {
        
        // instance variables
        char type_;
        char sku_[max_sku_length + 1];
        char unit_[max_unit_length + 1];
        char* name_;
        int qty;
        int qtyNeeded_;
        double price_;
        
        bool isTaxed;
        std::string msg_;
        
    protected:
        void name(const char*);
        const char* name() const;
        double cost() const;
        void message(const char*);
        bool isClear() const;
        std::string message() const;

        
    public:
        void setEmpty();
        void init(const char* sku, const char* name_, const char* unit, int qty, bool isTaxed, double price, int qtyNeeded_);
        
        // zero-one argument constructor
        Product(char type = 'N');
        
        Product(const char* sku, const char* name_, const char* unit, int qty = 0, bool isTaxed = true, double price = 0, int qtyNeeded = 0);
        Product(const Product&);
        Product& operator=(const Product&);     // copy assignment operator
        ~Product();

        std::fstream& store(std::fstream& file, bool newLine=true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        
        bool operator==(const char*) const;
        double total_cost() const;
        void quantity(int);
        bool isEmpty() const;
        int qtyNeeded() const;
        int quantity() const;
        bool operator>(const char*) const;
        bool operator>(const Product&) const;
        int operator+=(int);
        
        const char* sku() const;
        const char* unit() const;
        bool taxed() const;
        double price() const;
        
        char type() const;      
        void type(char);
        
        bool operator>(const iProduct&) const;
        
    };
    
    // helper functions
    std::ostream& operator<<(std::ostream&, const iProduct&);
    std::istream& operator>>(std::istream&, iProduct&);
    double operator+=(double&, const iProduct&);
    
}


#endif
