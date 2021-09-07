#include <bits/stdc++.h>
using namespace std;
#include "lexer.cpp"
struct Expression {
	vector<Token> tokens;
};
struct Constraint {
	Expression expr1;
	Token rel;
	Expression expr2;
	
};

class Parser{
	public:
		Parser(vector<Token> tokens){
			input = tokens;
		}
		void parse(){
			pointer =0;
			token = input[0];
			identifiers.clear();
			sentence();
		}
		void sentence(){
			if(pointer<input.size()){
				if(token.type == "id" or token.type == "num"){
				term();
				
				sentence();
			}
			}
			
			
		}
		void term(){
			if(pointer < input.size()){
				if(token.type == "id" or token.type == "num"){
				Expression expr1 = expr();
				if(pointer < input.size() and token.type == "rel"){
					Token relation = token;
					match('+');
					Expression expr2 = expr();
					Constraint constraint = {expr1,relation,expr2};
					constraints.push_back(constraint);
				}else{
					maximize = expr1;
				}
			}
			}
		}
		Expression expr(){
			vector<Token> tokens {};
			if(pointer < input.size()){
				if(token.type == "id" or token.type == "num"){
					
					tokens.push_back(token);
					match('+');
					for(auto thing:rightexpr().tokens){
						tokens.push_back(thing);
					}
				}
			}
			Expression expr {tokens};
			return expr;
		}
		Expression rightexpr(){
			vector<Token> tokens {};
			if(pointer < input.size()){
				if(token.type == "add"){
					match('+');
					if(pointer<input.size() and (token.type == "id" or token.type == "num")){
						
						tokens.push_back(token);
						match('+');

						for(auto thing:rightexpr().tokens){
							tokens.push_back(thing);
						}
					}
				}
			}
			Expression expr {tokens};
		
			return expr;
		}
		void match(char t){
			pointer+=1;
			if(pointer < input.size()){
			token = input[pointer];
			}
		}
		vector<vector<float>> table(){
			vector<vector<float>> table{};
			vector<float> row {1};
			for(auto x:maximize.tokens){
				identifiers.push_back(x.name);
				reverse[x.name] = identifiers.size()-1;
				row.push_back(-x.val);
			}
			for(auto constraint : constraints){
				row.push_back(0);

			}
			row.push_back(0);
			table.push_back(row);
			int l = 0;
			for(auto constraint:constraints){
				row.clear();
				for(int i = 0 ;i<identifiers.size()+constraints.size()+2;i++){
				row.push_back(0);
			}
				row[identifiers.size()+1 +l] = 1;
				row[identifiers.size()+constraints.size()+1] = (constraint.expr2.tokens)[0].val;

				for(auto thing :constraint.expr1.tokens){
					row[1+reverse[thing.name]] = thing.val;
				}
				table.push_back(row);
				l+=1;
			}
			return table;
			

		}
		vector<string> getIdentifiers(){
			return identifiers;
		}

	private:
		int pointer;
		Token token;
		vector<Token> input;
		vector<Constraint> constraints;
		Expression maximize;
		vector<string> identifiers;
		map<string,int> reverse;

};
