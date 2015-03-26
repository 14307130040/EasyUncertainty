#ifndef __mystack__
#define __mystack__
#define STACKMAX 1024

template<class TYPE>
class CMyStack
{
private:
	TYPE elements[STACKMAX + 1];	//the bottom of the stack is not used. 
public:
	TYPE* SS;	//stack segment
	TYPE* SP;	//stack pointer
	CMyStack()
	{
		SS = elements;
		SP = &elements[STACKMAX];
	}
	TYPE* push(TYPE element)
	{
		*(--SP) = element;
		return SP;
	}

	TYPE* pop(TYPE& element)
	{
		element = *(SP++);
		return SP;
	}
};

#endif
