#include <map>
#include <queue>

#include "brush.h"

#ifndef CMD_H
#define CMD_H

#define DIST_MOVE 20
#define DIST_TURN 30

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
	virtual char get_id() const = 0;
};

class forward : public root{
public:
	forward(double scale) : root(scale){}
	void exec(brush& b) const{
		b.move(scale);
	}
	char get_id() const{
		return 'F';
	}
	~forward(){};
};

class leaf : public root{
public:
	leaf(double scale) : root(scale){}
	void exec(brush& b) const{
		b.move(scale);
	}
	char get_id() const{
		return 'f';
	}
	~leaf(){};
};

class left : public root{
public:
	left(double scale) : root(scale){}
	void exec(brush& b) const{
		b.turn(scale);
	}
	char get_id() const{
		return '-';
	}
	~left(){};
};

class right : public root{
public:
	right(double scale) : root(scale){}
	void exec(brush& b) const{
		b.turn(-scale);
	}
	char get_id() const{
		return '+';
	}
	~right(){};
};

class save : public root{
public:
	save(double scale) : root(scale){}
	void exec(brush& b) const{
		b.save();
	}
	char get_id() const{
		return '[';
	}
	~save(){};
};

class load : public root{
public:
	load(double scale) : root(scale){}
	void exec(brush& b) const{
		b.load();
	}
	char get_id() const{
		return ']';
	}
	~load(){};
};

class aux : public root{
public:
	aux(double scale) : root(scale){}
	void exec(brush&) const{}
	char get_id() const{
		return 'x';
	}
	~aux(){};
};

std::queue<const root*> queue;
std::map<char, const cmd::root*> cmd_map;

std::vector<const root*> cmds{
	new forward(DIST_MOVE),
	new leaf(DIST_MOVE),
	new left(DIST_TURN),
	new right(DIST_TURN),
	new save(0),
	new load(0),
	new aux(0),
};


void init(){
	int size = cmds.size();
	for(int i = 0; i < size; i++)
		cmd_map.insert(std::make_pair(cmds[i]->get_id(), cmds[i]));
}

void parse(unsigned char c){
	if(cmd_map.count(c))
		queue.push(cmd_map.at(c));
}

void parse(std::string buffer){
	int size = buffer.length();
	for(int i = 0; i < size; i++)
		parse(buffer[i]);
}

}


#endif
