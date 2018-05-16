#include "brush.h"

#ifndef CMD_H
#define CMD_H

namespace cmd{

class root{
protected:
	double scale;
	root(double scale):
		scale(scale)
	{}

public:
	virtual ~root(){};

	virtual void exec(brush&) const = 0;
};

class move : public root{
public:
	move(double scale) : root(scale){}
	void exec(brush& b) const{
		b.move(scale);
	}
	~move(){};
};

class turn : public root{
public:
	turn(double scale) : root(scale){}
	void exec(brush& b) const{
		b.turn(scale);
	}
	~turn(){};
};

class save : public root{
public:
	save(double scale) : root(scale){}
	void exec(brush& b) const{
		b.save();
	}
	~save(){};
};

class load : public root{
public:
	load(double scale) : root(scale){}
	void exec(brush& b) const{
		b.load();
	}
	~load(){};
};

}


#endif
