#include <fstream>
#include <stdlib.h>
#include<random>
#include<iostream>
#include<ctime>
using namespace std;
int main(){
	fstream out("data/data_500.txt", ios::out);
	default_random_engine e(time(0));
	uniform_real_distribution<double> u(-6.6,6.6);
	for(int j=0; j<=500; j++){
            out<< j << " " << u(e) << endl; //生成-6.6到6.6之间的小数.
	}
	out.close();
	return 0;
}
