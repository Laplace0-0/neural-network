#include <iostream>
#include <vector>
#include "neural.hpp"

int main(){
    Matrix A(3, 3), B(3, 3), C(3, 3), D(3, 3), E(3, 3);

    // Fill with any pattern or values
    nn.init.he_normal(A);
    A.print();

    return 0;
}