


#include "stdafx.h"

using namespace std;
//mutex mtx;
//condition_variable cv;

int result = -1;

class szavak
{
public:
	int szoRank;
	string szo;
	int szoRank_file;
	int melyik_file;
};

szavak szo[10000];

void thread0()
{
	ofstream fileki;
	ifstream filebe;

	
	string bekert = "";
	string final = "";
	int stringmeret = 0;
	double talalatok = 0;
	int **kettosRelaciok=new int*[10000];
	for (int i = 0; i < 10000; i++) kettosRelaciok[i] = new int[10000];
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 10000; j++) kettosRelaciok[i][j] = 0;
	}

	filebe.open("wordlist.txt");
	
	int teszt = 0;
	string sor="";
	while (getline(filebe, sor))
	{
			//string kezelés
			for (int i = 0; i < sor.length(); i++)
			{
				if (sor[i] == ';')
				{
					szo[teszt].szo= sor.substr(0, i);
					stringmeret = i;
					szo[teszt].szoRank = atoi(sor.substr(i+1,sor.length()-i-1).c_str());
				}
			}
			teszt++;
	}
	filebe.close();

	string output="";
	filebe.open("big.txt");
	sor = "";

	while (getline(filebe, sor))
	{
		output += sor+" ";
	}
	filebe.close();

	string output_teszt = "";
	filebe.open("teszt.txt");
	sor = "";

	while (getline(filebe, sor))
	{
		output_teszt += sor + " ";
	}
	filebe.close();

	

	/*for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 10000; j++)
		{
			string keres = " "+szo[i].szo + " " + szo[j].szo+" ";
			

			for (int k = 0; k < output.length()-keres.length()-1; k++)
			{
				if (keres == output.substr(k, keres.length()))
				{
					kettosRelaciok[i][j]++;
				}
			}

			fileki << kettosRelaciok[i][j] << " ";
			cout << kettosRelaciok[i][j] << " ";
			
		}
		fileki << endl;
		cout << endl;
	}*/
	
	int l = 0;
	int figy=0;
	for (int i = 3969; i < 10000; i++)
	{

		string keres = " " + szo[i].szo + " ";

			for (int k = 0; k < output_teszt.length() - keres.length() - 1;k++)
			{
				figy = 0;
				l = 0;
				if (keres[0] == output_teszt[k])
				{
					
					while (figy < keres.length() && l<keres.length()-1)
					{
						if (keres[l + 1] == output_teszt[k + l + 1]) l++;
						else figy = keres.length();
					}
					if (l==keres.length()-1) szo[i].szoRank_file++;
				}
				k += l;
			}
			szo[i].melyik_file = 0;
			if (szo[i].szoRank_file == 0)
			{
				for (int k = 0; k < output.length() - keres.length() - 1; k++)
				{
					figy = 0;
					l = 0;
					if (keres[0] == output[k])
					{

						while (figy < keres.length() && l<keres.length() - 1)
						{
							if (keres[l + 1] == output[k + l + 1]) l++;
							else figy = keres.length();
						}
						if (l == keres.length() - 1) szo[i].szoRank_file++;
					}
					k += l;
				}
				szo[i].melyik_file = 1;
			}
			
			fileki << szo[i].szoRank_file << ";"<<szo[i].melyik_file<< endl;
			cout << szo[i].szoRank_file <<"   "<<i<<"       "<<szo[i].melyik_file<< endl;

	}


	fileki.close();

}

void thread1()
{
	ofstream fileki;
	ifstream filebe;


	string bekert = "";
	string final = "";
	int stringmeret = 0;
	double talalatok = 0;
	int **kettosRelaciok = new int*[10000];
	for (int i = 0; i < 10000; i++) kettosRelaciok[i] = new int[10000];
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 10000; j++) kettosRelaciok[i][j] = 0;
	}

	filebe.open("wordlist.txt");

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

	filebe.open("szoRank_file.txt");
	sor = "";
	teszt = 0;

	while (getline(filebe, sor))
	{
		if (sor[0] != 0)
		{
			for (int i = 0; i < sor.length(); i++)
			{
				if (sor[i] == ';')
				{
					if (sor[i + 1] == '0')
					{
						szo[teszt].szoRank_file= atoi(sor.substr(0, i).c_str());
						szo[teszt].szoRank_file = szo[teszt].szoRank_file * 28;
					}
					else szo[teszt].szoRank_file = atoi(sor.substr(0, i).c_str());
				}
			}
		}
		else szo[teszt].szoRank_file = 0;
		teszt++;
	}
	filebe.close();


	int *szoRank_index = new int[10000];

	for (int i = 0; i < 10000; i++) szoRank_index[i] = i;

	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int j = 0; j < 9999; j++)
		{
			if (szo[j].szoRank_file < szo[j + 1].szoRank_file)
			{
				int k = szo[j].szoRank_file;
				szo[j].szoRank_file = szo[j + 1].szoRank_file;
				szo[j + 1].szoRank_file = k;

				k = szoRank_index[j];
				szoRank_index[j] = szoRank_index[j + 1];
				szoRank_index[j + 1] = k;
				swapped = true;
			}
		}
	}

	fileki.open("szoRank_file_szavak.txt");

	for (int i = 0; i < 10000; i++)
	{
		if (szo[i].szoRank_file != 0)
		{
			fileki << szo[szoRank_index[i]].szo << ";" << szo[i].szoRank_file << endl;
		}
	}



	fileki.close();






/*
	string output = "";
	filebe.open("big.txt");
	sor = "";

	while (getline(filebe, sor))
	{
		output += sor + " ";
	}
	filebe.close();

	string output_teszt = "";
	filebe.open("teszt.txt");
	sor = "";

	while (getline(filebe, sor))
	{
		output_teszt += sor + " ";
	}
	filebe.close();
*/




	int l = 0;
	int figy = 0;
	/*for (int i = 3969; i < 10000; i++)
	{

		string keres = " " + szo[i].szo + " ";

		for (int k = 0; k < output_teszt.length() - keres.length() - 1; k++)
		{
			figy = 0;
			l = 0;
			if (keres[0] == output_teszt[k])
			{

				while (figy < keres.length() && l<keres.length() - 1)
				{
					if (keres[l + 1] == output_teszt[k + l + 1]) l++;
					else figy = keres.length();
				}
				if (l == keres.length() - 1) szo[i].szoRank_file++;
			}
			k += l;
		}
		szo[i].melyik_file = 0;
		

		fileki << szo[i].szoRank_file << ";" << szo[i].melyik_file << endl;
		cout << szo[i].szoRank_file << "   " << i << "       " << szo[i].melyik_file << endl;

	}
	*/

	fileki.close();

}

void thread2()
{
	ofstream fileki;
	ifstream filebe;

	string bekert = "";
	string final = "";
	int stringmeret = 0;
	double talalatok = 0;
	int *harmasRelaciok = new int[1000000];
	string *harmasR_szavak = new string[1000000];
	for (int i = 0; i < 1000000; i++)
	{
		harmasRelaciok[i] = 0;
		harmasR_szavak[i] = "";
	}
	

	filebe.open("szoRank_file_szavak.txt");

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
	cout << teszt;
	
	filebe.open("text_szavak.txt");
	fileki.open("negyesRelaciok.txt");
	sor = "";
	string output = "";
	teszt = 0;
	string elozo1sor="0";
	string elozo2sor = "0";
	string elozo3sor = "0";
	string elozo4sor = "0";
	while (getline(filebe, sor))
	{
		if (sor[0] != '0' && elozo1sor[0]!='0' && elozo2sor[0]!='0'&& elozo3sor[0] != '0'&& elozo4sor[0] != '0')
		{
			int i = 0;
			bool talalat = false;
			while (i<5969 && !talalat)
			{
				if (elozo4sor == szo[i].szo)
				{
					talalat = true;
				}
				i++;
			}
			int j = 0;
			bool talalat1 = false;
			int k = 0;
			bool talalat2 = false;
			int l = 0;
			bool talalat3 = false;
			int m = 0;
			bool talalat4 = false;

			if (talalat)
			{
				while (j<5969 && !talalat1)
				{
					if (elozo3sor == szo[j].szo)
					{
						talalat1 = true;
					}
					j++;
				}

				if (talalat1)
				{
					while (k<5969 && !talalat2)
					{
						if (elozo2sor == szo[k].szo)
						{
							talalat2 = true;
						}
						k++;
					}

					if (talalat2)
					{
						while (l<5969 && !talalat3)
						{
							if (elozo1sor == szo[l].szo)
							{
								talalat3 = true;
							}
							l++;
						}

						if (talalat3)
						{
							while (m<5969 && !talalat4)
							{
								if (sor == szo[m].szo)
								{
									talalat4 = true;
								}
								m++;
							}
						}
					}
				}
			}

			if (talalat && talalat1 && talalat2 &&talalat3&&talalat4)
			{
				int z = 0;
				bool talalt = false;
				ostringstream convert1;
				ostringstream convert2;
				ostringstream convert3;
				ostringstream convert4;
				ostringstream convert5;
				convert1 << i - 1;
				convert2 << j - 1;
				convert3 << k - 1;
				convert4 << l - 1;
				convert5 << m - 1;

				string keres = convert1.str() + ";" + convert2.str() + ";" + convert3.str() +
					";" + convert4.str() + ";"+convert5.str();
				while (!talalt && harmasRelaciok[z] != 0)
				{
					if (harmasR_szavak[z] == keres)
					{
						harmasRelaciok[z]++;
						talalt = true;
					}
					z++;
				}

				if (!talalt)
				{
					harmasRelaciok[z]++;
					harmasR_szavak[z] = keres;
				}
				//cout << harmasR_szavak[z] << endl;
			}
		}

		
		cout << teszt << endl;
		teszt++;

		elozo4sor = elozo3sor;
		elozo3sor = elozo2sor;
		elozo2sor = elozo1sor;
		elozo1sor = sor;
		
	}
	filebe.close();
	
	for (int i = 0; i < 1000000; i++)
	{
		if (harmasRelaciok[i] != 0)
		{
			fileki << harmasR_szavak[i] << " " << harmasRelaciok[i] << endl;
			cout << harmasR_szavak[i] << " " << harmasRelaciok[i] << endl;
		}
		else i = 1000000;
		
	}

	fileki.close();

	/*

	filebe.open("big.txt");
	sor = "";
	string output = "";
	while (getline(filebe, sor))
	{
		output += sor + " ";
	}
	filebe.close();



	fileki.open("text_szavak.txt");
	sor = "";
	teszt = 0;
	
	string *szavak = new string[1000000];

	int l = 0;
	int figy = 0;
	int szamlalo = 0;
	
		for (int k = 0; k < output.length() - 100; k++)
		{
			
			l = 1;
			bool space = false;
			bool veg = false;
			if (output[k] == ' ')
			{
				while (!veg)
				{
					if (output[k + l] >= 97 && output[k + l] <= 122)
					{
						szavak[szamlalo] += output[k + l];
					}
					else veg = true;
					if (output[k+l]==' ') space = true;
					l++;
				}

				if (!space) szavak[szamlalo] = '0';
				if (output[k + 1] == 'I' && output[k + 2] == ' ') szavak[szamlalo] = 'i';
				if (szavak[szamlalo] != "") { fileki << szavak[szamlalo] << endl; szamlalo++; }
				
			}
			if (l>1) k += l-2;
		}
		
	*/

/*
	int *szoRank_index = new int[10000];

	for (int i = 0; i < 10000; i++) szoRank_index[i] = i;

	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int j = 0; j < 9999; j++)
		{
			if (szo[j].szoRank_file < szo[j + 1].szoRank_file)
			{
				int k = szo[j].szoRank_file;
				szo[j].szoRank_file = szo[j + 1].szoRank_file;
				szo[j + 1].szoRank_file = k;

				k = szoRank_index[j];
				szoRank_index[j] = szoRank_index[j + 1];
				szoRank_index[j + 1] = k;
				swapped = true;
			}
		}
	}
	
	fileki.open("szoRank_file_szavak.txt");

	for (int i = 0; i < 10000; i++)
	{
		if (szo[i].szoRank_file != 0)
		{
			fileki << szo[szoRank_index[i]].szo << ";" << szo[i].szoRank_file << endl;
		}
	}



	fileki.close();


	*/



	/*
	string output = "";
	filebe.open("big.txt");
	sor = "";

	while (getline(filebe, sor))
	{
	output += sor + " ";
	}
	filebe.close();

	string output_teszt = "";
	filebe.open("teszt.txt");
	sor = "";

	while (getline(filebe, sor))
	{
	output_teszt += sor + " ";
	}
	filebe.close();
	*/




	//int l = 0;
	//int figy = 0;
	/*for (int i = 3969; i < 10000; i++)
	{

	string keres = " " + szo[i].szo + " ";

	for (int k = 0; k < output_teszt.length() - keres.length() - 1; k++)
	{
	figy = 0;
	l = 0;
	if (keres[0] == output_teszt[k])
	{

	while (figy < keres.length() && l<keres.length() - 1)
	{
	if (keres[l + 1] == output_teszt[k + l + 1]) l++;
	else figy = keres.length();
	}
	if (l == keres.length() - 1) szo[i].szoRank_file++;
	}
	k += l;
	}
	szo[i].melyik_file = 0;


	fileki << szo[i].szoRank_file << ";" << szo[i].melyik_file << endl;
	cout << szo[i].szoRank_file << "   " << i << "       " << szo[i].melyik_file << endl;

	}
	*/

	fileki.close();

}

int main(int argc, char* argv[])
{
	//unique_lock<std::mutex> lck(mtx); // needed so the threads cannot finish befor wait
	//thread t0(thread0),t1(thread1), t2(thread2), t3(thread3), t4(thread4), t5(thread5), t6(thread6), t7(thread7), t8(thread8), t9(thread9);

	//cv.wait(lck); // wait until one result
	thread2();
				  // here result is 0 or 1;

				  // If you use the loop described below, you can use join safely:
	/*t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();*/
	// You have to call join or detach of std::thread objects before the
	// destructor of std::thread is called. 

	_getch();
    return 0;
}

