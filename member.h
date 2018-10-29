#include "resource.h"

class member {
	private:
		string mname;
		vector<book> books;
		vector<magazine> magazines;
		vector<e_book> e_books;

		int penalty = 0;
		int b_num = 0;
		int m_num = 0;
		int e_num = 0;

	public:
		void set(string n, int p);
		void r_set(string n, string t, int sd, int ed);
		string pname();
		int prnum(string rt);
		int ppenalty();
		book searchbook(string s);
		magazine searchmaga(string s);
		e_book searche_b(string s);
		void returnrs(string n, string t);
};

class undergraduate:public member{};
class graduate:public member{};
class faculty:public member{};

book member :: searchbook(string s){
	class book b;
	b.set("n","n",0,0);
	for (int i=0;i<b_num;i++){
		if(s == books.at(i).pname()) return books.at(i);
	}
	return b;
}

magazine member :: searchmaga(string s){
	class magazine m;
	m.set("n","n",0,0);
	for (int i=0;i<m_num;i++){
		if(s == magazines.at(i).pname()) return magazines.at(i);
	}
	return m;
}

e_book member :: searche_b(string s){
	class e_book e;
	e.set("n","n",0,0);
	for (int i=0;i<e_num;i++){
		if(s == e_books.at(i).pname()) return e_books.at(i);
	}
	return e;
}

string member :: pname(){
	return mname;
}

int member :: prnum(string rt){
	if(rt == "Book")
		return b_num;
	if(rt == "Magazine")
		return m_num;
	if(rt == "e_Book")
		return e_num;
}

int member :: ppenalty(){
	return penalty;
}

void member :: set(string n, int p){
	penalty = p;
	mname = n;
}

void member :: r_set(string n, string t, int sd, int ed){
	if(t == "Book"){
		class book b;
		b.set(n,"B",sd,ed);
		books.push_back(b);
		b_num++;
	}
	if(t == "Magazine"){
		class magazine m;
		m.set(n,"B",sd,ed);
		magazines.push_back(m);
		m_num++;
	}
	if(t == "e_Book"){
		class e_book e;
		e.set(n,"B",sd,ed);
		e_books.push_back(e);
		e_num++;
	}
}

void member :: returnrs(string n, string t){
	int i;
	if(t == "Book"){
		class book b;
		if(b_num == 1){
			books.pop_back();
			b_num--;
			return;
		}
		for(i=0;i<b_num-1;i++){
			if(books.at(i).pname() == n) {
				b = books.at(i);
				books.at(i) = books.at(i+1);
				books.at(i+1) = b;
			}
		}
		books.pop_back();
		b_num--;
		return;
	}
	if(t == "Magazine"){
		class magazine m;
		if(m_num == 1){
			magazines.pop_back();
			m_num--;
			return;
		}
		for(i=0;i<m_num-1;i++){
			if(magazines.at(i).pname() == n) {
				m = magazines.at(i);
				magazines.at(i) = magazines.at(i+1);
				magazines.at(i+1) = m;
			}
		}
		magazines.pop_back();
		m_num--;
		return;
	}
	if(t == "e_Book"){
		class e_book e;
		if(e_num == 1){
			e_books.pop_back();
			e_num--;
			return;
		}
		for(i=0;i<e_num-1;i++){
			if(e_books.at(i).pname() == n) {
				e = e_books.at(i);
				e_books.at(i) = e_books.at(i+1);
				e_books.at(i+1) = e;
			}
		}
		e_books.pop_back();
		e_num--;
		return;
	}
}
