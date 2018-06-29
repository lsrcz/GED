//
//  input.hpp
//
//  Created by 吴怡凡 on 07/06/2018.
//  Copyright © 2018 evan. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <stdio.h>
#include <string>
#include <map>
using std::map;
using std::string;

#define MAX_NODE 75
class chemgraph{
public:
	chemgraph(){};
	chemgraph(char filename[]);
	void printchem();
	void muta_avoid_H();

	int g[MAX_NODE][MAX_NODE];
	int node[MAX_NODE];
	int node_cnt;
	bool muta;
	int node_with_H[MAX_NODE];

private:
	int match_ele(const char atom[]);

	static map <string, int> ele;
	static int ele_cnt;
};


#endif /* input_hpp */
