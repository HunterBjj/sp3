#include <iostream>

int main()
{
    std::cout<<std::endl<<"random gen size"<<std::endl;
    long long n = rand() % 9 + 2;
    std::cout << n << std::endl;
    long long long_array[n*n];
    
    std::cout<<std::endl<<"random gen list"<<std::endl;
    for (int i = 0; i < (n*n); i++)
    {
        long_array[i] = rand() % 9 + 1;
        std::cout << long_array[i] << " ";
    }

    long long *ptr_array = &long_array[0];
    long long *end_array = &long_array[(n*n)-1];
    long long new_array[n][n];
    long long *ptr_new_array = &new_array[0][0];
    long long *end_new_array = &new_array[n-1][n-1];

    __asm__ (
        "mov $8, %%rax\n\t"
        "mulq %[n]\n\t"
        "mov %%rax, %%rbx\n\t"
        "mov %[n], %%rcx\n\t"
        "dec %%rcx\n\t"
        "mulq %%rcx\n\t" 
        "mov %%rax, %%rcx\n\t"
        "mov $0, %%rax\n\t"
        "mov %[ptr_new_array], %%rdx\n\t"
        "add %%rcx, %%rdx\n\t"

        "loop_start:\n\t"
        "mov %[ptr_array], %%rax\n\t"
        "push (%%rax)\n\t"
        "mov %[ptr_new_array], %%rax\n\t"
        "pop (%%rax)\n\t"
        "cmp %%rdx, %[ptr_new_array]\n\t"
        "je next_loop\n\t"
        "add $8, %[ptr_array]\n\t"
        "add %%rbx, %[ptr_new_array]\n\t"
        "jmp loop_start\n\t"

        "next_loop:\n\t"
        "cmp %%rdx, %[end_new_array]\n\t"
        "je end_asm\n\t"
        "add $8, %%rdx\n\t"
        "sub %%rcx, %[ptr_new_array]\n\t"
        "add $8, %[ptr_new_array]\n\t"
        "add $8, %[ptr_array]\n\t"
        "jmp loop_start\n\t"

        "end_asm:\n\t"
        :
        :[ptr_array]"m"(ptr_array), [end_array]"m"(end_array), [ptr_new_array]"m"(ptr_new_array), [end_new_array]"m"(end_new_array), [n]"m"(n)
        :"%rax", "%rbx", "%rcx", "%rdx"
    );
    std::cout<<std::endl<<"--------------"<<std::endl;
    std::cout<<std::endl<<"array"<<std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout<<new_array[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    return 0;
}
