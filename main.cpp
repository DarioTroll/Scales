#include <iostream>
#include "scala.h"
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <cmath>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

struct nota {
	string nome;
};

struct opzione {
	string nome;
	bool selezionata;
};

void stampa (scala v[], int num);
bool inizializza (nota c[]);
int sceglitipo (nota c[], scala v[], int n);
void scaladitipo(scala s, nota c[]);

const int LUN=30;

int main(int argc, char** argv) {
	scala vet[LUN];
	//inizializzazione del vettore di scale
	ifstream file;
	file.open("scale.txt",ios::in);
	if (!file.is_open()) {
		perror("Errore nell'apertura del file!!");
		return 0;
	}
	else 
		cout<<"File aperto con successo!!";
	int s1,s2,s3,s4,s5,s6,s7,i;
	string n,start;
	file>>start;
	for (i=0;file>>n>>s1>>s2>>s3>>s4>>s5>>s6>>s7;++i) {
		vet[i].set_nome(n);
		vet[i].set_salto(0,s1);
		vet[i].set_salto(1,s2);
		vet[i].set_salto(2,s3);
		vet[i].set_salto(3,s4);
		vet[i].set_salto(4,s5);
		vet[i].set_salto(5,s6);
		vet[i].set_salto(6,s7);
	}
	cout<<"\nSono state caricate "<<i<<" scale";
	int numscale=i;
	cout<<"\nCaricamento delle scale effettuato con successo!!\n\n";
	
	//Da questo punto del codice in poi le scale sono caricate con successo!!
	
	nota cromatica[12];
	
	if (!inizializza(cromatica))
		return -1;
	
	system("cls");
	
	//Stesura del menu di utilizzo
	int sc=0;
	int ris=0;
	
	opzione op[3];
	op[0].nome="Cambia lingua";
	op[1].nome="Scale";
	op[2].nome="Chiudi";
	op[0].selezionata=false;
	op[1].selezionata=false;
	op[2].selezionata=false;
	do {
		int key=2;
		while (key!=KEY_RIGHT) {
			system("cls");
			cout<<"MENU";
			cout<<"\n\nFreccia SU/GIU per scorrere, Freccia DESTRA per selezionare\n\n";
			switch (key) {
				case KEY_UP: if (sc==0) sc=2; else --sc; break;
				case KEY_DOWN: if(sc==2) sc=0; else ++sc; break; 
			}
			
			op[0].selezionata=false;
			op[1].selezionata=false;
			op[2].selezionata=false;
			op[sc].selezionata=true;
			
			for (int i=0;i<3;++i) {
				if (i==sc)
					cout<<">";
				cout<<"   "<<op[i].nome<<endl;
			}
			key=getch();
		}
		system("cls");
		switch (sc) {
			case 0: ris=inizializza(cromatica);key=2;break;
			case 1: ris=sceglitipo(cromatica,vet,numscale);key=2;break;
			case 2: ris=0;key=2;
		}
	} while(ris!=0);		
	return 0;
}

void stampa (scala v[], int num) {
	for (int i=0;i<num;++i) {
		cout<<v[i].get_nome()<<"\n";
		for(int j=0;j<7;++j)
			cout<<v[i].get_salto(j)<<" ";
		cout<<"\n\n";
	}
}

bool inizializza (nota c[]) {
	string set;
	do {
		cout<<"ENG/ITA?: ";
		cin>>set;
	} while (set!="ITA" and set!="ENG" and set!="ita" and set!="eng");
	ifstream setting;
	if (set=="ENG" or set=="eng")
		setting.open("eng.txt",ios::in);
	else 
		setting.open("ita.txt",ios::in);
	if (!setting.is_open()) {
		perror("Errore nel caricamento delle note");
		return false;
	}
	string s,n;
	setting>>s;
	for (int i=0;setting>>n;++i)
		c[i].nome=n;
	/*/cout<<"\n\nInizializzazione note effettuata con successo!!\n";
	for (int i=0;i<12;++i)
		cout<<c[i].nome<<" ";*/
	return true;
}

int sceglitipo (nota c[], scala v[], int n) {
	int sc=0;
	opzione o[LUN];
	for (int i=0;i<n;++i) {
		o[i].nome=v[i].get_nome();
		o[i].selezionata=false;
	}
	int key=2;
	while (key!=KEY_RIGHT) {
		system("cls");
		cout<<"Freccia SU/GIU per scorrere, Freccia DESTRA per selezionare\n\n";			
		switch (key) {
			case KEY_UP: if (sc==0) sc=n-1; else --sc; break;
			case KEY_DOWN: if(sc==n-1) sc=0; else ++sc; break; 
		}
		for (int i=0;i<n;++i)
			o[i].selezionata=false;
		o[sc].selezionata=true;
			
		for (int i=0;i<n;++i) {
			if (i==sc)
				cout<<">";
			cout<<"   "<<o[i].nome<<endl;
		}
		key=getch();
	}
	system("cls");
	scaladitipo(v[sc],c);
	return 1;
}

void scaladitipo(scala s, nota c[]) {
	int sc=0;
	
	int key=2;
	while (key!=KEY_RIGHT) {
		system("cls");
		cout<<"Freccia SU/GIU per cambiare nota, Freccia DESTRA per tornare al Menu";			
		switch (key) {
			case KEY_UP: if (sc==0) sc=11; else --sc; break;
			case KEY_DOWN: if(sc==11) sc=0; else ++sc; break; 
		}
		cout<<"\n\nScala "<<s.get_nome()<<" di "<<c[sc].nome;
		
		
		int val=sc;
		cout<<"\n"<<c[val].nome<<" ";
		
		for (int i=0;i<7;++i) {
			if (val+s.get_salto(i)<12) 
				val+=s.get_salto(i);
			else
				val=(val+s.get_salto(i)-12);
			cout<<c[val].nome<<" ";
		}
		key=getch();
		
	}
	system("cls");
	key=2;
}
