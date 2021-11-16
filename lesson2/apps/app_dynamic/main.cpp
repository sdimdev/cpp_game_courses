#include <iostream>
#include <dlfcn.h>

int main()
{
    void* handle = dlopen("liblib_shared.so", RTLD_LAZY);
    if (handle == nullptr)
    {
        std::cout << "unable to load " << "liblib_shared.so" << " Library!" << std::endl;
        return 1;
    }
    auto print_hello = (void(*)())dlsym(handle, "hello");

    if (print_hello == nullptr)
    {
        std::cout << "unable to load " << "liblib_shared.so" << " print function!" << std::endl;
        dlclose(handle);
        return 2;
    }

    print_hello();
    std::cout<<"my congratulations";
    dlclose(handle);

    return 0;
}
