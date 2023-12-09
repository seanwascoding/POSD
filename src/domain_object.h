#pragma once

#include <string>
#include <iostream>

class DomainObject {
public:
    DomainObject(std::string id): _id(id) {}

    std::string id() const {
        std::cout << "DomainObject::id" << std::endl;
        return _id;
    }

    virtual ~DomainObject() {
        
    }
    
protected:
    std::string _id;
};