#include "../include/exeption.h"

Exeption::Exeption(std::string reason) {
    m_reason = reason;
}



Exeption::~Exeption() {
    
}



std::string Exeption::what() const {
    return m_reason;
}



