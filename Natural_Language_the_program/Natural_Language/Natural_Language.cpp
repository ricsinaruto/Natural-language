#include "stdafx.h"

using namespace std;

class szavak
{
public:
	int szoRank;
	string szo;
	int szoRank_file;
	int melyik_file;
};
szavak szo[10000];

//kéne még egy fájlba elmenteni a beszélgetéseket, hogy legyen komolyabb memóriája
int main(int argc, char* argv[])
{
	cout << "hey" << "\n";
	ofstream fileki;
	ifstream filebe;

	string bekert = "";
	string final = "";
	int stringmeret = 0;
	double talalatok = 0;
	int **kettosRelaciok = new int*[3];
	for (int i = 0; i < 3; i++) kettosRelaciok[i] = new int[112605];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 112605; j++) kettosRelaciok[i][j] = 0;
	}

	int **harmasRelaciok = new int*[4];
	for (int i = 0; i < 4; i++) harmasRelaciok[i] = new int[231902];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 231902; j++) harmasRelaciok[i][j] = 0;
	}

	int **negyesRelaciok = new int*[5];
	for (int i = 0; i < 5; i++) negyesRelaciok[i] = new int[233359];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 233359; j++) negyesRelaciok[i][j] = 0;
	}

	int **otosRelaciok = new int*[6];
	for (int i = 0; i < 6; i++) otosRelaciok[i] = new int[187341];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 187341; j++) otosRelaciok[i][j] = 0;
	}


	filebe.open("szoRank_file_szavak.txt");
	//wordlist feltöltés
	int teszt = 0;
	string sor = "";
	while (getline(filebe, sor))
	{
		//string kezelés
		for (int i = 0; i < sor.length(); i++)
		{
			if (sor[i] == ';')
			{
				szo[teszt].szo = sor.substr(0, i);
				stringmeret = i;
				szo[teszt].szoRank = atoi(sor.substr(i + 1, sor.length() - i - 1).c_str());
			}
		}
		teszt++;
	}
	filebe.close();
	cout << teszt<<endl;

	filebe.open("kettosRelaciok.txt");
	//kettosRelaciok feltöltés
	teszt = 0;
	sor = "";
	while (getline(filebe, sor))
	{
		int vesszo = 0;
		//string kezelés
		for (int i = 0; i < sor.length(); i++)
		{
			if (sor[i] == ';')
			{
				kettosRelaciok[0][teszt]= atoi(sor.substr(0, i).c_str());
				vesszo = i;
			}
			if (sor[i] == ' ')
			{
				kettosRelaciok[1][teszt] = atoi(sor.substr(vesszo+1, i).c_str());
				kettosRelaciok[2][teszt] = atoi(sor.substr(i+1, sor.length() - i - 1).c_str());
			}
		}
		teszt++;
	}
	filebe.close();
	cout << teszt<<endl;

	filebe.open("harmasRelaciok.txt");
	//harmasRelaciok feltöltés
	teszt = 0;
	sor = "";
	while (getline(filebe, sor))
	{
		int vesszo = 0;
		int vesszo1 = 0;
		//string kezelés
		for (int i = 0; i < sor.length(); i++)
		{
			if (sor[i] == ';'&&vesszo == 0)
			{
				harmasRelaciok[0][teszt] = atoi(sor.substr(0, i).c_str());
				vesszo = i;
			}
			if (sor[i] == ';'&&vesszo != 0)
			{
				harmasRelaciok[1][teszt] = atoi(sor.substr(vesszo + 1, i).c_str());
				vesszo1 = i;
			}
			if (sor[i] == ' ')
			{
				harmasRelaciok[2][teszt] = atoi(sor.substr(vesszo1 + 1, i).c_str());
				harmasRelaciok[3][teszt] = atoi(sor.substr(i + 1, sor.length() - i - 1).c_str());
			}
		}
		teszt++;
	}
	filebe.close();
	cout << teszt << endl;

	filebe.open("negyesRelaciok.txt");
	//negyesRelaciok feltöltés
	teszt = 0;
	sor = "";
	while (getline(filebe, sor))
	{
		int vesszo = 0;
		int vesszo1 = 0;
		int vesszo2 = 0;
		//string kezelés
		for (int i = 0; i < sor.length(); i++)
		{
			if (sor[i] == ';'&&vesszo == 0)
			{
				negyesRelaciok[0][teszt] = atoi(sor.substr(0, i).c_str());
				vesszo = i;
			}
			if (sor[i] == ';'&&vesszo1 == 0 &&vesszo!=0)
			{
				negyesRelaciok[1][teszt] = atoi(sor.substr(vesszo + 1, i).c_str());
				vesszo1 = i;
			}
			if (sor[i] == ';'&&vesszo != 0&&vesszo1!=0)
			{
				negyesRelaciok[2][teszt] = atoi(sor.substr(vesszo1 + 1, i).c_str());
				vesszo2 = i;
			}
			if (sor[i] == ' ')
			{
				negyesRelaciok[3][teszt] = atoi(sor.substr(vesszo2 + 1, i).c_str());
				negyesRelaciok[4][teszt] = atoi(sor.substr(i + 1, sor.length() - i - 1).c_str());
			}
		}
		teszt++;
	}
	filebe.close();
	cout << teszt << endl;

	filebe.open("otosRelaciok.txt");
	//otosRelaciok feltöltés
	teszt = 0;
	sor = "";
	while (getline(filebe, sor))
	{
		int vesszo = 0;
		int vesszo1 = 0;
		int vesszo2 = 0;
		int vesszo3 = 0;
		//string kezelés
		for (int i = 0; i < sor.length(); i++)
		{
			if (sor[i] == ';'&&vesszo == 0)
			{
				otosRelaciok[0][teszt] = atoi(sor.substr(0, i).c_str());
				vesszo = i;
			}
			if (sor[i] == ';'&&vesszo1 == 0 && vesszo != 0&&vesszo2==0)
			{
				otosRelaciok[1][teszt] = atoi(sor.substr(vesszo + 1, i).c_str());
				vesszo1 = i;
			}
			if (sor[i] == ';'&&vesszo != 0 && vesszo1 != 0&&vesszo2==0)
			{
				otosRelaciok[2][teszt] = atoi(sor.substr(vesszo1 + 1, i).c_str());
				vesszo2 = i;
			}
			if (sor[i] == ';'&&vesszo != 0 && vesszo1 != 0&&vesszo2!=0)
			{
				otosRelaciok[3][teszt] = atoi(sor.substr(vesszo1 + 1, i).c_str());
				vesszo3 = i;
			}
			if (sor[i] == ' ')
			{
				otosRelaciok[4][teszt] = atoi(sor.substr(vesszo3 + 1, i).c_str());
				otosRelaciok[5][teszt] = atoi(sor.substr(i + 1, sor.length() - i - 1).c_str());
			}
		}
		teszt++;
	}
	filebe.close();
	cout << teszt << endl;

	pcg32_random_t rng;
	pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&rng);	//random number generator


	
	int karakterek[400] = { 0 };
	int space = 1;

	for (int i = 0; i < 1000; i++)
	{
		string s;
		getline(cin, s);
		

		int valaszmeret = 0;
		while (valaszmeret<2) valaszmeret = (((double)pcg32_boundedrand_r(&rng, 1000000000)) / 250000000+1);
		

	


		cout << "\n";
		space = 1;
	}
	


	_getch();
    return 0;
}

