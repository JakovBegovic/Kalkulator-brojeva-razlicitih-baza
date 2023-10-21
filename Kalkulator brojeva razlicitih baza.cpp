#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

int slovo_u_broj(char sl){
	int broj;
	
	switch(sl){
		case 'A': broj = 10; break;
		case 'B': broj = 11; break;
		case 'C': broj = 12; break;
		case 'D': broj = 13; break;
		case 'E': broj = 14; break;
		case 'F': broj = 15; break;
		default: broj=int(sl)-48;
	}
	
	return broj;
}

char broj_u_slovo(int br){
	char sl;
	
	switch(br){
		case 10: sl='A'; break;
		case 11: sl='B'; break;
		case 12: sl='C'; break;
		case 13: sl='D'; break;
		case 14: sl='E'; break;
		case 15: sl='F'; break;
		default: sl=char(br+'0');

	}
	
	return sl;
}

bool baza_valja(string br, int bz){
	bool valja = true;
	
	for(int i=0; i<br.size(); i++){
		if(char(br[i])!='.'){
			if((slovo_u_broj(char(br[i])))>=bz){
			valja = false;
			break;
			}
		}
	}
	
	if(!valja){
		cout << "Vas broj nije navedene baze. Ponovno unesite broj." << endl;
	}
	
	return valja;
}

string uDekadski(string br, int bz){
	int duljina= br.size();
	
	int eksp=1;
	int rez=0;
	
	for(int i=duljina-1; i>=0; i--){
		rez+=slovo_u_broj(br[i])*eksp;
		eksp=eksp*bz;
	}
	stringstream SS;
	
	string str;
	SS<<rez;
	SS>>str;
	
	return str;
}

string izDekadskog(string uneseniSt, int nova_bz){
	stringstream ss;
	
	int prvotniBr;
	
	ss << uneseniSt;
	
	ss>>prvotniBr;
	
	string rezultat="";
	
	while(prvotniBr>0){
		rezultat +=broj_u_slovo(prvotniBr%nova_bz);
		prvotniBr /= nova_bz;
	}
	
	reverse (rezultat.begin(), rezultat.end());
	
	return rezultat;
}

void pretvori_u_drugu_bazu(string br, int stara_bz){
	cout << "U broj koje baze zelite pretvoriti svoj broj? Odaberite 2, 8, 10 ili 16: ";
	
	bool uvjet;
	
	int nova_bz;
	
	do{
		cin>> nova_bz;
		uvjet=false;
		if(nova_bz==stara_bz){
			cout <<"Vas broj je vec u toj bazi. Unesite drugaciju bazu: ";
			uvjet = false;
		}else if(nova_bz!=2 && nova_bz!=8 && nova_bz!=10 && nova_bz!=16){
			cout << "Upisite bazu 2, 8, 10 ili 16." << endl;
			uvjet = false;
		}
	}while(uvjet);
	
	string broj, broj2;
	if(stara_bz==10){
		broj= izDekadskog(br, nova_bz);
		cout << "Vas broj u bazi " << nova_bz << " je " << broj << endl;
	}else if(nova_bz==10){
		broj = uDekadski(br, stara_bz);
		cout << "Vas broj u bazi 10 je " << broj << endl;
	}else{
		broj=uDekadski(br, stara_bz);
		broj=izDekadskog(broj, nova_bz);
		cout << "Vas broj u bazi " << nova_bz << " je " << broj << endl;
	}
	
}

void mat_operacije(string br1, int bz1){
	char operacija;
	do{
		cout << "Izaberite matematicku operaciju (unesite +, -, *,/): ";
		cin>>operacija;
	}while(operacija!='+' && operacija!='-' && operacija!='*' && operacija!='/');
	
	string br2;
	int bz2;
	
	do{
		cout << "Unesite drugi broj za operaciju: ";
		cin >> br2;
		
		cout << "Upisite koje je baze vas broj: ";
		cin>> bz2;
		
	}while(!baza_valja(br2, bz2));
	
	int baza_rez;
	do{
		cout << "Upisite u kojoj bazi zelite prikazan rezultat: ";
		cin >> baza_rez;
	
	}while(baza_rez!=2 && baza_rez!=8 && baza_rez!=10 && baza_rez!=16);
	
	if(bz1!=10){
		br1=uDekadski(br1, bz1);
	}
	if(bz2!=10){
		br2=uDekadski(br2, bz2);
	}
	
	stringstream ss1, ss2, ss3;
	
	int br1I, br2I;
	
	ss1 << br1;
	ss1>>br1I;
	
	ss2<<br2;
	ss2>>br2I;
	
	int rezInt;
	
	switch(operacija){
		case '+': rezInt = br1I+br2I; break;
		case '-': rezInt = br1I-br2I; break;
		case '*': rezInt = br1I*br2I; break;
		case '/': rezInt = br1I/br2I; break;
	}
	
	string rezSt;
	
	ss3<<rezInt;
	ss3>>rezSt;
	
	if(baza_rez!=10){
		cout << "Vas razultat u bazi " << baza_rez << " je " << izDekadskog(rezSt, baza_rez) << endl;
	}else{
		cout << "Vas rezultat u bazi 10 je " << rezInt << endl;
	}
}


// pocetak izvodenja programa
int main(){

	string broj1, broj2;
	cout << "Ako zelite terminirati program, upisite rijec \"kraj\". Ako zelite unijeti";
	cout << " heksadekadski broj, slovne znamenke unesite velikim slovima." << endl;
	int baza1;
	bool izlaz = false;
	
	do{
		do{
		
			cout << "Upisite broj sa bazom 2, 8, 10 ili 16 (ili kraj za izlaz): ";
			cin >> broj1;
			
			if(broj1=="kraj"){
				izlaz = true;
				break;
			}
			
			cout << "Upisite koje je baze vas broj: ";
			cin>> baza1;			
		}while((!baza_valja(broj1, baza1)));
		
		if(izlaz){
			break;
		}
		
		cout << "Odaberite jednu opciju: " << endl;
		cout << "1. Pretvorba broja u neku drugu bazu." << endl;
		cout << "2. Matematicke operacije sa unesenim brojem." << endl;
		cout << "Unesite Vas odabir: ";
		
		int odabir;
		cin >> odabir;
		
		switch(odabir){	
			case 1: pretvori_u_drugu_bazu(broj1, baza1); break;
			case 2: mat_operacije(broj1, baza1); break;
		}
	
	}while(broj1!="kraj");
	system("PAUSE");
}
