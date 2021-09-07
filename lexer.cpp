#include <bits/stdc++.h>
using namespace std;
struct Token{
	string name;
	string type;
	int val;
};
class Lexer{
	public:
		Lexer(string text){
			input = text;
		}
		vector<Token> lex(){
			int pointer = 0;
			set<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
			string alpha = "abcdefghijklmnopqrstuvwxyz";
			vector<Token> tokens {};
			set<char> alphabet {};
			for(auto character : alpha){
				alphabet.insert(character);
			}
				
			while (pointer < input.size()){
				char term = input[pointer];
				if(term == '+'){
					tokens.push_back({"+","add",0});
				}else if(term == '<'){
					if(pointer+1<input.size() and input[pointer+1] == '='){
						tokens.push_back({"<=","rel",0});
						pointer+=1;
					}else{
						tokens.push_back({"<","rel",0});
					}

				}else if(term == '>'){
                                        if(pointer+1<input.size() and input[pointer+1] == '='){
                                                tokens.push_back({">=","rel",0});
                                                pointer+=1;
                                        }else{     
                                                tokens.push_back({">","rel",0});
                                        }       
                                        
                                }else if (term == '='){
					tokens.push_back({"=","rel",0});
				}
				if(digits.find(term) != digits.end()){
					string l = "";
					int currentpointer = pointer;
					int coefficient = 0;
					int coefflength = 0;
					bool done = false;
					while(digits.find(input[currentpointer]) !=digits.end() or alphabet.find(input[currentpointer])!=alphabet.end()){
						if(alphabet.find(input[currentpointer])!=alphabet.end()){
						done = true;
						coefficient = stoi(l);
						coefflength = l.size();
						l  = "";
				}
						l += input[currentpointer];					      	
						currentpointer++;

					}
					if(done){
					tokens.push_back({l,"id",coefficient});
					}else{
					tokens.push_back({l,"num",stoi(l)});
					}
					pointer +=(coefflength+l.size()-1);
				}
				if(alphabet.find(term) !=alphabet.end()){
					string l ="";
					int currentpointer = pointer;
					while(digits.find(input[currentpointer])!=digits.end() or alphabet.find(input[currentpointer])!=alphabet.end()){
					l+=input[currentpointer];
					currentpointer++;
			}
					tokens.push_back({l,"id",1});
					pointer+=(l.size()-1);
				}
				
				pointer+=1;	
			}
			return tokens;
		}
	private:
		string input;
		

};
