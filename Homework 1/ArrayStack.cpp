#include "ArrayStack.h"
#include <iostream>

ArrayStack::ArrayStack(int capacity)
{
    stacksize = capacity;
    position = 0;
}

void ArrayStack::push(char c)
{
    if (position < stacksize)
    {
        stack[position] = c;
        position++;
    }
}

void ArrayStack::pop()
{
    if (position > 0)
    {
        stack[position] = NULL;
        position--;
    }
}

char ArrayStack::top()
{
    if (position == 0)
    {
        return 0;
    }
    else
    {
        return stack[position - 1];
    }
}

bool ArrayStack::isEmpty()
{
    if (position == 0)
        return true;
    else
        return false;
}

bool ArrayStack::isFull()
{
    if (position == stacksize)
        return true;
    else
        return false;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        ArrayStack *stack = new ArrayStack(3);
        std::cout<<stack->isEmpty() << std::endl;
        stack->push('A');
        stack->push('B');
        std::cout << stack->top() << std::endl;
        stack->push('C');
        std::cout << stack->top() << std::endl;
        std::cout << stack->isFull() << std::endl;
        stack->pop();
        std::cout << stack->isFull() << std::endl;
        stack->push('D');
        std::cout << stack->top() << std::endl;
        delete stack;
    }
    else
    {
        while (argc > 1)
        {
            int count = 0;

            while (argv[argc - 1][count] != NULL)
            {
                count++;
            }
        
            if (count<100)
            {
                ArrayStack *stack = new ArrayStack(count);
        
                for (int i = 0; i < count + 2; i++)
                    stack->push(argv[argc - 1][i]);
        
                while(!(stack->isEmpty()))
                {
                    std::cout << stack->top();
                    stack->pop();
                }

                std::cout << " ";
        
                delete stack;
            }
            else
                std::cout << "ERROR:  String is too long!" << std::endl;
            argc--;
        }
        std::cout << std::endl;
    }   

    return 0;
}
