#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <iomanip>

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14f
#define L2B_ENDIAN(n) (((n) >> 24)&0xff) | (((n) << 8) & 0xff0000) | (((n) >> 8) & 0xff00) | (((n) << 24) & 0xff000000)

using namespace std;

char* read_wav(const char* filename, short* nchannel, short* ssample, int* csample) {

	FILE* fp = fopen(filename, "rb");

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

	cout<<"ChunkSize :      "<< *(int*)&buffer[4]<<endl;
	cout<<"Format :         "<<*(short*)&buffer[20]<<endl;
	cout<<"NumChannels :    "<<*(short*)&buffer[22]<<endl;
	cout<<"SampleRate :     "<< *(int*)&buffer[24]<<endl;
	cout<<"ByteRate :       "<<*(int*)&buffer[28]<<endl;
	cout<<"BitsPerSample :  "<<*(short*)&buffer[34]<<endl;
	cout<<"Subchunk2ID :    "<<buffer[36]<<buffer[37]<<buffer[38]<<buffer[39]<<endl;
	cout<<"Subchunk2Size :  "<<*(int*)&buffer[40]<<endl;
	cout<<"Duration :       "<<(float)(*(int*)&buffer[40]) / *(int*)&buffer[28]<<endl;
	cout<<endl;

	fclose(fp);
	return buffer;
}


int main()
{
    short nchannel, ssample;
    int csample;
    char* buffer = read_wav("PinkPanther60.wav", &nchannel, &ssample, &csample);
    short* data = (short*)&buffer[44];
    int XX = 512;
    int X = XX / 2;
    double* R_X = (double*)malloc(sizeof(double) * X);
    double* IM_X = (double*)malloc(sizeof(double) * X);
    for (int i= 0; i < X; i++) {
        R_X[i] = 0.0f;
        IM_X[i] = 0.0f;
    }
    for(int k=0;k<X;k++){
        for (int i = 0; i < XX; i++) {
            R_X[k] += data[i * csample / XX] * cos(2 * PI * k * i / XX);
            IM_X[k] -= data[i * csample / XX] * sin(2 * PI * k * i / XX);
        }
    }


    cout<<"Re_f"<<setw(17)<<"Im_f"<<endl;
    for(int i = 0; i < X; i++){
        cout<<R_X[i];;
        cout<<setw(17);
        cout<< IM_X[i]<<endl;
}

    for(int i = X-1 ; i >0; i--)
    {
        R_X[i]=R_X[i-1];
        IM_X[i]=IM_X[i-1];
    }
    R_X[0]=value;
    IM_X[0]=value;
    for(int i=0; i<X;i++)
    {
        R[i] += R_X[i]*h[i];
        IM[i] += IM_X[i]*h[i];

    }





}



/*float FIR_filter(float value)
{
    for(int i=step-1 ; i>0; i--)
    {
        buffer[i]=buffer[i-1];
    }
    buffer[0]=value;
    for(int i=0; i<step;i++)
    {
        output += buffer[i]*h[i];

    }
    return output;
}*/
