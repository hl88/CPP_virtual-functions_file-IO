/* --------------------------------------------
 Description: This implementation file contains definitions for the Product class which encapsulates information for products. It provides information on sku, unit, price, tax, quantity on hand and quantity needed.
 ----------------------------------------------- */

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <string>
#include "Product.h"

namespace AMA {
    
    // stores name in dynamically allocated memory & replaces any name previously stored
    void Product::name(const char* nm) {
        
        // deallocates name_ memory
        delete [] name_;
        
        if(nm == nullptr) {
            
            // allocates memory for one character
            name_ = new char [1];
            
            // points to empty string
            name_[0] = '\0';
            
        } else {
            
            // allocates memory for name_
            name_ = new char [max_name_length + 1];
            
            // copies nm into name_
            strncpy(name_, nm, max_name_length);
            
            // makes sure the string name terminates with null character
            this->name_[max_name_length] = '\0';
            
        }
    }
    
    // returns the name of the product
    const char* Product::name() const {
        if(name_[0] == '\0') {
            return nullptr;
        } else {
            return name_;
        }
    }
    
    // returns the price of a single item plus any applicable tax
    double Product::cost() const {
        if(isTaxed) {
            return price_ * (1 + tax);
        } else {
            return price_;
        }
    }
    
    // returns error message and stores message in ErrorState object
    void Product::message(const char* msg){
        msg_ = msg;
    }
    
    std::string Product::message() const {
        return msg_;
    }
    
    // sets object to safe empty state
    void Product::setEmpty() {
        
        // allocates memory for one character
        name_ = new char [1];
        
        sku_[0] = '\0';
        unit_[0] = '\0';
        name_[0] = '\0';
        qty = 0;
        qtyNeeded_ = 0;
        price_ = 0.0;
    }
    
    // copies over type and sets object to safe empty state
    Product::Product(char type) {
        this->type_ = type;
        setEmpty();
    }
    
    // initializes object and copies values to current object
    void Product::init(const char* sku, const char* name_, const char* unit, int qty, bool isTaxed, double price, int qtyNeeded_) {
        
        this->name_ = new char [strlen(name_) + 1];
        
        strncpy(this->sku_, sku, max_sku_length);
        strncpy(this->name_, name_, max_name_length);
        strncpy(this->unit_, unit, max_unit_length);
        
        this->sku_[max_sku_length] = '\0';
        this->name_[max_name_length] = '\0';
        this->unit_[max_unit_length] = '\0';
        
        
        this->qty = qty;
        this->isTaxed = isTaxed;
        this->price_ =  price;
        this->qtyNeeded_ = qtyNeeded_;
    }
    
    // overloaded constructor that initializes the object and copies values to the current object
    Product::Product(const char* sku, const char* name_, const char* unit, int qty, bool isTaxed, double price, int qtyNeeded_) {
        
        if(sku == nullptr || name_ == nullptr || unit == nullptr || qty <0 || price < 0 || qtyNeeded_ < 0) {
            setEmpty();
        } else {
            init(sku, name_, unit, qty, isTaxed, price, qtyNeeded_);
        }
        
    }
    
    // copies object referenced to current object
    Product::Product(const Product& prd) {
        init(prd.sku_, prd.name_, prd.unit_, prd.qty, prd.isTaxed, prd.price_, prd.qtyNeeded_);
    }
    
    // copy assignment operator replaces current object with a copy of the object referenced
    Product& Product::operator=(const Product& src) {
        if(this != &src) {
            delete [] name_;
            init(src.sku_, src.name_, src.unit_, src.qty, src.isTaxed, src.price_, src.qtyNeeded_);
        }
        return *this;
    }
    
    // destructor - deallocates memory that has been dynamically allocated
    Product::~Product() {
        delete [] name_;
    }
    
    // inserts into fstream object the character that identifies the product type and the data for current object
    std::fstream& Product::store(std::fstream& file, bool newLine) const {
        file << type_ << ',' << sku_ << ',' << name_ << ',' << unit_ << ',' << taxed() << ',' << price_ << ',' << qty << ',' << qtyNeeded_;
        if(newLine) {
            file << std::endl;
        }
        return file;
    }
    
    // extracts fields for a single record from fstream object
    std::fstream& Product::load(std::fstream& file) {
        
        // deallocates dynamic memory
        delete [] name_;
        
        // gets sku_
        file.getline(sku_, max_sku_length, ',');
        
        if (file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }
        
        // creates temporary object
        char temp[max_name_length + 1];
        
        temp[max_name_length] = '\0';
        
        file.getline(temp, max_name_length, ',');
        
        if (file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }
        
        // gets unit_
        file.getline(unit_, max_unit_length, ',');
        
        if (file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }
        
        int isTaxedInt;
        
        // inserts taxable
        file >> isTaxedInt;
        
        file.ignore(1);
        
        if (isTaxedInt == 1) {
            isTaxed = true;
        } else if(isTaxedInt == 0) {
            isTaxed = false;
        }
        
        if ((isTaxedInt != 1 && isTaxedInt != 0) || file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }

        // inserts into price_ from file
        file >> price_;
        file.ignore(1);

        if (file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }
        
        // inserts into qty from file
        file >> qty;
        file.ignore(1);

        if (file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }
        
        // inserts into qtyNeeded_ from file
        file >> qtyNeeded_;
        file.ignore(1); // ignores comma

        if (file.fail()) {
            file.setstate(std::ios::failbit);
            setEmpty();
            return file;
        }
        
        unsigned long length = strlen(temp);
        
        name_ = new char[length + 1];
        
        // copies temporary object into currect object
        strncpy(name_, temp, length);
        
        name_[length] = '\0';
        
        return file;
        
    }
    
    // inserts data fields for current object into ostream object separated by '|'
    std::ostream& Product::write(std::ostream& os, bool linear) const {
        
        if(message().length() > 0) {
            os << message();
            return os;
        }
        
        
        // if bool paramter is true
        if(linear) {
            
            // inserts sku_ into ostream object
            os.width(max_sku_length);
            os << std::left << sku_ << '|';
            
            // inserts name_ into ostream object
            os.width(20);
            os << std::left << name_  << '|';
            
            // inserts cost into ostream object
            os.width(7);
            os << std::fixed;
            os << std::setprecision(2);
            os << std::right << cost() << '|';
            
            // inserts qyt into ostream object
            os.width(4);
            os << qty << '|';
            
            // inserts unit_ into ostream object
            os.width(10);
            os << std::left << unit_ << '|';
            os << std::right;
            
            // inserts qytNeeded_ into ostream object
            os.width(4);
            os << qtyNeeded_ << '|';
            
        // if bool parameter is false
        } else {
            os << " Sku: " << sku_ << std::endl;
            os << " Name (no spaces): " << name_ << std::endl;
            os << " Price: " << price_ << std::endl;
            if(isTaxed) {
                os << " Price after tax: " << total_cost() << std::endl;
            } else {
                os << " Price after tax: N/A" << std::endl;
            }
            os << " Quantity on Hand: " << qty << " " << unit_ << std::endl;
            os << " Quantity needed: " << qtyNeeded_;
        }
        
        return os;
    }
    
    // extracts data field for current object
    std::istream& Product::read(std::istream& is) {
        
        // clears out error
        message("");
        
        char sku[max_sku_length];
        char unit[max_unit_length];
        std::string name_;
        int qty;
        int qtyNeeded_;
        double price;
        
        char discard[20];
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts sku from is and stores it
        is >> sku;
        
        if (is.fail()) {
            message("Invalid Sku Entry");
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts name_ from is and stores it
        is >> name_;
        
        if (is.fail()) {
            message("Invalid Name Entry");
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts unit from is and stores it
        is >> unit;
        
        if (is.fail()) {
            message("Invalid Unit Entry");
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        // flag for whether item is taxed
        char answer;
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts answer from is and stores it
        is >> answer;
        
        if(answer == 'y' || answer == 'Y') {
            isTaxed = true;
        } else if(answer == 'n' || answer == 'N') {
            isTaxed = false;
        } else {
            message("Only (Y)es or (N)o are acceptable");
            
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts price from is and stores it
        is >> price;
        
        if (is.fail()) {
            message("Invalid Price Entry");
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts qty from is and stores it
        is >> qty;
        
        if (is.fail()) {
            message("Invalid Quantity Entry");
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        // discards semicolon
        is.getline(discard, 20, ':');
        
        // discards space
        is.get();
        
        // extracts qtyNeeded_ from is and stores it
        is >> qtyNeeded_;
        
        is.ignore(1);
        
        if (is.fail()) {
            message("Invalid Quantity Needed Entry");
            is.setstate(std::ios::failbit);
            setEmpty();
            return is;
        }
        
        delete [] this->name_;
        
        init(sku, name_.c_str(), unit, qty, isTaxed, price, qtyNeeded_);
        
        return is;
    }
    
    // returns if string is identical to sku of current object
    bool Product::operator==(const char* str) const {
        return this->sku_ == str;
    }
    
    // returns total cost of all items on hand including taxes
    double Product::total_cost() const {
        return cost() * qty;
    }
    
    // resets number of units on hand to number received
    void Product::quantity(int unit) {
        this->qty = unit;
    }
    
    // returns true if object is in a safe empty state
    bool Product::isEmpty() const {
        return  type_ == '\0' &&
        sku_[0] == '\0' &&
        unit_[0] == '\0' &&
        name_ == nullptr &&
        qty == 0 &&
        qtyNeeded_ == 0 &&
        price_ == 0.0;
    }
    
    // returns number of units of product that are needed
    int Product::qtyNeeded() const {
        return qtyNeeded_;
    }
    
    // returns number of untis of product that are on hand
    int Product::quantity() const {
        return qty;
    }
    
    // returns true if sku of current object is greater than string stored at received address
    bool Product::operator>(const char* sku) const {
        return strcmp(this->sku_, sku) > 0;
    }
    
    // returns true if name of current object is greater than name of the referenced object
    bool Product::operator>(const iProduct& src) const {
        return strcmp(this->name(), src.name()) > 0;
    }
    
    // returns the updated number of units on hand
    // if integer received is positive, function adds it to quantity on hand
    int Product::operator+=(int qty) {
        if(qty > 0) {
            this->qty += qty;
        }
        return this->qty;
    }
    
    // returns reference to ostream object
    std::ostream& operator<<(std::ostream& ostr, const iProduct& src) {
        return src.write(ostr, true);
        
    }
    
    // returns reference to istream object
    std::istream& operator>>(std::istream& istr, iProduct& src) {
        return src.read(istr);
        
    }
    
    // returns the sum of total cost and price received
    double operator+=(double& price, const Product& src) {
        return price + src.total_cost();
    }
    
    // returns sku_
    const char* Product::sku() const {
        return sku_;
        
    }
    
    // returns unit_
    const char* Product::unit() const {
        return unit_;
    }
    
    // returns isTaxed
    bool Product::taxed() const {
        return isTaxed;
    }
    
    // returns price_
    double Product::price() const {
        return price_;
    }
    
    // returns type
    char Product::type() const {
        return type_;
    }

    // setter for type
    void Product::type(char newType) {
        this->type_ = newType;
    }

}


























