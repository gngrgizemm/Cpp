#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

//Akan veri ile standart sapma ve ortalama sapma hesaplayan program

using namespace std;

void standart_sapma(int arr[],int size){
double sum_sq=0.0,sum_sr=0.0,mean=0.0; 
double varyans,std_sp;
int step=0;

for(int j=0;j<size;j++){
    step=step+1;
    sum_sr += arr[j];
    sum_sq += arr[j]*arr[j];
    mean=sum_sr/step;
    if(step==1){
        std_sp=0;
    }else{
    varyans=fabs((sum_sq-(pow(sum_sr,2)/step))/(step-1));
    std_sp=pow(varyans,0.5);
    cout<<"Eleman sayisi: "<<j+1<<endl;
    cout<<"Standart sapma: "<<std_sp<<endl;
    cout<<"Ortalama deger: "<<mean<<endl;
    cout<<endl;
    
}
}
}
void ortalama_sapma(int arr[],int size){
   double mean,mean_sp;
   int step=0;
   
   for(int j=0;j<size;j++){
        double sum=0.0;
        double sum_sr=0.0;
         step+=1;
      for(int k=0;k<=j;k++){
           sum+=arr[k];
      }
      mean=sum/step;
      for(int l=0;l<=j;l++){
           sum_sr +=abs(arr[l]-mean);
      }
      mean_sp=sum_sr/step;
      cout<<"Eleman sayisi: "<<j+1<<endl;
      cout<<"Ortalama sapma: "<<mean_sp<<endl;
      cout<<endl;
      
   }
}
void input(int num){
  int point;
  ofstream file;
  file.open("point.txt");
  for(int j=0;j<num;j++){
    point=1+rand()%100;
    file<<point<<endl;
  }
  file.close();
}
int *read(int num){
  int *point;
  point=new int[num];
  for(int i=0;i<num;i++){
    point[i]=0;
  }
  int buf; 
  int count=0;
  ifstream read("point.txt");
  while ( count<point[num] && read >> buf){
			point[count++] = buf;
  }
  read.close();
  return point;
}

int main(){
    int points_num;
    cout<<"Not Sayisini giriniz: "<<endl;
    cin>>points_num;
    input(points_num);
    int *arr_val=read(points_num);
    standart_sapma(arr_val,points_num);
    ortalama_sapma(arr_val,points_num);
return 0;
}