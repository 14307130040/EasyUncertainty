#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

#include "mystack.cpp"
#include "uncertainty.cpp"

#define ENDF '#'	//the end of a formula
typedef uncertainty<double> U;

signed char pri[0xff][0xff];	//a priority matrix

using namespace std;

istream& operator >>(istream& in, U &s)
{
	return in;
}

ostream& operator <<(ostream& out, const U &u)
{
	out<<u.main<<":"<<u.uncert;
	return out;
}

//this and the following functions are originally from the internet
//but i can't clearly identify where it is from because people here
//do not concern the copyright
U parse(const char* f)
{
	mystack<char> op;
	mystack<U> nu;
	op.push('#');
	
	while((*f) != '\0')
	{
		if(*f == '.' || *f == ':' || (*f >= '0' && *f <= '9'))	//number
		{
			U tmp;
			sscanf(f, "%lf:%lf", &tmp.main, &tmp.uncert);
			nu.push(tmp);
			while(*f == '.' || *f == ':' || (*f >= '0' && *f <= '9'))
				f++;
		}
		else
		{
			if(pri[*op.SP][*f]==-1)
			{
				op.push(*f);
				f++;
			}
			else if(pri[*op.SP][*f]==1)
			{
				U a, b;
				char c;
				nu.pop(a);
				nu.pop(b);
				op.pop(c);
				switch(c)
				{
				case '+':
					b = a + b; 
					break;
				case '-':
					b = b - a;
					break;
				case '*':
					b = a * b;
					break;
				case '/':
					b = b / a;
					break;
				case '^':
					b = b ^ a;
					break;
				}
				nu.push(b);
			}
			else if(pri[*op.SP][*f]==0)
			{
				op.SP++;
				f++;
			}
			else
			{
				cerr<<"Syntax error: "<<*op.SP<<" "<<*f<<endl;
				cerr<<(int)pri[*op.SP][*f]<<endl;
				return U(-999.999, 0.001);
			}
		}
	}
	return *nu.SP;
}

void initpri()
{
	memset(pri, 2, sizeof(pri));
	pri['+']['+']=1;
	pri['+']['-']=1;
	pri['+']['*']=-1;
	pri['+']['/']=-1;
	pri['+']['(']=-1;
	pri['+'][')']=1;
	pri['+']['#']=1;
	pri['+']['^']=-1;
	
	pri['-']['+']=1;
	pri['-']['-']=1;
	pri['-']['*']=-1;
	pri['-']['/']=-1;
	pri['-']['(']=-1;
	pri['-'][')']=1;
	pri['-']['#']=1;
	pri['-']['^']=-1;

	pri['*']['+']=1;
	pri['*']['-']=1;
	pri['*']['*']=1;
	pri['*']['/']=1;
	pri['*']['(']=-1;
	pri['*'][')']=1;
	pri['*']['#']=1;
	pri['*']['^']=-1;

	pri['/']['+']=1;
	pri['/']['-']=1;
	pri['/']['*']=1;
	pri['/']['/']=1;
	pri['/']['(']=-1;
	pri['/'][')']=1;
	pri['/']['#']=1;
	pri['/']['^']=-1;

	pri['(']['+']=-1;
	pri['(']['-']=-1;
	pri['(']['*']=-1;
	pri['(']['/']=-1;
	pri['(']['(']=-1;
	pri['('][')']=0;
	pri['(']['#']=2;
	pri['(']['^']=-1;

	pri[')']['+']=1;
	pri[')']['-']=1;
	pri[')']['*']=1;
	pri[')']['/']=1;
	pri[')']['(']=2;
	pri[')'][')']=1;
	pri[')']['#']=1;
	pri[')']['^']=1;

	pri['#']['+']=-1;
	pri['#']['-']=-1;
	pri['#']['*']=-1;
	pri['#']['/']=-1;
	pri['#']['(']=-1;
	pri['#'][')']=2;
	pri['#']['#']=0;
	pri['#']['^']=-1;

	pri['^']['+']=1;
	pri['^']['-']=1;
	pri['^']['*']=1;
	pri['^']['/']=1;
	pri['^']['(']=-1;
	pri['^'][')']=1;
	pri['^']['#']=1;
	pri['^']['^']=1;
}

int main(int argc, char* argv[])
{
	initpri();
	FILE * f = stdin;
	char buf[1024 + 1];
	string str;
	if(argc == 2)
	{
		f = fopen(argv[2], "r");
		if(f == NULL)
		{
			perror("file open failed");
			return -1;
		}
	}

	while(!feof(f) && 1 == fscanf(f, "%1024s", buf))
	{
		str = buf;
		str += "#";
		cout<<parse(str.c_str())<<endl;
	}

	return 0;
}
