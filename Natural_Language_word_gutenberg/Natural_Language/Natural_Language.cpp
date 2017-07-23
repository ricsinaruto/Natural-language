


#include "stdafx.h"

using namespace std;
//mutex mtx;
//condition_variable cv;

int result = -1;

void thread0()
{
	ofstream fileki;
	ifstream filebe;

	int ossz = 100;
	int hanyadik = 0;
	string output = "";
	string bekert = "";
	string final = "";
	int stringmeret = 0;
	double talalatok = 0;

	filebe.open("wordlist.txt");
	int teszt = 0;
	string sor="";
	while (getline(filebe, sor))
	{
		
		
		fileki.open("google.txt");

			//string handling
			for (int i = 0; i < sor.length(); i++)
			{
				if (sor[i] == ';')
				{
					bekert = sor.substr(0, i);
					stringmeret = i;
				}
			}


			//HACKing
			if (teszt == 0)
			{
				output = "";
				bekert = "";
				final = "";
				stringmeret = 0;
				talalatok = 0;

				DWORD dwSize = 0;
				DWORD dwDownloaded = 0;
				LPSTR pszOutBuffer;
				string lol = "/search?q=" + bekert;
				wstring stemp = wstring(lol.begin(), lol.end());
				LPCWSTR sw = stemp.c_str();

				BOOL  bResults = FALSE;
				HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;


				// Use WinHttpOpen to obtain a session handle.
				hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

				// Specify an HTTP server.
				if (hSession) hConnect = WinHttpConnect(hSession, L"www.gutenberg.org", INTERNET_DEFAULT_HTTPS_PORT, 0);

				// Create an HTTP request handle.
				if (hConnect) hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/cache/epub/3775/pg3775.txt", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

				// Send a request.
				if (hRequest) bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

				// End the request.
				if (bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);

				// Keep checking for data until there is nothing left.
				if (bResults)
				{
					do
					{
						// Check for available data.
						dwSize = 0;
						if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
						{
							printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
							break;
						}

						// No more available data.
						if (!dwSize) break;

						// Allocate space for the buffer.
						pszOutBuffer = new char[dwSize + 1];
						if (!pszOutBuffer)
						{
							printf("Out of memory\n");
							break;
						}

						// Read the Data.
						ZeroMemory(pszOutBuffer, dwSize + 1);

						if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
						{
							printf("Error %u in WinHttpReadData.\n", GetLastError());
						}
						else
						{
							output += pszOutBuffer;
							//fileki << pszOutBuffer;
						}

						// Free the memory allocated to the buffer.
						delete[] pszOutBuffer;

						// This condition should never be reached since WinHttpQueryDataAvailable
						// reported that there are bits to read.
						if (!dwDownloaded) break;

					} while (dwSize > 0);
				}

				else
				{
					// Report any errors.
					printf("Error %d has occurred.\n", GetLastError());
				}
				// Close any open handles.
				if (hRequest) WinHttpCloseHandle(hRequest);
				if (hConnect) WinHttpCloseHandle(hConnect);
				if (hSession) WinHttpCloseHandle(hSession);
			}
			

			
			int i = 0;
			int j = 0;
			for (i = 0; i < output.length(); i++)
			{
				if (output.substr(i, stringmeret) == bekert) j++;
			}
			
			
			cout << j<<"  "<<bekert<< "\n";
			fileki.close();

			teszt++;
			// got a result? publish it!
			//unique_lock<std::mutex> lck(mtx);
			//	if (result != -1)
			//	return; // there is already a result!

			//result = 0; // my result
			//cv.notify_one(); // say I am ready
		
	}

	filebe.close();
}

//kéne még egy fájlba elmenteni a beszélgetéseket, hogy legyen komolyabb memóriája
int main(int argc, char* argv[])
{
	//unique_lock<std::mutex> lck(mtx); // needed so the threads cannot finish befor wait
	//thread t0(thread0),t1(thread1), t2(thread2), t3(thread3), t4(thread4), t5(thread5), t6(thread6), t7(thread7), t8(thread8), t9(thread9);

	//cv.wait(lck); // wait until one result
	thread0();
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

