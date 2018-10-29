#include "library.h"

int main(int argc, char* argv[]){	
	int i,code;
	int opcnt = 0;
	ifstream fin1;
	ifstream fin2;

	fin1.open("resource.dat");
	fin2.open("input.dat");
	string line;
	string resource_type;
	string resource_name;
	string date;
	string OP;
	string member_type;
	string member_name;

	class library lib;

	getline(fin1,line);
	while(getline(fin1,line)){
		resource_type = line.substr(0,line.find('	'));
		resource_name = line.substr(line.find('	')+1,line.length());
		if(resource_type == "Book"){
			lib.r_set(resource_name, resource_type);
		}
	}

	getline(fin2,line);
	cout << "Op_#	Return_code	Description" << endl;
	while(getline(fin2,line)){
		opcnt++;
		cout << opcnt << '	';
		date = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		resource_type = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		resource_name = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		OP = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		member_type = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		member_name = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());

		code = lib.operation(date,resource_type,resource_name,OP,member_type,member_name);
		lib.description(code);
	}
	fin1.close();
	fin2.close();
	return 0;
}
