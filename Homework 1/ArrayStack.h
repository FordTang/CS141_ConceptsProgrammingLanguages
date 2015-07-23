class ArrayStack
{
    public:
        ArrayStack(int capacity);
            // constructor for a stack
        void push(char c);
            // adds a c to the top of the stack, does nothing if stack is full
        void pop();
            // removes the top element, does nothing if stack is empty
        char top();
            // returns the top element or 0 if stack is empty
        bool isEmpty();
            // returns true if the stack is empty
        bool isFull();
            // returns true if the stack is full
    private:
        char stack[100];
        int stacksize = 0;
        int position = 0;
};
