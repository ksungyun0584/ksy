#include "member.h"
#define MAX_borrow 1

class library {
	private:
		int u_num = 0;
		int g_num = 0;
		int f_num = 0;
		int b_num = 0;
		int m_num = 0;
		int e_num = 0;
		int date = 0;
		vector<undergraduate> undergraduates;
		vector<graduate> graduates;
		vector<faculty> facultys;
		vector<book> lbooks;
		vector<magazine> lmagazines;
		vector<e_book> le_books;

	public:
		void set(int n);
		void m_set(string n, string t);
		void r_set(string n, string t);
		int operation(string d, string rt, string rn, string st, string mt, string mn);
		void description(int code);
};

void library :: r_set(string n, string t){
	if(t == "Book"){
		class book b;
		b.set(n,"R",0,0);
		lbooks.push_back(b);
		b_num++;
	}
	if(t == "Magazine"){
		class magazine m;
		m.set(n,"R",0,0);
		lmagazines.push_back(m);
		m_num++;
	}
	if(t == "e_Book"){
		class e_book e;
		e.set(n,"R",0,0);
		le_books.push_back(e);
		e_num++;
	}
}

void library :: m_set(string n, string t){
	if(t == "Undergraduate"){
		class undergraduate un;
		un.set(n,0);
		undergraduates.push_back(un);
		u_num++;
	}
	if(t == "Graduate"){
		class graduate g;
		g.set(n,0);
		graduates.push_back(g);
		g_num++;
	}
	if(t == "Faculty"){
		class faculty f;
		f.set(n,0);
		facultys.push_back(f);
		f_num++;
	}
}

int library :: operation(string d, string rt, string rn, string st, string mt, string mn){
	date = transdate(d);
	class book b;
	class magazine m;
	class e_book e;
	int i;
	int rnum=0;
	int mnum=0;
	int mrnum=0;
	int r_num=0;

//find resource in lib
	if (rt == "Book"){
		for(i=0;i<b_num;i++){
			rnum = b_num;
			if(rn == lbooks.at(i).pname()) {
				rnum = i;
				break;
			}
		}
		r_num = b_num;
	}	
	else if (rt == "Magazine"){
		for(i=0;i<m_num;i++){
			rnum = m_num;
			if(rn == lmagazines.at(i).pname()) {
				rnum = i;
				break;
			}
		}
		r_num = m_num;
	}
	else if (rt == "e_Book"){
		for(i=0;i<e_num;i++){
			rnum = e_num;
			if(rn == le_books.at(i).pname()) {
				rnum = i;
				break;
			}
		}
		r_num = e_num;
	}

//find member
	if (mt == "Undergraduate"){
		for(i=0;i<u_num;i++){
			mnum = u_num;
			if(mn == undergraduates.at(i).pname()) {
				mnum = i;
				break;
			}
		}
		if(mnum == u_num){
			m_set(mn, mt);
		}
		if(rt == "Book") b = undergraduates.at(mnum).searchbook(rn);
		if(rt == "Magazine") m = undergraduates.at(mnum).searchmaga(rn);
		if(rt == "e_Book") e = undergraduates.at(mnum).searche_b(rn);
	}
	else if (mt == "Graduate"){
		for(i=0;i<g_num;i++){
			mnum = g_num;
			if(mn == graduates.at(i).pname()) {
				mnum = i;
				break;
			}
		}
		if(mnum == g_num){
			m_set(mn, mt);
		}
		if(rt == "Book") b = graduates.at(mnum).searchbook(rn);
		if(rt == "Magazine") m = graduates.at(mnum).searchmaga(rn);
		if(rt == "e_Book") e = graduates.at(mnum).searche_b(rn);
	}
	else if (mt == "Faculty"){
		for(i=0;i<f_num;i++){
			mnum = f_num;
			if(mn == facultys.at(i).pname()) {
				mnum = i;
				break;
			}
		}
		if(mnum == f_num){
			m_set(mn, mt);
		}
		if(rt == "Book") b = facultys.at(mnum).searchbook(rn);
		if(rt == "Magazine") m = facultys.at(mnum).searchmaga(rn);
		if(rt == "e_Book") e = facultys.at(mnum).searche_b(rn);
	}
	
//operation
	if(st == "B"){
		if(rnum == r_num){
			date = 0;
			return 1;
		}
		if(mt == "Undergraduate" && undergraduates.at(mnum).prnum(rt) > MAX_borrow - 1){
			date = 0;
			return 2;	
		}
		if(mt == "Graduate" && graduates.at(mnum).prnum(rt) > MAX_borrow - 1){
			date = 0;
			return 2;	
		}
		if(mt == "Faculty" && facultys.at(mnum).prnum(rt) > MAX_borrow - 1){
			date = 0;
			return 2;	
		}
		
		if(rt == "Book"){
			if(b.pstate() == "B" && b.pname() == rn){
				date = b.psd();
				return 4;
			}
			if(lbooks.at(rnum).pstate() == "B"){
				date = lbooks.at(rnum).ped();
				return 5;
			}
		}
		if(rt == "Magazine"){
			if(m.pstate() == "B" && m.pname() == rn){
				date = m.psd();
				return 4;
			}
			if(lmagazines.at(rnum).pstate() == "B"){
				date = lmagazines.at(rnum).ped();
				return 5;
			}
		}
		if(rt == "e_Book"){
			if(e.pstate() == "B" && e.pname() == rn){
				date = e.psd();
				return 4;
			}
			if(le_books.at(rnum).pstate() == "B"){
				date = le_books.at(rnum).ped();
				return 5;
			}
		}

		if(mt == "Undergraduate" && date-1 < undergraduates.at(mnum).ppenalty()){
			date = undergraduates.at(mnum).ppenalty();
			return 6;
		}
		else if(mt == "Undergraduate"){
			if(rt == "Book") lbooks.at(rnum).set(rn,"B",date,date+13);
			if(rt == "Magazine") lmagazines.at(rnum).set(rn,"B",date,date+13);
			if(rt == "e_Book") le_books.at(rnum).set(rn,"B",date,date+13);
			undergraduates.at(mnum).set(mn,0);
			undergraduates.at(mnum).r_set(rn,rt,date,date+13);
			date = 0;
			return 0;
		}

		if(mt == "Graduate" && date-1 < graduates.at(mnum).ppenalty()){
			date = graduates.at(mnum).ppenalty();
			return 6;
		}
		else if(mt == "Graduate"){
			if(rt == "Book") lbooks.at(rnum).set(rn,"B",date,date+13);
			if(rt == "Magazine") lmagazines.at(rnum).set(rn,"B",date,date+13);
			if(rt == "e_Book") le_books.at(rnum).set(rn,"B",date,date+13);
			graduates.at(mnum).set(mn,0);
			graduates.at(mnum).r_set(rn,rt,date,date+13);
			date = 0;
			return 0;
		}

		if(mt == "Faculty" && date-1 < facultys.at(mnum).ppenalty()){
			date = facultys.at(mnum).ppenalty();
			return 6;
		}
		else if(mt == "Faculty"){
			if(rt == "Book") lbooks.at(rnum).set(rn,"B",date,date+13);
			if(rt == "Magazine") lmagazines.at(rnum).set(rn,"B",date,date+13);
			if(rt == "e_Book") le_books.at(rnum).set(rn,"B",date,date+13);
			facultys.at(mnum).set(mn,0);
			facultys.at(mnum).r_set(rn,rt,date,date+13);
			date = 0;
			return 0;
		}
	}
	if(st == "R"){
		if(rt == "Book"){
			if(b.pstate() == "n"){
				date = 0;
				return 3;
			}
			if(date > lbooks.at(rnum).ped()){
				if(mt == "Undergraduate"){
					undergraduates.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
					date = undergraduates.at(mnum).ppenalty();
					lbooks.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnrs(rn,rt);
				}
				if(mt == "Graduate"){
					graduates.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
					date = graduates.at(mnum).ppenalty();
					lbooks.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnrs(rn,rt);
				}
				if(mt == "Faculty"){
					facultys.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
					date = facultys.at(mnum).ppenalty();
					lbooks.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnrs(rn,rt);
				}
				return 7;
			}
			else {
				lbooks.at(rnum).set(rn,"R",0,0);
				if(mt == "Undergraduate") undergraduates.at(mnum).returnrs(rn,rt);
				if(mt == "Graduate") graduates.at(mnum).returnrs(rn,rt);
				if(mt == "Faculty") facultys.at(mnum).returnrs(rn,rt);
				date = 0;
				return 0;
			}
		}
		if(rt == "Magazine"){
			if(m.pstate() == "n"){
				date = 0;
				return 3;
			}
			if(date > lmagazines.at(rnum).ped()){
				if(mt == "Undergraduate"){
					undergraduates.at(mnum).set(mn,date-lmagazines.at(rnum).ped() + date);
					date = undergraduates.at(mnum).ppenalty();
					lmagazines.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnrs(rn,rt);
				}
				if(mt == "Graduate"){
					graduates.at(mnum).set(mn,date - lmagazines.at(rnum).ped() + date);
					date = graduates.at(mnum).ppenalty();
					lmagazines.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnrs(rn,rt);
				}
				if(mt == "Faculty"){
					facultys.at(mnum).set(mn,date - lmagazines.at(rnum).ped() + date);
					date = facultys.at(mnum).ppenalty();
					lmagazines.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnrs(rn,rt);
				}
				return 7;
			}
			else {
				lmagazines.at(rnum).set(rn,"R",0,0);
				if(mt == "Undergraduate") undergraduates.at(mnum).returnrs(rn,rt);
				if(mt == "Graduate") graduates.at(mnum).returnrs(rn,rt);
				if(mt == "Faculty") facultys.at(mnum).returnrs(rn,rt);
				date = 0;
				return 0;
			}
		}
		if(rt == "e_Book"){
			if(e.pstate() == "n"){
				date = 0;
				return 3;
			}
			if(date > le_books.at(rnum).ped()){
				if(mt == "Undergraduate"){
					undergraduates.at(mnum).set(mn,date - le_books.at(rnum).ped() + date);
					date = undergraduates.at(mnum).ppenalty();
					le_books.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnrs(rn,rt);
				}
				if(mt == "Graduate"){
					graduates.at(mnum).set(mn,date - le_books.at(rnum).ped() + date);
					date = graduates.at(mnum).ppenalty();
					le_books.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnrs(rn,rt);
				}
				if(mt == "Faculty"){
					facultys.at(mnum).set(mn,date - le_books.at(rnum).ped() + date);
					date = facultys.at(mnum).ppenalty();
					le_books.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnrs(rn,rt);
				}
			}
			else {
				le_books.at(rnum).set(rn,"R",0,0);
				if(mt == "Undergraduate") undergraduates.at(mnum).returnrs(rn,rt);
				if(mt == "Graduate") graduates.at(mnum).returnrs(rn,rt);
				if(mt == "Faculty") facultys.at(mnum).returnrs(rn,rt);
				date = 0;
				return 0;
			}
		}
	}
}

void library :: description(int code){
	cout << code << '	';
	switch (code){
		case 0: cout << "Success." << endl; break;
		case 1: cout << "Non exist resource." << endl; break;
		case 2: cout << "Exceeds your possible number of borrow. Possible # of borrows: " << MAX_borrow << endl; break;
		case 3: cout <<  "You did not borrow this book." << endl; break;
		case 4: cout << "You already borrowed this book at "; pday(date); break;
		case 5: cout << "Other member already borrowed this book. This book will be returned at "; pday(date); break;
		case 6: cout << "Restricted member until "; pday(date); break;
		case 7: cout << "Delayed return. You'll be restricted until "; pday(date); break;
	}
}
