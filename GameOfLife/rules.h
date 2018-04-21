#include <iostream>
#include <string>
#include <sstream>

namespace rules{

#define NEIGHBOUR_COUNT 9

	bool for_alive[NEIGHBOUR_COUNT]{false}; // # of neighbours for alive cells to stay alive
	bool for_dead[NEIGHBOUR_COUNT]{false}; // # of neighbours for dead cells to become alive

	bool get_next_gen(bool thisGenCell, int neighbours){
		return thisGenCell ? for_alive[neighbours] : for_dead[neighbours];
	}

	inline std::string get_rules(){
		std::ostringstream oss;

		for(int i = 0; i < NEIGHBOUR_COUNT; i++)
			if(for_alive[i]) oss << i;

		oss << '/';

		for(int i = 0; i < NEIGHBOUR_COUNT; i++)
			if(for_dead[i]) oss << i;

		return oss.str();
	}

	inline int to_neighbour_count(char c){
		int i = c -'0';
		return (0 <= i && i < NEIGHBOUR_COUNT) ? i : -1;
	}

	void parse_num(bool arr[NEIGHBOUR_COUNT], char c){
		int num = to_neighbour_count(c);
		if(num != -1)
			arr[num] = true;
	}

	bool parse(std::string rules){
		int size = rules.size();
		if(size == 0){ // no input given, set default
			for_alive[2] = true;
			for_alive[3] = true;
			for_dead[3] = true;
			return true;
		}

		if(size < 3) // invalid input
			return false;

		int slash_pos = 0;
		// check for '/' char
		for(; slash_pos < size && rules[slash_pos] != '/'; slash_pos++);
		if(slash_pos == 0 || slash_pos == size-1) // invalid input
			return false;

		int i = 0;
		while(i < slash_pos)
			parse_num(for_alive, rules[i++]);
		while(i < size)
			parse_num(for_dead, rules[i++]);

		return true;
	}

	void read(){
		std::string rules;
		std::cout << "Provide rules (blank for default): ";
		getline(std::cin, rules);
		if(parse(rules))
			std::cout << "Selected rules: " << get_rules() << std::endl;
		else read();
	}

}
