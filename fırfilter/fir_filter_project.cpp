#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "string.h"
char* read_wav(const char* filename, short*, short*, int*);  //read wav file
void write_wav(const char* filename, const char*, int);  // write output wav file


/*#define FILTER_LEN  63
//http://t-filter.engineerjs.com/ adresinden rastgele örnek olarak alınmıştır.
double coeffs[FILTER_LEN] =
{
  -0.0448093,  0.0322875,   0.0181163,   0.0087615,   0.0056797,
   0.0086685,  0.0148049,   0.0187190,   0.0151019,   0.0027594,
  -0.0132676, -0.0232561,  -0.0187804,   0.0006382,   0.0250536,
   0.0387214,  0.0299817,   0.0002609,  -0.0345546,  -0.0525282,
  -0.0395620,  0.0000246,   0.0440998,   0.0651867,   0.0479110,
   0.0000135, -0.0508558,  -0.0736313,  -0.0529380,  -0.0000709,
   0.0540186,  0.0766746,   0.0540186,  -0.0000709,  -0.0529380,
  -0.0736313, -0.0508558,   0.0000135,   0.0479110,   0.0651867,
   0.0440998,  0.0000246,  -0.0395620,  -0.0525282,  -0.0345546,
   0.0002609,  0.0299817,   0.0387214,   0.0250536,   0.0006382,
  -0.0187804, -0.0232561,  -0.0132676,   0.0027594,   0.0151019,
   0.0187190,  0.0148049,   0.0086685,   0.0056797,   0.0087615,
   0.0181163,  0.0322875,  -0.0448093
};*/

using namespace std;

int main()
{
	int coeff_num, secim;
	double* coeffs;

	cout << "FIR FILTER..." << endl;
	cout << "FIR filter katsayi adedini giriniz: ";
	cin >> coeff_num;
	
	coeffs = new double[coeff_num];
	cout << "FIR filtre katsayilarinin nasil verilecegini seciniz \n 1-komut satiri \n 2-dosyadan okutma"<<endl;
	
	cin >> secim;
	switch (secim) {
	case 1:
		for (int i = 0; i < coeff_num; i++)
		{
			cin >> coeffs[i];
		}
		break;
	case 2:
		std::ifstream inputFile;
		inputFile.open("input.txt");  //FIR coeff file
		for (int i = 0; i < coeff_num; i++)
		{
			inputFile >> *(coeffs + i);
				
		}
		inputFile.close();

	}
	short nchannel, ssample;
	int csample;
	string wavfile;  //sample wavfile
	cout << "wav dosyasının ismini giriniz: ";
	cin >> wavfile;
	char* buffer = read_wav(wavfile.c_str(), &nchannel, &ssample, &csample);
	short* data = (short*)&buffer[44];

	short* samp = (short*)malloc(sizeof(short) * csample);


	double acc;     // accumulator 
	double* coeffp; // pointer to coefficients
	short* inputp; // pointer to input samples
	int n;
	int k;

	// apply the filter to each input sample
	for (n = 0; n < csample; n++) {
		// calculate output n
		coeffp = coeffs;
		inputp = &data[coeff_num - 1 + n];
		acc = 0.0;
		for (k = 0; k < coeff_num; k++) {
			acc += (*coeffp++) * (*inputp--);
		}
		samp[n] = acc;
	}

	for (n = 0; n < csample; n++)
		data[n] = samp[n];

	write_wav("test.wav", buffer, csample * ssample + 44);   //filtered wav file
	return 0;
}


char* read_wav(const char* filename, short* nchannel, short* ssample, int* csample) {

	FILE* fp = fopen(filename, "rb");   //open wav file

	if (!fp) {
		fprintf(stderr, "Couldn't open the file \"%s\"\n", filename);
		exit(0);
	}

	fseek(fp, 0, SEEK_END);
	int file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	printf("The file \"%s\" has %d bytes\n\n", filename, file_size);

	char* buffer = (char*)malloc(sizeof(char) * file_size);
	fread(buffer, file_size, 1, fp);


	*nchannel = *(short*)&buffer[22];
	*ssample = *(short*)&buffer[34] / 8;
	*csample = *(int*)&buffer[40] / *ssample;

	printf("ChunkSize :\t %u\n", *(int*)&buffer[4]);
	printf("Format :\t %u\n", *(short*)&buffer[20]);
	printf("NumChannels :\t %u\n", *(short*)&buffer[22]);
	printf("SampleRate :\t %u\n", *(int*)&buffer[24]);	// number of samples per second
	printf("ByteRate :\t %u\n", *(int*)&buffer[28]);		// number of bytes per second
	printf("BitsPerSample :\t %u\n", *(short*)&buffer[34]);
	printf("Subchunk2ID :\t \"%c%c%c%c\"\n", buffer[36], buffer[37], buffer[38], buffer[39]);	// marks beginning of the data section
	printf("Subchunk2Size :\t %u\n", *(int*)&buffer[40]);		// size of data (byte)
	printf("Duration :\t %fs\n\n", (float)(*(int*)&buffer[40]) / *(int*)&buffer[28]);

	fclose(fp);
	return buffer;
}

void write_wav(const char* filename, const char* data, int len) {
	FILE* fp = fopen(filename, "wb"); 

	if (!fp) {
		fprintf(stderr, "Couldn't open the file \"%s\"\n", filename);
		exit(0);
	}

	fwrite(data, len, 1, fp);
	fclose(fp);
}
