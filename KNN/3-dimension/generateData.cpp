#include <fstream>
#include <stdlib.h>
#include<random>
#include<iostream>
#include<ctime>
using namespace std;
int main(){
	fstream out("data.txt", ios::out);
	default_random_engine e(time(0));
	uniform_real_distribution<double> u(-16.6,16.6);
	for(int j=0; j<=1000; j++){
            out<< j << " " << u(e) << " " << u(e) << " " << u(e)  << endl; //生成-16.6到16.6之间的小数.
	}
	out.close();
	return 0;
}
