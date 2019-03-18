#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<string>
#include <math.h>

std::vector<std::string> split(std::string str, std::string pattern) {
  std::size_t pos;
  std::vector<std::string> result;
  str += pattern;
  int size = str.size();
  int i = 0;
  while (i < size) {
    pos = str.find(pattern, i);
    if (pos < size) {
      std::string s = str.substr(i, pos - i);
      result.push_back(s);
      i = pos + pattern.size() - 1;
    }
    i++;
  }
  return result;
}

void input(std::string path, std::vector<double> &Data1, std::vector<double> &Data2, std::vector<double> &Data3){
	std::ifstream fin(path,std::ios::in); 
	std::string line;
	double position1,position2,position3;
	while(getline(fin, line)) {
		// id = std::stoi(split(line, " ")[0]); //数据的id
		position1 = std::stod(split(line, " ")[1]); //数据的横坐标值
		position2 = std::stod(split(line, " ")[2]); //数据的纵坐标值
		position3 = std::stod(split(line, " ")[3]); //数据的高度坐标值
		Data1.push_back(position1);
		Data2.push_back(position2);
		Data3.push_back(position3);
	}
	fin.close();
	std::cout<<"Data1.size="<<Data1.size()<<",Data2.size="<<Data2.size()<<",Data3.size="<<Data3.size()<<std::endl;
	std::cout<<"input down."<<std::endl;
}

void KNN(std::vector<double> Data1, std::vector<double> Data2, std::vector<double> Data3, int k){
	std::vector<double> density;
	density.resize(Data1.size());
	std::cout<<"density.size="<<density.size()<<std::endl;
	int i,j;
	for(int index=0; index<Data1.size(); index++){
		std::set<double> temp;
		for(int i=0; i<Data1.size(); i++){
			if(i != index){
				temp.insert( sqrt( pow((Data1[index]-Data1[i]),2) + pow((Data2[index]-Data2[i]),2) + pow((Data3[index]-Data3[i]),2) ) );
			}
		}
		int pos = 0;
		for(auto u : temp){
			pos++;
			if(pos == k){
				density[index] = 1 / u;
				break;
			}
		}
		// std::cout<<index<<" "<<density[index]<<std::endl;	
	}
	std::fstream out("./density.txt", std::ios::out);
	for(int i=0; i<density.size(); i++){
		// out << i << " " << density[i] << std::endl;	
		out << Data1[i]<<" "<<Data2[i]<<" "<<Data3[i]<<" "<< density[i] << std::endl;
	}
	out.close();
}

int main(){
	std::vector<double> Data1, Data2, Data3;
	input("./data.txt", Data1, Data2, Data3);
	KNN(Data1, Data2, Data3, 900);
	return 0;
}

// g++ KNN-algorithm.cpp --std=c++11
