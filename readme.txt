This program is to calculate the uncertainty easily,  which troubles
me a lot while doing physical experiment. A number with uncertainty 
should be given in the following format:
value:uncertainty

You can calculate with those operators: '+' '-' '*' '/' '^' '(' ')'

for example 
input (12.000:0.004)^2 and the result is 144:0.096
input 1.002:0.04+1.005:0.03 and the result is 2.007:0.05

WARNING
There's no error detecting in the program. Please be careful with your
input. Since the input buf is 1024-byte long, you should not type too
much while the operator stack and the number stack is the same size.

File:
	mystack.cpp: a stack implement
	uncertainty.cpp: a number with uncertainty
	main.cpp: a stack calculator and the main interface
