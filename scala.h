using namespace std;
#include <string.h>
class scala {
	string nome;
	string num_note;
	int salti[7];
	public:
		scala() {nome="";num_note=0;}
		
		string get_nome ()  {return nome;}
		void set_nome(string name) {nome=name;}
		
		int get_salto(int i) {return salti[i];}
		void set_salto(int i, int val) {salti[i]=val;}
		
		string get_num_note () {return num_note;}
		void set_num_note (string n) {num_note=n;}
};
