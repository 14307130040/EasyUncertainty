#ifndef __uncertainty__
#define __uncertainty__
#include "cmath"

#define x2(x) (x) * (x)
template<class TYPE>
class uncertainty
{
public:
	TYPE main;
	TYPE uncert;
public:
	uncertainty(TYPE m, TYPE u)
	{
		this->main = m;
		this->uncert = u;
	}

	uncertainty()
	{
		main = 0;
		uncert = 0;
	}

	uncertainty operator +(const uncertainty &u)
	{
		return uncertainty(this->main + u.main,
				sqrt(x2(this->uncert) + x2(u.uncert)));
	}
	uncertainty operator -(const uncertainty &u)
	{
		return uncertainty(this->main - u.main,
				sqrt(x2(this->uncert) + x2(u.uncert)));
	}
	uncertainty operator *(const uncertainty &u)
	{
		TYPE _main = this->main * u.main;
		TYPE _u = sqrt(x2(this->uncert / this->main) + x2(u.uncert / u.main));
		return uncertainty(_main, _main * _u);
	}
	uncertainty operator /(const uncertainty &u)
	{
		TYPE _main = this->main / u.main;
		TYPE _u = sqrt(x2(this->uncert / this->main) + x2(u.uncert / u.main));
		return uncertainty(_main, _main * _u);
	}

	
	uncertainty operator ^(const double n)
	{
		TYPE _main = pow(this->main, n);
		TYPE _u = sqrt(x2(this->uncert / this->main * n));
		return uncertainty(_main, _main * _u);
	}

	uncertainty operator ^(const uncertainty n)
	{
		TYPE _main = pow(this->main, n.main);
		TYPE _u = sqrt(x2(this->uncert / this->main * n.main));
		return uncertainty(_main, _main * _u);
	}

};
#endif
