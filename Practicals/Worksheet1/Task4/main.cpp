#include "my_string.hpp"
#include "RefCounter.hpp"

int main() {
    std::cout << "Running Task4" << std::endl;
    {
        RefCounter<my_string> s(new my_string("Hello world"));
        s.getObject()->print();
        s.printRefs();
        {
            RefCounter<my_string> t = s;
            s.getObject()->print();
            s.printRefs();
            t.getObject()->print();
            t.printRefs();
            std::cout << s.getObject()->getChar(1) << std::endl;
            s.getObject()->print();
            s.printRefs();
            t.getObject()->print();
            t.printRefs();
        }
        s.getObject()->setChar(1, 'E');
        s.getObject()->print();
        s.printRefs();
    }

    std::cout << "Objects should be removed" << std::endl;
}