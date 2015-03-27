#ifndef __mystack__
#define __mystack__
#define STACKMAX 1024

template<class TYPE>
class mystack
{
private:
	TYPE elements[STACKMAX];
public:
	TYPE* SS;	//stack segment
	TYPE* SP;	//stack pointer
	mystack()
	{
		SS = elements;
		SP = &elements[STACKMAX];	//point behind the end of the arr
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
