#include <bits/stdc++.h>
#include "parser.cpp"
using namespace std;
class Simplex{
	public:
		Simplex(vector<vector<float>> initialtable,vector<string> identify){
			table =initialtable;
			width = initialtable[0].size();
			height = initialtable.size();
			identifiers = identify;
		}
		void print(){
			int maxlength = 0;
			vector<string> printtable {};
			printtable.push_back("P");
			string slack;
			for(auto x:identifiers){
				printtable.push_back(x);
			}
			for(int i=0;i<height-1;i++){
				slack = "s";
				slack += to_string(i+1);
				printtable.push_back(slack);
			}
			printtable.push_back("Value");
		
			for(auto cell:printtable){
				maxlength = cell.size() > maxlength ? cell.size() : maxlength;		
			}
				
			
			for(auto row:table){
				for(auto cell:row){
					maxlength = to_string(cell).size()>maxlength ? to_string(cell).size() : maxlength;
				}
			}
			
			for(auto cell:printtable){
				cout << "|" << cell;
				for(int i=0;i<maxlength-cell.size();i++){
					cout << " ";
				}

			}
			cout << "|\n";
			for(auto row : table){
				
				for(auto cell : row){
					
					cout << "|" << cell;
					for(int i=0;i<2*maxlength-2-to_string(cell).size();i++){
					cout << " ";
				}
				}
				cout << "|\n";
			}
		}
		void solve(){
			int iterations = 1;
			cout << "Initial state: " << "\n";
			print();
			cout << "\n";
			cout << "\n";
			while(iterate()){
				cout << "Iteration " << iterations << ":" << "\n";
				iterations+=1;
				print();
				cout << "\n";
				cout << "\n";
			}
			bool one;
			float cell;
			float value =0 ;
			bool nonbasic;
			for(int i = 1;i<identifiers.size()+1;i++){
				nonbasic = true;
				one = false;
				for(int j = 0;j<height;j++){
					cell = table[j][i];
					if(cell != 0){
						if(cell !=1){
							nonbasic = false;
						}else{
							if(one){
								nonbasic = false;
							}else{
								one = true;
								value = table[j][width-1];
							}

						}
					}
				}
				if(nonbasic){
					cout << identifiers[i-1] << ":" << value << "\n";
				}
			}
		}
		bool iterate(){
			float min = 0;
			int pivotcolumn = 0;
			for(int i = 1;i<width;i++)
			{
				float x = table[0][i];
				if(x < min){
					min = x;
					pivotcolumn =i;

				}
			
			}
			if(min == 0){
				return false;
			}
			min = 0.0;
			int pivotrow;
			float ratio = 0;
			float cellmin =0 ;
			for(int j = 1;j<height;j++){
				float value = table[j][width-1];
				float cell = table[j][pivotcolumn];
				if(cell > 0){
					ratio = value/cell; 
				}
				if ( min == 0 or (ratio >= 0 and ratio < min)){
					min = ratio;
					cellmin = cell;
					pivotrow = j;
				}
			}
			for(int i = 0 ;i<width;i++){
				table[pivotrow][i] = table[pivotrow][i]/cellmin;
			}
			float multiple;
			for (int j = 0;j<height;j++){
				if(j!=pivotrow){
					multiple = table[j][pivotcolumn];
					for(int i = 0;i<width;i++){
						table[j][i] = table[j][i] - multiple * table[pivotrow][i];
					}
				}
			}
			return true;
		}
	private:
		vector<vector<float>> table;
		vector<string> identifiers;
		int width;
		int height;
};

int main(){
	ifstream fin;
	fin.open("input.txt",ios::in);
	string input;
	string x;
	while(fin >> x){
		for(int i = 0;i<x.size();i++){
			input += x[i];
		}	
		input += " ";
	}
	Lexer lexer(input);
	vector<Token> tokens = lexer.lex();
	Parser parser(tokens);
	parser.parse();
	vector<vector<float>> table = parser.table();
	vector<string> identifiers = parser.getIdentifiers();
	Simplex simple(table,identifiers);
	simple.solve();	
}
