#include "stdafx.h"

using namespace std;

//save conversations to a file to have longer memory
int main(int argc, char* argv[])
{
	cout << "hey" << "\n";
	
	pcg32_random_t rng;
	pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&rng);	//random number generator


	
	int karakterek[400] = { 0 };
	int space = 1;

	for (int i = 0; i < 1000; i++)
	{
		string s;
		getline(cin, s);
		

		int valaszmeret = 0;
		while (valaszmeret<2) valaszmeret = (((double)pcg32_boundedrand_r(&rng, 1000000000)) / 250000000-1)*s.length();
		int szam = s.length() / 3 + 1;

		for (int j = 0; j <= valaszmeret; )
		{
			double nullaegy[100];
			double oszto = 0;
			
			for (int k = -szam; k <= szam; k++)
			{
				if (k != 0)
				{
					nullaegy[k+szam] = (((double)pcg32_boundedrand_r(&rng, 1000000000)) / 1000000000+0.5) * ((double)szam / abs((double)k));
					oszto += (double)szam / abs((double)k);
					
					//to handle differences between input and output string size
					if (j + k >= 0 && j + k < s.length())
					{
						if (s[j + k] != 32)				karakterek[j] += (double)s[j + k] * nullaegy[k + szam];
						else							karakterek[j] += (double)110 * nullaegy[k + szam];
					}
						
					else if (j + k < 0)
					{
						if (s[abs(j + k) + j] != 32)	karakterek[j] += (double)s[abs(j + k) + j] * nullaegy[k + szam];
						else							karakterek[j] += (double)110 * nullaegy[k + szam];
					}
						
					else if (j - k < s.length())
					{
						if (s[j - k] != 32)				karakterek[j] += (double)s[j - k] * nullaegy[k + szam];
						else							karakterek[j] += (double)110 * nullaegy[k + szam];
					}
						
					else if (j-abs(k)>=0)
					{
						if (karakterek[j - abs(k)] != 32)	karakterek[j] += (double)karakterek[j - abs(k)] * nullaegy[k + szam];
						else								karakterek[j] += (double)110 * nullaegy[k + szam];
					}
					else karakterek[j] += (double)110 * nullaegy[k + szam];
					
				}
				
				
			}

			karakterek[j] = (double)karakterek[j] / oszto;

			if (karakterek[j] > 96 && karakterek[j] < 123)
			{
				char c = karakterek[j];
				//cout << karakterek[j] << "\n";
				cout << c;

				//rng
				double z = 0;
				double xr=0, yr=0;
				while (z <= 0 || z >= 1)
				{
					xr = ((double)pcg32_boundedrand_r(&rng, 1000000000)) / 500000000 - 1;
					yr = ((double)pcg32_boundedrand_r(&rng, 1000000000)) / 500000000 - 1;
					z = xr*xr + yr*yr;

				}

				//gaussian random number
				double distro = 5 + xr * 1 * sqrt(-2 * log(z) / z);

				if ((double)j / space > distro) { cout << " "; space++; }
				j++;
			}
			else karakterek[j] = 0;
			
			
		}


		cout << "\n";
		space = 1;
	}
	


	_getch();
    return 0;
}

