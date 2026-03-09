#include "unique_ptr.h"
#include <iostream>
int main() {
    UniquePtr<int> uptr(new int(42));
    std::cout << "UniquePtr value: " << *uptr << std::endl;
    return 0;
}