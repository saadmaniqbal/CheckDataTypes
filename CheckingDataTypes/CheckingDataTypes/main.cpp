#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include<sstream>
#include <iterator>
#include <cctype>
//#include<regex>
#include <algorithm>

using namespace std;


string checkDataType_add(string key, string str, std::map<std::string, std::string>& data_type) {
	//need to find type based on everything after the = sign.
	if (data_type.find(key) == data_type.end()) {
		size_t found_double = str.find("\"");
    size_t found_single = str.find("'");
		if (found_single != string::npos||found_double != string::npos)
			//cout << "First occurrence is " << found << endl;
			data_type.insert({ key, "string" });
		else if (std::string::npos != str.find_first_of("0123456789")) {
			//std::cout << "digit(s)found!" << std::endl;
			data_type.insert({ key, "int" });
		}


	}



	std::map<string, string>::iterator it;

	string val;
	it = data_type.find(str);
	if (it != data_type.end())
		val = it->second;

	return val;
}


string checkDataType_exists(string str, std::map<std::string, std::string>& data_type) {
	//need to find type based on everything after the = sign.

	std::map<string, string>::iterator it;
	string val;

	size_t found_double = str.find("\"");
  size_t found_single = str.find("'");
	if (found_single != string::npos||found_double != string::npos) {
		//cout << "First occurrence is " << found << endl;
		val = "string";
		return val;
	}
	else if (std::string::npos != str.find_first_of("0123456789")) {
		it = data_type.find(str);
		if (it != data_type.end()) {
			val = it->second;

		}
		else
			val = "int";
		return val;

	}




	it = data_type.find(str);
	if (it != data_type.end())
		val = it->second;

	return val;
}


string handle_if(string str){
  //this is to handle every type of comparisons that may arise

  string newstr = "";
  if(str.find("if") < 10000){
    int pos1 = str.find("if");
    int pos2 = str.find("else");
    size_t conditional_gt = str.find(">");
    size_t conditional_gte= str.find(">=");
    size_t conditional_lt = str.find("<");
    size_t conditional_lte = str.find("<=");
    size_t conditional_e = str.find("==");

    //if (found!=std::string::npos)

    //cout << conditional_e <<endl;

    for(int i=0; i<str.length(); i++){
      if(i == pos1){
        newstr += " if ";
        i+=1;
      }
      else if(i == pos2){
        newstr += " else ";
        i+=3;
      }

      else if(i == conditional_gt && conditional_gte >10000){
        newstr += " > ";
      }
      else if(i == conditional_gt && conditional_gte > 10000){
        newstr += " >= ";
        i+=1;
      }

      else if(i == conditional_lt&& conditional_lte >10000){
        newstr += " < ";
      }
      else if(i == conditional_lt && conditional_lte <10000){
        newstr += " <= ";
        i+=1;
      }
      
      else if(i == conditional_e){
        newstr += " == ";
        i+=1;
      }
      else{
        newstr += str[i];
      }
    }
    
  }
  return newstr;
}

string addspace(string str) {
	string newstr = "";
  //this deals with the print statement only
	if (str.find("print") == 0) {
		newstr = "print ";
		for (int i = 5; i < str.length();i++) {
      if (str[i] == '(') {
				newstr = newstr + "( ";
			}
      else if (str[i] == ')') {
				newstr = newstr + " )";
			}
      else if (str[i] == '[') {
				newstr = newstr + " [ ";
			}
      else if (str[i] == ']') {
				newstr = newstr + " ]";
			}
      else if (str[i] == ':') {
				newstr = newstr + " : ";
			}

			else if (str[i] == '=') {
				newstr = newstr + " = ";
			}
			else if (str[i] == '+') {
				newstr = newstr + " + ";
			}
			else if (str[i] == '*') {
				newstr = newstr + " * ";
			}
			else {
				newstr += str[i];
			}
		}

		return newstr;
	}

  //if(str.find("if") < 10000){
   // str = handle_if(str);
  //}

  

	for (int i = 0; i < str.length(); i++) {
    if(str[i] == '('){
      continue;
    }
    else if(str[i] == ')'){
      continue;
    }

    else if (str[i] == '['){
      newstr = newstr + "[ ";
    }
    else if (str[i] == ']'){
      newstr = newstr + " ]";
    }
		else if (str[i] == '=') {
      if(str[i-1] == '>' || str[i-1] == '<' || str[i+1] == '='||str[i-1] == '='){
        newstr += str[i];
      }
      else{
			newstr = newstr + " = ";
      }
		}
		else if (str[i] == '+') {
			newstr = newstr + " + ";
		}
		else if (str[i] == '*') {
			newstr = newstr + " * ";
		}
   
    

		else {
			newstr += str[i];
		}
	}

  if(str.find("if") < 10000){
    newstr = handle_if(newstr);
  }

	return newstr;
}



bool isPresent(string key, std::map<std::string, std::string>& data_type) {
	if (data_type.find(key) == data_type.end()) {
		// not found
		return false;
	}
	return true;
}


string addspace_paren(string str) {
	string newstr = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			newstr = newstr + " ";
		}
		else if (str[i] == ')') {
			newstr = newstr + "";
		}
		else if (str[i] == ',') {
			newstr = newstr + " ";
		}

		else {
			newstr += str[i];
		}
	}
	return newstr;

}


int main(/*int argc, char *argv[]*/) {

  map<string, string> data_type;
  map<string, string> data_value;
  ifstream inputFile;
	ofstream outputFile;
	inputFile.open("tc2.py");

  string message="";

  int n = 1;
  int line_num = 1;
  while (getline(inputFile, message)) {
		//get the individual lines of codes
    string printed;
    bool need_to_print = false;
    string final_message = message;
    

		//remove all the spaces present
		message.erase(remove(message.begin(), message.end(), ' '), message.end());

    if(message.length() == 0){
      cout << endl;
      continue;
    }

		//checking for an empty line
		if (message.length() != 0) {
      
			

			//if (std::find_if(message.begin(), message.end(), isspace)) != userName.end()){

		  //keep an eye on this

			//find = and * and +, put a space before and after each of them

			string n_message;
			//message = trim(message);
			//string temp = message;


			//this becomes redundant, but lets move on.
			message.erase(remove(message.begin(), message.end(), ' '), message.end());

			//add spaces to only where i want to, look at the function above.
			//message = addspace_paren(message);
      //addspace_paren call only when needed, not everytime for now.
			n_message = addspace(message);

      //cout << n_message <<endl;
			//break down the line of code

			stringstream line(n_message);
			string token;

			//this will contain each of the words separated by a space

			vector<string> token_container;
			vector<string>::iterator it;
			//cout << "line " << n <<" tokens" << endl;
			//n++;


			while (getline(line, token, ' ')){
				token_container.push_back(token);
        //cout << token <<endl;
      }

      //we will be checking the first element in the vector for variable assignments, prints.
			//if the first element is a variable assignment, check for an if/else in the same line.

			//assignments can be: lists(this can include integers, strings, variables of integer/strings), addition of two list variables, addition of list literal with list variables
			//assignment can also be a string or int variable converted to a list.

			//for assignments, check for square brackets, if present then,
			//check for "+", if not present, then
			//check for commas,
			//if present, then parse every token separated by a comma
			//for each token, check if token is a variable(go through variable list)
			//or if they are string or ints
			//first iteration assigns the type of the list

			//if "+" present, then check for parentheses, if found then
			//iterate till the ")", and add it together, and assign it to the variable
			//then for the rest of the part, add them too. they have to be lists themselves as well

			//if no parentheses, then add them together, and then assign list value to variable

			//for every addition, check left and right summands, check their data type
			//if they contain square brackets, then, check inside it and, determine them, and 
			//add them, and then assign them to the left hand side summand. repeat with lhs + rhs, lhs now being the summation of everything up to that point.
			//keep doing it until there are no more "+"

			//for if and else, will be in a single line of code
			//every if line will start with a variable assignment
			//check for "if" first, (a>b), operator define beforehand ">" example
			// left > right, bool true, then go back to assignment part token_container[0]
			//assign the value to that variable, if bool false, then assign everything after "else"
			//to that variable

			//for prints
			//scan for square brackets, if none present then,
			//cout or write in a file, the variable mentioned between print parentheses

			//if square brackets present
			//pick the variable mentioned for the square bracket
			//check for colon, if no colon then,
			//output the index numbered element frrom the python list

			//if colon present then,
			//get value before colon, and after colon.
			//run a loop, and output every element from before to after.

			//no functions

			//no multi lined conditionals


      
      //cout << token_container[0] <<endl;
      if (token_container[0] != "print" /*&& token_container[0] != "if" && token_container[0] != "else"*/) {

				//need to remove any white spaces

				int count = 0;
				//bool eval = false;


        


				
				for (auto i : token_container) {

					//if the line contains a "="
					if (i == "=") {

						string exp = "";
						bool eval;
            bool conditional = false;
            int if_index, else_index;
						for (int i = count + 1; i < token_container.size(); i++) {

							// this loop checks if the lines contain operators or conditions, bool is used to indicate this
              if (token_container[i] == "if"){
                conditional = true;
                if_index = i;
                
                
              }

              if(token_container[i] == "else"){
                else_index = i;
              }

							if (token_container[i] == "+" || token_container[i] == "*") {
								//cout << "line number: " << n << " has + or -" << endl;
								eval = true;
								break;
							}
							else {
								//cout << "entering eval false condition for line "<<n << endl;
								eval = false;

							}
						}

						/*if (eval == true) {
							cout << "eval for line " << n << " is true" << endl;
						}
						else {
							cout << "eval for line " << n << " is false" << endl;
						}*/

						//if the line contains a conditional
            if(conditional == true){
              
              //since everything is well defined inside the token_container with fixed locations
              //the following assignments are made 
              
              //this is the variable being compared
              string var_comp = token_container[if_index+1];
              //find the actual value of the variable

              //this is the value and type of the above variable
              string var_comp_val = data_value[var_comp];
              string var_comp_type = data_type[var_comp];

              //this is the operator used for comparison, and whatever it is being compared to
              string comp = token_container[if_index+2];
              string comp_literal = token_container[if_index+3];
              int var_comp_val_int;
              int comp_literal_int;
              //cout << var_comp_val <<endl;

              //if the comparison is between ints, change the operands to ints
              
              
              map<string, string>::iterator it;
              it = data_value.find(comp_literal);
              if(it != data_value.end()){
                comp_literal = it->second;
              }
              
              //cout << comp_literal <<endl;
              


              if (var_comp_type == "int"){
                //cout << var_comp_val <<endl;
                var_comp_val_int = stoi(var_comp_val);
                //cout << var_comp_val <<endl;
                comp_literal_int = stoi(comp_literal);
              }

              
              //cout << var_comp_val_int <<endl;
              //this is the variable that will be assigned a value based on the conditional
              string var_assign = token_container[0];
              //string assign_true = token_container[if_index-1];
              //string assign_false = token_container[token_container.size()-1];


              //this returns true or false based on the comparison
              bool comp_bool = false;
              //this checks for what type of operator is used during comparison
              if (comp == ">"){
                if(var_comp_type == "string"){
                  if(var_comp_val > comp_literal){
                    comp_bool = true;
                  }
                }
                else{
                if(var_comp_val_int > comp_literal_int){
                  comp_bool = true;
                }
                }
              }
              else if (comp == ">="){
                if(var_comp_type == "string"){
                  if(var_comp_val >= comp_literal){
                    comp_bool = true;
                  }
                }
                else{
                if(var_comp_val_int >= comp_literal_int){
                  comp_bool = true;
                }
                }
              }

              else if(comp == "<"){
                if(var_comp_type == "string"){
                  if(var_comp_val < comp_literal){
                    comp_bool = true;
                  }
                }
                else{
                if(var_comp_val_int < comp_literal_int){
                  comp_bool = true;
                }
                }
              }

              else if(comp == "<="){ 
                //cout << "here"<<endl;
                if(var_comp_type == "string"){
                  if(var_comp_val <= comp_literal){
                    comp_bool = true;
                  }
                }
                else{
                
                if(var_comp_val_int <= comp_literal_int){
                  //cout << "here"<<endl;
                  comp_bool = true;
                }
                }
              }

              else if (comp == "=="){
                if(var_comp_type == "string"){
                  if(var_comp_val == comp_literal){
                    comp_bool = true;
                  }
                }
                else{
                  if(var_comp_val_int == comp_literal_int){
                    comp_bool = true;
                  }
                }
              }

              //now to assign based on comp_bool value
              //cout << comp_bool <<endl;
              string type_name, value;
              
              if(comp_bool == true){
                //for lists
                if (token_container[count + 2] == "[") {
                  //cout << "list"<<endl;
                    //cout << "here" <<endl;
                    //loop to get the expression being assigned to the variable
                    
                    exp = token_container[count+3];
                    //cout << exp <<endl;
                    
                    //need to find the type of the exp
                    size_t found = exp.find(",");
                    if (found == string::npos) {
                      //find the type for singular literal or prev var
                      type_name = checkDataType_exists(exp, data_type);
                      //check if this exp is a predefined variable
                      

                      map<string, string>::iterator it;
                      
                      //this checks if the exp is actually another variable
                      it = data_value.find(exp);
                      if (it != data_value.end()) {
                        value = it->second;
                      }
                      else {
                        value = exp;
                      }



                    }
                    //two maps, one to keep track of type, one for value;
                    data_value.insert({ var_assign, value });
                    data_type.insert({ var_assign, ("list" + type_name) });
                    //cout << "have done it" << endl << endl;
                }
                //for literals like string or a number
                else{
                    //cout << "here"<<endl;
                    //need to define when one list equals the other.
                    //cout <<"nonlist"<<endl;
                  exp = token_container[count+2];
                  //cout << exp<<endl;
                  type_name = checkDataType_exists(exp, data_type);
                  //cout << type_name<<endl;
                  map<string, string>::iterator it;
                  it = data_value.find(token_container[count+2]);
                  if (it != data_value.end()) {
                    //cout << "not"<<endl;
                    data_value[token_container[0]] = it->second;
                  }
                  else {
                    data_value[token_container[0]] = token_container[count + 2];
                  }
                  data_type[token_container[0]] = type_name;

                }
              }
              //if the comp bool value returns false, same thing as above, just using the part after "else"
              else{
                if (token_container[else_index + 1] == "[") {
                  //cout << "here" <<endl;
									//loop to get the expression being assigned to the variable
									
									exp = token_container[else_index + 2];
                  //cout << exp <<endl;
									
									//need to find the type of the exp
									size_t found = exp.find(",");
									if (found == string::npos) {
										//find the type for singular literal or prev var
										type_name = checkDataType_exists(exp, data_type);
										//check if this exp is a predefined variable
										

										map<string, string>::iterator it;
										
										it = data_value.find(exp);
										if (it != data_value.end()) {
											value = it->second;
										}
										else {
											value = exp;
										}



									}
									//two maps, one to keep track of type, one for value;
									data_value.insert({ var_assign, value });
									data_type.insert({ var_assign, ("list" + type_name) });
									//cout << "have done it" << endl << endl;
								}
                else{
                  //cout << "here"<<endl;
                  //need to define when one list equals the other.

                  exp = token_container[else_index + 1];
                  type_name = checkDataType_exists(exp, data_type);

                  map<string, string>::iterator it;
                  it = data_value.find(exp);
								  if (it != data_value.end()) {
									  data_value[token_container[0]] = it->second;
								  }
								  else {
									  data_value[token_container[0]] = token_container[else_index + 1];
								  }
                  data_type[token_container[0]] = type_name;

                }
              }





                 
            }

            //this is the same piece of assignment code as written above, just a few indices tweaked 
						else if (eval == false) {

							//check if the variable being defined has already been defined before
							//redifinition

              //cout << token_container[0] <<endl;
              

							if (isPresent(token_container[0], data_type)) {
                //cout << "here" <<endl;
                string dataT;
                string all_elem;
                int temp_counter;
                string type_name = "";
								string value;
                //break it down into
                if (token_container[count + 2] == "["){
                  temp_counter = count + 3;
							    
                  //cout <<"here"<<endl;
                  //cout << token_container[count + 3]<<endl;

                  while(token_container[temp_counter] != "]"){
                    all_elem += token_container[temp_counter];
                    temp_counter++;
                  }



                  stringstream ss(all_elem);
                  string token;
                  int counter_random = 0;



                  while(std::getline(ss, token, ',')) {
                      //cout << token <<endl;
                      if(counter_random ==0){
                        type_name = checkDataType_exists(token, data_type);
                        counter_random++;
                      }
                      map<string, string>::iterator it;
                      it = data_value.find(token);
                      if (it != data_value.end()) {
											  value += it->second + " ";
                        
										  }
                      else {
											  value += token + " ";
										  }

                  }







                  


                data_type[token_container[0]] = "list"+type_name;}
                else{
                  dataT = checkDataType_exists(token_container[count + 2], data_type);
                  string ttype = checkDataType_exists(token_container[0], data_type);

                  map<string, string>::iterator it;
                  it = data_value.find(token_container[count+2]);
									if (it != data_value.end()) {
										data_value[token_container[0]] = it->second;
									}
									else {
										data_value[token_container[0]] = token_container[count + 2];
									}
                  data_type[token_container[0]] = dataT;



                  //cout <<dataT<<endl;
                  //cout << "here" <<endl;
                  //cout << dataT <<endl;
                }







                //pick each element
               







                 
								//string ttype = checkDataType_exists(token_container[0], data_type);
                //we are skipping on the comparison between different data types because it is legal
                //no warning is asked from the program
								//string dataT = checkDataType_exists(token_container[count + 3], data_type);////////changed here
								//if (dataT != ttype) {
									//outputFile << "#warning" << endl;
									//data_type[token_container[0]] = dataT;







                  /*if (token_container[count + 2] == "["){
									  //data_value[token_container[0]] = token_container[count + 3];


                    stringstream ss(all_elem);
                    string token;

                    while(getline(ss, token, ',')) {
                      //cout << "HERE" <<endl;
                      map<string, string>::iterator it;
                      it = data_value.find(token);
                      if (it != data_value.end()) {
											  data_value[token_container[0]] += it->second + " ";
										  }
                      else {
											  data_value[token_container[0]] += token + " ";
										  }

                    }

                    





                    //map<string, string>::iterator it;
                    //it = data_value.find(token_container[count+3]);
										//if (it != data_value.end()) {
										//	data_value[token_container[0]] = it->second;
										//}
										//else {
										//	data_value[token_container[0]] = all_elem;
										//}

                    data_type[token_container[0]] = "list"+dataT;}
                  else{
                    map<string, string>::iterator it;
                    it = data_value.find(token_container[count+2]);
										if (it != data_value.end()) {
											data_value[token_container[0]] = it->second;
										}
										else {
											data_value[token_container[0]] = token_container[count + 2];
										}
                    data_type[token_container[0]] = dataT;
                    //data_value[token_container[0]] = token_container[count + 2];
                    //data_type[token_container[0]] = dataT;
                  }*/
								//}
								//else {
									
								//}
							}

							//define for the first time
							else {
                //cout << token_container[count+2] <<endl;
                string all_elem;
                int temp_counter;
								string type_name = "";
								string value;
								if (token_container[count + 2] == "[") {
                  //cout << "here" <<endl;
									//loop to get the expression being assigned to the variable
									temp_counter = count + 3;
                  //exp is used to set the datatype, first value
                  //regardless of whether list has multiple entries
									//exp = token_container[count+3];
                  //cout << exp <<endl;

                  while(token_container[temp_counter] != "]"){
                    all_elem += token_container[temp_counter];
                    temp_counter++;
                  }

									
									//need to find the type of the exp
									//size_t found = exp.find(",");
									
										//find the type for singular literal or prev var
									//type_name = checkDataType_exists(exp, data_type);
										//check if this exp is a predefined variable

                  //cout << token_container[count+3]<<"111" <<endl;
                  //cout << type_name<<"111" <<endl;


                    stringstream ss(all_elem);
                    string token;
                    int counter_random = 0;


                    while(std::getline(ss, token, ',')) {
                      //cout << token <<endl;
                      if(counter_random ==0){
                        type_name = checkDataType_exists(token, data_type);
                        counter_random++;
                      }
                      map<string, string>::iterator it;
                      it = data_value.find(token);
                      if (it != data_value.end()) {
											  value += it->second + " ";
                        
										  }
                      else {
											  value += token + " ";
										  }

                    }




										

									//map<string, string>::iterator it;
										
									//it = data_value.find(exp);
									//if (it != data_value.end()) {
									//  value = it->second;
									//}
									//else {
									//	value = exp;
									//}



									
									//two maps, one to keep track of type, one for value;
									data_value.insert({ token_container[0], value });
									data_type.insert({ token_container[0], ("list" + type_name) });
									//cout << "have done it" << endl << endl;
								}
                else{
                  //cout << "here"<<endl;
                  //need to define when one list equals the other.
                  exp = token_container[count+2];
                  type_name = checkDataType_exists(exp, data_type);

                  map<string, string>::iterator it;
                  it = data_value.find(token_container[count+2]);
									if (it != data_value.end()) {
										data_value[token_container[0]] = it->second;
									}
									else {
										data_value[token_container[0]] = token_container[count + 2];
									}
                  data_type[token_container[0]] = type_name;




                  /*exp = token_container[count+2];
                  type_name = checkDataType_exists(exp, data_type);
                  data_value.insert({ token_container[0], exp });
									data_type.insert({ token_container[0], (type_name)});*/

                }
              }
            }
            else if (eval == true){
              string carryover_to_left_nonint ="";
              int left_summand_int, right_summand_int, carryover_to_left_int=0;
              string data_type_left;
              string data_type_right;

              for(int i =0; i < token_container.size(); i++){

                string left_summand, right_summand;
                if (token_container[i] == "+"){

                  

                  /*if(data_type_left != data_type_right){
                    cout << "#error"<<endl;
                    break;
                  }*/

                  if(carryover_to_left_nonint == ""){
                    stringstream ss;
                    //left_summand =find and assign value ;
                    if(token_container[i-1] == "]"){
                      string l_val = token_container[i-2];
                      
                      //cout <<l_val<<endl;;
                      stringstream ss(l_val);
                      string token;
                      int counter_random = 0;
                    


                      while(std::getline(ss, token, ',')) {
                        //cout << token <<endl;
                        if(counter_random ==0){
                        data_type_left = "list"+checkDataType_exists(token, data_type);
                        counter_random++;
                        }
                        map<string, string>::iterator it;
                        it = data_value.find(token);
                        if (it != data_value.end()) {
											    left_summand += it->second+ " ";
                        
										    }
                        else {
											    left_summand += token+ " ";
										    }

                      }



                    }
                    else{
                      //find the 
                      map<string, string>::iterator it;
                      it = data_value.find(token_container[i-1]);
                      if (it != data_value.end()) {
											  left_summand = it->second + " ";
                        data_type_left = data_type[it->first];  
										  }
                      else{
                        cout << "#error" <<endl;
                        break;
                      }
                    }
                    if(token_container[i+1] == "["){
                      string r_val = token_container[i+2];
                      stringstream ss(r_val);
                      string token;
                      int counter_random = 0;
                    


                      while(std::getline(ss, token, ',')) {
                        //cout << token <<endl;
                        if(counter_random ==0){
                        data_type_right = "list"+checkDataType_exists(token, data_type);
                        counter_random++;
                        }
                        map<string, string>::iterator it;
                        it = data_value.find(token);
                        if (it != data_value.end()) {
											    right_summand += it->second + " ";
                        
										    }
                        else {
											    right_summand += token + " ";
										    }

                      }




                    }
                    else{
                      map<string, string>::iterator it;
                      it = data_value.find(token_container[i+1]);
                      if (it != data_value.end()) {
											  right_summand = it->second + " ";
                        data_type_right = data_type[it->first];  
										  }
                      else{
                        cout << "#error" <<endl;
                        break;
                      }
                    }

                  }
                  else{
                    stringstream ss;
                    //left_summand =find and assign value ;
                    //left_summand = carryover_to_left_nonint;
                    //data_type_left = data_type_right;
                    if(token_container[i+1] == "["){
                      string r_val = token_container[i+2];
                      stringstream ss(r_val);
                      string token;
                      int counter_random = 0;
                      //cout << r_val <<"11"<<endl;


                      while(std::getline(ss, token, ',')) {
                        //cout << token <<endl;
                        if(counter_random ==0){
                        data_type_right = "list"+checkDataType_exists(token, data_type);
                        counter_random++;
                        }
                        map<string, string>::iterator it;
                        it = data_value.find(token);
                        if (it != data_value.end()) {
											    right_summand += it->second + " ";
                          //data_type_right = data_type[it->first];
										    }
                        else {
											    right_summand += token + " ";
										    }
                        //cout <<right_summand <<"11"<<endl;

                      }




                    }
                    else{

                      map<string, string>::iterator it;
                      it = data_value.find(token_container[i+1]);
                      if (it != data_value.end()) {
											  right_summand = it->second + " ";
                        data_type_right = data_type[it->first];
                        //cout << right_summand << data_type_right << "11 "<<endl;   
										  }
                      else{
                        cout << "#error" <<endl;
                        break;
                      }
                    }

                    
                  }

                    //cout << left_summand<<" "<<data_type_left<<endl;
                   // cout <<right_summand<<" "<<data_type_right <<endl;
                      //stringstream ss(l_val);
                    
                    if(data_type_left != data_type_right){
                      cout << "#error"<<endl;
                      break;
                    }

                    if (carryover_to_left_nonint == ""){
                      carryover_to_left_nonint = left_summand + right_summand;
                    }
                    else{
                      //cout << "here" <<endl;
                      left_summand = carryover_to_left_nonint;
                      carryover_to_left_nonint = left_summand  +right_summand;
                    }
                    


                      
                      
                    
                  
                  //cout << carryover_to_left_nonint<<endl;
                  

                  //left_summand_int = stoi(token_container[i-1]);
                  //right_summand_int = stoi(token_container[i+1]);

                  ////check token_container left and right everytime outside

                  ////left or right can either be the list itself in terms of a variable or spelled out between square brackets

                  //lhs or rhs will be assigned the actual values of the lists like

                  //lhs = 5 6 7 8 and rhs = 2 2 2 for example

                  //all the if and else has to do is based on the type, concatonate or add
                  

                  
                  /*if(checkDataType_exists(token_container[i-1], data_type) == "int"){

                    left_summand_int = stoi(token_container[i-1]);
                    right_summand_int = stoi(token_container[i+1]);

                    if (carryover_to_left_int == 0){
                      carryover_to_left_int = left_summand_int + right_summand_int;
                    }
                    else{
                      cout << "here" <<endl;
                      left_summand_int = carryover_to_left_int;
                      carryover_to_left_int = left_summand_int + right_summand_int;
                    }
                  }
                  else if(checkDataType_exists(token_container[i-1], data_type) == "liststring" || checkDataType_exists(token_container[i-1], data_type) == "listint"){

                  }*/

                  //cout <<left_summand_int<<endl;
                }
              }
              
              data_type[token_container[0]] = data_type_left;
              data_value[token_container[0]] = carryover_to_left_nonint;

            }


          }
        }
      }
      //this is for the print statement
      else{
        need_to_print = true;
        //removes any unwanted empty token inside vector token_container
        vector<string>::iterator result = find(token_container.begin(), token_container.end(), "");
        if (result != token_container.end()){
          token_container.erase(result);
          
        }
        string l_val,var;
        bool slicing=false;
        bool indexing = false;
        int start=0, stop=0;
        
        //cout <<exp<<endl;
        //check for slicing with a check for square brackets
        vector<string>::iterator sli = find(token_container.begin(), token_container.end(), ":");
        if(sli != token_container.end()){
          slicing = true;
          //cout <<"here"<<endl;
        }
        if (slicing == true){
          for (int i = 1; i < token_container.size(); i++) {
            
            if(token_container[i]==":"){
              if(token_container[i-1] != "["){
                start = stoi(token_container[i-1]);
              }
              
              if(token_container[i+1] != "]"){
                stop = stoi(token_container[i+1]);
              }
            }
            if(token_container[i] == "("){
              var = token_container[i+1];
            }
            
    
            
          }
        }
        else{
          for (int i = 1; i < token_container.size(); i++) {
            if(token_container[i] == "["){
              start = stop = stoi(token_container[i+1]);
              indexing = true;
            }
            if(token_container[i] == "("){
              var = token_container[i+1];
            }
          }
        }

        //cout <<var<<endl;
        //fetch var from the data_value map;
        l_val = data_value[var];
        //cout << l_val.length() <<endl;
        

        size_t whitespace_trail = l_val.find_last_not_of(" ");
        if(whitespace_trail != string::npos){
          l_val = l_val.substr(0, whitespace_trail+1);
        }

        int counting = 0;
        stringstream ss1(l_val);
        string token;

        vector <string> to_print;
        while(getline(ss1,token,' ')){
         //cout << token << endl;
         to_print.push_back(token);
        }

        string temp = "";
        
        if(stop == 0 && indexing == false){
          stop = to_print.size();
        }

        //cout << start << "  "<<stop << endl;

        if(start == stop){
          temp=to_print[start];
          
        }
        else{
          
        for(int i =start; i<stop; i++){
          if(to_print[i] == "" ){
            continue;
          }
          temp+= to_print[i] +",";
        }
        }

        //vector <string> to_print;


        size_t comma_trail = temp.find_last_not_of(",");
        if(comma_trail != string::npos){
          temp = temp.substr(0, comma_trail+1);
        }

        if(start==stop){
          printed = temp;
          //cout <<printed<<endl;
        }
        else{
          printed = "["+temp+"]";
          //cout <<printed<<endl;
        }
        //ONLY THING LEFT TO TAKE CARE OF ARE PARENTHESES, AS OF RIGHT NOW

        
        //cout <<counting<<endl;
        //cout << l_val<<endl;
        //we will have lists seperated by commas, havent added the support for it yet. will be done when adddition
        //is specified
        //printed ="["
        



        //this only outputs the entire list for now. will incorporate start and stop later on
        //for(int i =0; i<l_val.length();i++){
         // printed +=l_val[i];
        //}
        //printed+="]";

        //cout <<printed<<endl;
        //cout <<endl;
       
      }

      cout << final_message <<endl;

      if(need_to_print == true){
        cout << printed <<endl;
      }


      
    }
  }
  

  //cout << data_type[0]->first <<endl;
  //print out the variable and their values
  //for (std::map<string,string>::iterator it=data_value.begin(); it!=data_value.end(); ++it)
    //std::cout << it->first << " => " << it->second << '\n';
  
  //cout << endl;
  //print out the variable and their types
  //for (std::map<string,string>::iterator it=data_type.begin(); it!=data_type.end(); ++it)
    //std::cout << it->first << " => " << it->second << '\n';
  
}



////MAKE SURE TO TRIM OFF TRAILING ENDS WHEN YOU STORE IN A VARIABLE