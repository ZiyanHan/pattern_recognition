#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<string>

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

void input(std::string path, std::vector<double> &Data){
	std::ifstream fin(path,std::ios::in); 
	std::string line;
	double position;
	std::set<double> SourceData;
	while(getline(fin, line)) {
		// id = std::stoi(split(line, " ")[0]); //数据的id
		position = std::stod(split(line, " ")[1]); //数据的坐标值
		SourceData.insert(position);
	}
	std::cout<<"SourceData.size="<<SourceData.size()<<std::endl;
	for(auto pos : SourceData){
		Data.push_back(pos);
	}
	fin.close();
	std::cout<<"input down."<<std::endl;
	std::cout<<"data.size="<<Data.size()<<std::endl;
}

void KNN(std::vector<double> Data, int k){
	std::vector<double> density;
	density.resize(Data.size());
	std::cout<<"data.size="<<Data.size()<<", density.size="<<density.size()<<std::endl;
	int i,j;
	for(int index=0; index<Data.size(); index++){
		for(i=index; i>=0&&i>=(index-k); i--);                 // <--
		for(j=index; j<Data.size()&&j<=(index+k); j++);        // -->
		density[index] = 1 / ((Data[j-1] - Data[i+1])/2);
		// std::cout<<index<<" "<<density[index]<<std::endl;	
	}
	std::fstream out("./density.txt", std::ios::out);
	for(int i=0; i<density.size(); i++){
		out << i << " " << density[i] << std::endl;	
	}
	out.close();
	std::cout<<Data[0]<<" "<<Data[1]<<" "<<Data[2]<<" "<<Data[3]<<" "<<Data[4]<<" "<<Data[5]<<" "<<Data[6]<<" "<<Data[7]<<std::endl;
}

int main(){
	std::vector<double> Data;
	input("./data.txt", Data);
	KNN(Data, 3);
	return 0;
}

// g++ KNN-algorithm.cpp --std=c++11
