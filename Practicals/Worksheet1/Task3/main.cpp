#include "my_string.hpp"


int main() {
    std::cout << "Running Task3" << std::endl;
   { 
        my_string s("Hello world");
        s.print();
        {
            my_string t = s;
            s.print();
            t.print();
            std::cout << s.getChar(1) << std::endl;
            s.print();
            t.print();
        }
        s.setChar(1,'E');
        s.print();
    }
    
}