#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include<sstream>
#include <iterator>
#include <cctype>
#include<regex>
#include <algorithm>

using namespace std;


/*std::string ltrim(const std::string& s) {
	return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string& s) {
	return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string& s) {
	return ltrim(rtrim(s));
}*/



string split_return(string str) {
	string s = str.substr(5, str.length());
	return s;

}



string checkDataType(string str) {
	string val;
	//need to find type based on everything after the = sign.
	//std::string str("There are two needles in this haystack with needles.");
	std::string str2("\"");

	// different member versions of find in the same order as above:
	std::size_t found = str.find(str2);
	if (found != std::string::npos)
		val = "string";
	else if (std::string::npos != str.find_first_of("0123456789")) {
		val = "int";
	}
	return val;




}

string checkFunction(string str, std::map<std::string, std::string>& functions) {
	//string s = "funcName(x,y,z)";
	//cout << s << endl;
	int finder = str.find("(");
	string func_name = str.substr(0, finder);
	functions.insert({ func_name, "" });
	//cout << s.length() << endl;
	string new_str = "";
	for (int i = finder + 1; i < str.length() - 2;i++) {
		new_str += str[i];

	}
	//cout << new_str << endl;

	//vector <string> tokens;

	// stringstream class check1 
	stringstream ss(new_str);

	string intermediate;

	// Tokenizing w.r.t. space ' ' 
	int count = 0;
	while (getline(ss, intermediate, ','))
	{
		functions[func_name] += intermediate + " ";
	}

	functions[func_name] += '\n';
	// Printing the token vector 
	return func_name;

}


string checkDataType_add(string key, string str, std::map<std::string, std::string>& data_type) {
	//need to find type based on everything after the = sign.
	if (data_type.find(key) == data_type.end()) {
		size_t found = str.find("\"");
		if (found != string::npos)
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

	size_t found = str.find("\"");
	if (found != string::npos) {
		//cout << "First occurrence is " << found << endl;
		val = "string";
		return val;
	}
	else if (std::string::npos != str.find_first_of("0123456789")) {
		//std::cout << "digit(s)found!" << std::endl;
		//std::cout << "digit(s)found!" << std::endl;
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

string addspace(string str) {
	string newstr = "";

	if (str.find("return") == 0) {
		newstr = "return ";
		for (int i = 6; i < str.length();i++) {
			if (str[i] == '=') {
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



	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '=') {
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


bool isPresent(string key, std::map<std::string, std::string>& data_type) {
	if (data_type.find(key) == data_type.end()) {
		// not found
		return false;
	}
	return true;
}


void populate_functions(string str, string nf, std::map<std::string, std::string>& functions) {
	functions[nf] += (str + "\n");
	//cout << str << endl;

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



int main() {

	// inputCommandLine = argv[1];


	//first, need to make a map that will hold variables and their respective data types
	//secondly, need to make a list that will contain all the predefined and reserved words like if, else, def, and a few others

	map<string, string> data_type;
	/////////bring this inside the function call loop
	list<string> reserved_words;
	map<string, string> functions;


	//need to define functions

	ifstream inputFile;
	inputFile.open("tc1.py");

	string message;
	int n = 1;
	int line_num = 1;
	while (getline(inputFile, message)) {
		string temp = message;
		message.erase(remove(message.begin(), message.end(), ' '), message.end());
		if (message.length() != 0) {


			//if (std::find_if(message.begin(), message.end(), isspace)) != userName.end()){

	//}		//keep an eye on this

			//find = and * and +, put a space before and after each of them

			string n_message;
			//message = trim(message);
			//string temp = message;
			message.erase(remove(message.begin(), message.end(), ' '), message.end());
			n_message = addspace(message);
			stringstream line(n_message);
			string token;
			vector<string> token_container;
			vector<string>::iterator it;
			//cout << "line " << n <<" tokens" << endl;
			//n++;


			while (getline(line, token, ' '))
				token_container.push_back(token);
			//cout << token << endl;

			int def_finder = token_container[0].find("def");

			if (def_finder == 0) {

				cout << temp << endl;
				string newfunc = token_container[0].substr(3, token_container[0].length());
				string function_name = checkFunction(newfunc, functions);
				//cout << function_name << endl;
				while (true) {
					getline(inputFile, message);
					string tempmsg = message;
					message.erase(remove(message.begin(), message.end(), ' '), message.end());
					if (message.length() == 0) {
						cout << endl;
						continue;
					}
					//message.erase(remove(message.begin(), message.end(), ' '), message.end());
					message.erase(remove(message.begin(), message.end(), ' '), message.end());
					message = addspace(message);

					//cout << message << endl;

					populate_functions(message, function_name, functions);


					stringstream line(message);

					string token;
					vector<string> token_container;

					while (getline(line, token, ' ')) {
						token_container.push_back(token);
						//cout << token <<endl;
					}
					int return_finder = token_container[0].find("return");

					//cout << message << endl;
					cout << tempmsg << endl;

					if (return_finder == 0)
						//cout << tempmsg << endl;
						break;


				}

				continue;

			}


			if (message.find("(") < 10000 && message.find(".") > 10000) {  ////this can count for both functions and appends, clarify
				message = addspace_paren(message);
				stringstream line2(message);
				vector<string> token_container;

				while (getline(line2, token, ' ')) {
					token_container.push_back(token);
					//cout << token << endl;
				}



				std::map<string, string>::iterator it2;
				it2 = functions.find(token_container[0]);

				if (it2 != functions.end()) {
					map<string, string>inter_type;
					string code = functions[token_container[0]];
					stringstream ss_code(code);
					string line_code;
					int checker = 0;
					while (getline(ss_code, line_code)) {
						stringstream ss_code_inter(line_code);
						string line_code_inter;
						vector<string> token_container_inter;
						while (getline(ss_code_inter, line_code_inter, ' ')) {
							token_container_inter.push_back(line_code_inter);
						}

						if (checker == 0) {
							//cout << token_container_inter[0] << endl;
							//cout << token_container_inter[1] << endl;
							//cout << token_container_inter[2] << endl;
							for (int i = 1; i < token_container.size();i++) {
								//cout << token_container[i] << endl;
								//cout << data_type.begin()->second <<"jere"<< endl;
								string ttype = checkDataType_exists(token_container[i], data_type);
								inter_type.insert({ token_container_inter[i - 1],ttype });
							}
						}
						checker++;
						/////start copy/////
						int count_inter = 0;
						//bool eval = false;
						if (token_container_inter[0] != "return") {
							for (auto i : token_container_inter) {
								if (i == "=") {

									bool eval_inter;

									for (int i = count_inter + 1; i < token_container_inter.size(); i++) {
										if (token_container_inter[i] == "+" || token_container_inter[i] == "*") {
											//cout << "line number: " << n << " has + or -" << endl;
											eval_inter = true;
											break;
										}
										else {
											//cout << "entering eval false condition for line "<<n << endl;
											eval_inter = false;

										}
									}

									/*if (eval_inter == true) {
										cout << "eval for line " << n << " is true" << endl;
									}
									else {
										cout << "eval for line " << n << " is false" << endl;
									}*/

									if (eval_inter == false) {
										if (isPresent(token_container_inter[0], inter_type)) {
											string ttype = checkDataType_exists(token_container_inter[0], inter_type);
											//string dataT = checkDataType(token_container_inter[count_inter + 1]);
											string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
											if (dataT != ttype) {
												cout << "#warning" << endl;
												inter_type[token_container_inter[0]] = dataT;

											}
										}
										else {
											if (token_container_inter[count_inter + 1] == "[]") {
												inter_type.insert({ token_container_inter[0], "list" });
											}
											else {
												//string type = checkDataType_add(token_container_inter[0], token_container_inter[count_inter + 1], inter_type);
												string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
												inter_type[token_container_inter[0]] = dataT;
											}
										}

									}


									for (auto it = token_container_inter.begin() + count_inter; it != token_container_inter.end(); ++it) {

										//check if token[0] has been set or not, if not assign the token[0] the same data type as left and right, provided left and right is the same. if not then produce error
										//also turn this into a function

										/////////////////////need to add cases for non variable addition and multiplication. UPDATE - just make sure assignment xyz = "saadman" + 34 is also taken care of.
										if (*it == "+" || *it == "*") {

											//eval = true;
											string left = checkDataType_exists(*(it - 1), inter_type);
											string right = checkDataType_exists(*(it + 1), inter_type);
											if (left != right) {
												if (*it == "+") {
													if (left == "liststring" || left == "listint") {
														cout << "#11warning" << endl;
													}
													else {
														cout << "#error" << endl;
														inter_type[token_container_inter[0]] = "string";
														break;
													}
												}
												else {
													cout << "#error" << endl;
													break;
												}
											}
											else {
												if (isPresent(token_container_inter[0], inter_type)) {
													string ttype = checkDataType_exists(token_container_inter[0], inter_type);
													if (ttype != left) {

														cout << "#warning" << endl;
														inter_type[token_container_inter[0]] = left;

													}
												}
												else {
													inter_type.insert({ token_container_inter[0], left });
												}

												//cout << token_container[0]<<endl;
											}
										}
										//need to focus on concatonation and overriding previously existing datatypes

									}

									break;
								}

								else if (i == "+" || i == "*") {
									string left = checkDataType_exists(token_container_inter[count_inter - 1], inter_type);
									string right = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
									if (left != right) {
										cout << "#error" << endl;
									}
								}

								count_inter++;
							}
						}

						/////this is when the return line hits
						else {
							bool eval_inter = true;

							for (int i = count_inter + 1; i < token_container_inter.size(); i++) {
								if (token_container_inter[i] == "+" || token_container_inter[i] == "*") {
									//cout << "line number: " << n << " has + or -" << endl;
									eval_inter = true;
									break;
								}
								else {
									//cout << "entering eval false condition for line "<<n << endl;
									eval_inter = false;

								}
							}

							if (eval_inter == false) {




								//string type = checkDataType_add(token_container_inter[0], token_container_inter[count_inter + 1], inter_type);
								string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
								inter_type[token_container_inter[0]] = dataT;
								data_type.insert({ token_container[0], dataT });
							}




							for (auto it = token_container_inter.begin() + 1; it != token_container_inter.end(); ++it) {
								if (*it == "+" || *it == "*") {

									//eval = true;
									/////the mistake exists in this block of ccode that turns a = blank 
									string left = checkDataType_exists(*(it - 1), inter_type);
									string right = checkDataType_exists(*(it + 1), inter_type);
									if (left != right) {
										if (*it == "+") {

											if (left == "liststring" || left == "listint") {
												cout << "#11warning" << endl;
												inter_type[token_container_inter[0]] = "listmixed";
												data_type.insert({ token_container[0], "listmixed" });
											}
											else {
												cout << "#error" << endl;
												inter_type[token_container_inter[0]] = "error";
												break;
											}
											

											//cout << "#warning " << endl;
											//inter_type[token_container_inter[0]] = "string";
											//data_type.insert({ token_container[0], "string" });
											//cout << "im here" << endl;
											//break;
										}
										else {
											cout << "#error " << endl;
											inter_type[token_container_inter[0]] = "error";
											data_type.insert({ token_container[0], "error" });

											break;
										}
									}
									else {
										if (isPresent(token_container_inter[0], inter_type)) {
											string ttype = checkDataType_exists(token_container_inter[0], inter_type);
											if (ttype != left) {

												cout << "#warning " << endl;
												inter_type[token_container_inter[0]] = left;

												data_type.insert({ token_container[0], left });

											}
										}
										else {
											inter_type.insert({ token_container_inter[0], left });

											data_type.insert({ token_container[0], left });
										}

										//cout << token_container[0]<<endl;
									}
								}
							}
						}


						/////end copy//////


					}
					map<string, string>::iterator itr;
					/*for (itr = inter_type.begin(); itr != inter_type.end(); ++itr) {
						cout << '\t' << itr->first
							<< '\t' << itr->second << '\n';
					}*/
					//cout << endl;

				}




			}


			int if_finder = temp.find("if");
			//cout << temp << endl;



			if (if_finder == 0) {
				string sign = "";
				if (temp.find("<") < 10000)
					if (temp.find("<=") < 10000)
						sign = "<=";
					else
						sign = "<";
				else if (temp.find(">") < 10000)
					if (temp.find(">=") < 10000)
						sign = ">=";
					else
						sign = ">";
				else if (temp.find("==") < 10000)
					sign = "==";

				//cout << sign << endl;


				//cout << temp.find(sign) << endl;;

				string left_var, right_var;
				for (int i = 3; i < temp.find(sign); i++) {
					left_var += temp[i];
				}
				if (sign.length() == 2) {
					for (int i = temp.find(sign) + 2; i < temp.find(":"); i++) {
						right_var += temp[i];
					}
				}
				else if (sign.length() == 1) {
					for (int i = temp.find(sign) + 1; i < temp.find(":"); i++) {
						right_var += temp[i];
					}
				}
				//cout << left_var << endl;
				//cout << right_var << endl;

				string left_type = checkDataType_exists(left_var, data_type);
				string right_type = checkDataType_exists(right_var, data_type);


				//cout << left_type << endl;;
				//cout << right_type << endl;;

				if (left_type != right_type) {
					cout << "#warning" << endl;
				}
				cout << temp << endl;
				continue;


				//string left_var = temp.substr(3, sign);
			}

			//cout << token_container[0].find("def") << endl;;
			//cout << message.find("(") << endl;

			if (temp.find(".append") < 10000) {
				string listname = "";
				string listadd = "";
				for (int i = 0; i < temp.find(".append");i++) {
					listname += temp[i];

				}
				//cout << listname << endl;
				for (int i = temp.find("(") + 1; i < temp.find(")");i++) {
					listadd += temp[i];
				}
				//cout << temp.find("(") <<" "<< temp.find(")") << endl;
				//cout << listadd << endl;


				string ttype = checkDataType_exists(listadd, data_type);
				string ltype = checkDataType_exists(listname, data_type);


				//data_type[listname] = "liststring";
				//cout << ttype << endl;
				//cout << ltype << endl;

				if (ltype == "list") {
					if (ttype == "string") {
						data_type[listname] = "liststring";
					}
					else if (ttype == "int")
						data_type[listname] = "listint";
				}

				if (ltype != "list" && (ttype != ltype)) {
					cout << "#warning" << endl;
				}

				//cout << listadd << endl;
				//cout << ttype << endl;
				//cout << ltype << endl;
				///check previous name
				/*if (data_type[listname] == "list") {
					if (ttype == "int") {
						//cout << "here int" << endl;
						data_type[listname] = "listint";
					}
					else{
						cout << "here string" << endl;
						data_type[listname] == "liststring";
					}
					//whatever is in the parentheses, find its type, and
					//search for this list name in data_type

				}
				else {
					if (data_type[listname] != ttype) {
						cout << "#warning" << endl;
						//break;
					}
				}*/
			}



			if (token_container[0] != "def" && token_container[0] != "if" && token_container[0] != "else") {
				//need to remove any white spaces

				int count = 0;
				//bool eval = false;

				for (auto i : token_container) {
					if (i == "=") {

						bool eval;

						for (int i = count + 1; i < token_container.size(); i++) {
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

						if (eval == false) {
							if (isPresent(token_container[0], data_type)) {
								string ttype = checkDataType_exists(token_container[0], data_type);
								string dataT = checkDataType_exists(token_container[count + 1], data_type);////////changed here
								if (dataT != ttype) {
									cout << "#warning" << endl;
									data_type[token_container[0]] = dataT;

								}
							}
							else {
								if (token_container[count + 1] == "[]") {
									data_type.insert({ token_container[0], "list" });
									//cout << "have done it" << endl << endl;
								}


								else {
									string message_right = token_container[count + 1];

									if (message_right.find("(") < 10000 && message_right.find(".") > 10000) {  ////this can count for both functions and appends, clarify
										message_right = addspace_paren(message_right);
										stringstream line2(message_right);
										vector<string> token_container_right;

										while (getline(line2, token, ' ')) {
											token_container_right.push_back(token);
											//cout << token << endl;
										}



										std::map<string, string>::iterator it2;
										it2 = functions.find(token_container_right[0]);

										if (it2 != functions.end()) {
											map<string, string>inter_type;
											string code = functions[token_container_right[0]];
											stringstream ss_code(code);
											string line_code;
											int checker = 0;
											while (getline(ss_code, line_code)) {
												stringstream ss_code_inter(line_code);
												string line_code_inter;
												vector<string> token_container_inter;
												while (getline(ss_code_inter, line_code_inter, ' ')) {
													token_container_inter.push_back(line_code_inter);
												}

												if (checker == 0) {
													//cout << token_container_inter[0] << endl;
													//cout << token_container_inter[1] << endl;
													//cout << token_container_inter[2] << endl;
													for (int i = 1; i < token_container_right.size();i++) {
														//cout << token_container_right[i] << endl;
														//cout << data_type.begin()->second <<"jere"<< endl;
														string ttype = checkDataType_exists(token_container_right[i], data_type);
														inter_type.insert({ token_container_inter[i - 1],ttype });
													}
												}
												checker++;
												/////start copy/////
												int count_inter = 0;
												//bool eval = false;
												if (token_container_inter[0] != "return") {
													for (auto i : token_container_inter) {
														if (i == "=") {

															bool eval_inter;

															for (int i = count_inter + 1; i < token_container_inter.size(); i++) {
																if (token_container_inter[i] == "+" || token_container_inter[i] == "*") {
																	//cout << "line number: " << n << " has + or -" << endl;
																	eval_inter = true;
																	break;
																}
																else {
																	//cout << "entering eval false condition for line "<<n << endl;
																	eval_inter = false;

																}
															}

															/*if (eval_inter == true) {
																cout << "eval for line " << n << " is true" << endl;
															}
															else {
																cout << "eval for line " << n << " is false" << endl;
															}*/

															if (eval_inter == false) {
																if (isPresent(token_container_inter[0], inter_type)) {
																	string ttype = checkDataType_exists(token_container_inter[0], inter_type);
																	//string dataT = checkDataType(token_container_inter[count_inter + 1]);
																	string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
																	if (dataT != ttype) {
																		cout << "warning" << endl;
																		inter_type[token_container_inter[0]] = dataT;

																	}
																}
																else {
																	if (token_container_inter[count_inter + 1] == "[]") {
																		inter_type.insert({ token_container_inter[0], "list" });
																		cout << "here i am" << endl;
																	}
																	else {
																		//string type = checkDataType_add(token_container_inter[0], token_container_inter[count_inter + 1], inter_type);
																		string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
																		inter_type[token_container_inter[0]] = dataT;
																	}
																}

															}


															for (auto it = token_container_inter.begin() + count_inter; it != token_container_inter.end(); ++it) {

																//check if token[0] has been set or not, if not assign the token[0] the same data type as left and right, provided left and right is the same. if not then produce error
																//also turn this into a function

																/////////////////////need to add cases for non variable addition and multiplication. UPDATE - just make sure assignment xyz = "saadman" + 34 is also taken care of.
																if (*it == "+" || *it == "*") {

																	//eval = true;
																	string left = checkDataType_exists(*(it - 1), inter_type);
																	string right = checkDataType_exists(*(it + 1), inter_type);
																	if (left != right) {
																		if (*it == "+") {

																			cout << "#warning " << endl;
																			inter_type[token_container_inter[0]] = "string";
																			//break;
																		}
																		else {
																			cout << "#error" << endl;

																		}
																	}
																	else {
																		if (isPresent(token_container_inter[0], inter_type)) {
																			string ttype = checkDataType_exists(token_container_inter[0], inter_type);
																			if (ttype != left) {

																				cout << "#warning " << endl;
																				inter_type[token_container_inter[0]] = left;

																			}
																		}
																		else {
																			inter_type.insert({ token_container_inter[0], left });
																		}

																		//cout << token_container[0]<<endl;
																	}
																}
																//need to focus on concatonation and overriding previously existing datatypes

															}

															break;
														}

														else if (i == "+" || i == "*") {
															string left = checkDataType_exists(token_container_inter[count_inter - 1], inter_type);
															string right = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
															if (left != right) {
																cout << "#error" << endl;
															}
														}

														count_inter++;
													}
												}

												/////this is when the return line hits
												else {
													bool eval_inter = true;

													for (int i = count_inter + 1; i < token_container_inter.size(); i++) {
														if (token_container_inter[i] == "+" || token_container_inter[i] == "*") {
															//cout << "line number: " << n << " has + or -" << endl;
															eval_inter = true;
															break;
														}
														else {
															//cout << "entering eval false condition for line "<<n << endl;
															eval_inter = false;

														}
													}

													if (eval_inter == false) {




														//string type = checkDataType_add(token_container_inter[0], token_container_inter[count_inter + 1], inter_type);
														string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
														inter_type[token_container_inter[0]] = dataT;
														data_type.insert({ token_container[0], dataT });
													}




													for (auto it = token_container_inter.begin() + 1; it != token_container_inter.end(); ++it) {
														if (*it == "+" || *it == "*") {

															//eval = true;
															/////the mistake exists in this block of ccode that turns a = blank 
															string left = checkDataType_exists(*(it - 1), inter_type);
															string right = checkDataType_exists(*(it + 1), inter_type);
															if (left != right) {
																if (*it == "+") {

																	cout << "#warning " << endl;
																	inter_type[token_container_inter[0]] = "string";
																	data_type.insert({ token_container[0], "string" });
																	//cout << "im here" << endl;
																	//break;
																}
																else {
																	cout << "#error" << endl;
																	inter_type[token_container_inter[0]] = "error";
																	data_type.insert({ token_container[0], "string" });

																	break;
																}
															}
															else {
																if (isPresent(token_container_inter[0], inter_type)) {
																	string ttype = checkDataType_exists(token_container_inter[0], inter_type);
																	if (ttype != left) {

																		cout << "#warning " << endl;
																		inter_type[token_container_inter[0]] = left;

																		data_type.insert({ token_container[0], left });

																	}
																}
																else {
																	inter_type.insert({ token_container_inter[0], left });

																	data_type.insert({ token_container[0], left });
																}

																//cout << token_container[0]<<endl;
															}
														}
													}
												}


												/////end copy//////


											}
											/*map<string, string>::iterator itr;
											for (itr = inter_type.begin(); itr != inter_type.end(); ++itr) {
												cout << '\t' << itr->first
													<< '\t' << itr->second << '\n';
											}
											cout << endl;*/

										}




									}
									else {


										string type = checkDataType_add(token_container[0], token_container[count + 1], data_type);
									}
								}
							}

						}


						for (auto it = token_container.begin() + count; it != token_container.end(); ++it) {

							//check if token[0] has been set or not, if not assign the token[0] the same data type as left and right, provided left and right is the same. if not then produce error
							//also turn this into a function

							/////////////////////need to add cases for non variable addition and multiplication. UPDATE - just make sure assignment xyz = "saadman" + 34 is also taken care of.
							if (*it == "+" || *it == "*") {

								//eval = true;

								string lv = *(it - 1);
								string rv = *(it + 1);

								if (lv.find("(") < 100000 || rv.find("(") < 100000) {
									if (lv.find(".") > 10000 && rv.find(".") > 10000) {
										string message_right;
										if(lv.find("(")<10000){
											message_right = lv;
										}
										else if (rv.find("(") < 100000) {
											message_right = rv;
										}
										////here, token_container contains the expressions such as c = fun(a) + b, and message_right = fun(a)
										message_right = addspace_paren(message_right);
										stringstream line2(message_right);
										vector<string> token_container_right;

										while (getline(line2, token, ' ')) {
											token_container_right.push_back(token);
											//cout << token << endl;
										}



										std::map<string, string>::iterator it2;
										it2 = functions.find(token_container_right[0]);

										if (it2 != functions.end()) {
											map<string, string>inter_type;
											string code = functions[token_container_right[0]];
											stringstream ss_code(code);
											string line_code;
											int checker = 0;
											while (getline(ss_code, line_code)) {
												stringstream ss_code_inter(line_code);
												string line_code_inter;
												vector<string> token_container_inter;
												while (getline(ss_code_inter, line_code_inter, ' ')) {
													token_container_inter.push_back(line_code_inter);
												}

												if (checker == 0) {
													//cout << token_container_inter[0] << endl;
													//cout << token_container_inter[1] << endl;
													//cout << token_container_inter[2] << endl;
													for (int i = 1; i < token_container_right.size();i++) {
														//cout << token_container_right[i] << endl;
														//cout << data_type.begin()->second <<"jere"<< endl;
														string ttype = checkDataType_exists(token_container_right[i], data_type);
														inter_type.insert({ token_container_inter[i - 1],ttype });
													}
												}
												checker++;
												/////start copy/////
												int count_inter = 0;
												//bool eval = false;
												if (token_container_inter[0] != "return") {
													for (auto i : token_container_inter) {
														if (i == "=") {

															bool eval_inter;

															for (int i = count_inter + 1; i < token_container_inter.size(); i++) {
																if (token_container_inter[i] == "+" || token_container_inter[i] == "*") {
																	//cout << "line number: " << n << " has + or -" << endl;
																	eval_inter = true;
																	break;
																}
																else {
																	//cout << "entering eval false condition for line "<<n << endl;
																	eval_inter = false;

																}
															}

															/*if (eval_inter == true) {
																cout << "eval for line " << n << " is true" << endl;
															}
															else {
																cout << "eval for line " << n << " is false" << endl;
															}*/

															if (eval_inter == false) {
																if (isPresent(token_container_inter[0], inter_type)) {
																	string ttype = checkDataType_exists(token_container_inter[0], inter_type);
																	//string dataT = checkDataType(token_container_inter[count_inter + 1]);
																	string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
																	if (dataT != ttype) {
																		cout << "warning" << endl;
																		inter_type[token_container_inter[0]] = dataT;

																	}
																}
																else {
																	if (token_container_inter[count_inter + 1] == "[]") {
																		inter_type.insert({ token_container_inter[0], "list" });
																		cout << "here i am" << endl;
																	}
																	else {
																		//string type = checkDataType_add(token_container_inter[0], token_container_inter[count_inter + 1], inter_type);
																		string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
																		inter_type[token_container_inter[0]] = dataT;
																	}
																}

															}


															for (auto it = token_container_inter.begin() + count_inter; it != token_container_inter.end(); ++it) {

																//check if token[0] has been set or not, if not assign the token[0] the same data type as left and right, provided left and right is the same. if not then produce error
																//also turn this into a function

																/////////////////////need to add cases for non variable addition and multiplication. UPDATE - just make sure assignment xyz = "saadman" + 34 is also taken care of.
																if (*it == "+" || *it == "*") {

																	//eval = true;
																	string left = checkDataType_exists(*(it - 1), inter_type);
																	string right = checkDataType_exists(*(it + 1), inter_type);
																	if (left != right) {
																		if (*it == "+") {

																			cout << "#warning " << endl;
																			inter_type[token_container_inter[0]] = "string";
																			//break;
																		}
																		else {
																			cout << "#error" << endl;

																		}
																	}
																	else {
																		if (isPresent(token_container_inter[0], inter_type)) {
																			string ttype = checkDataType_exists(token_container_inter[0], inter_type);
																			if (ttype != left) {

																				cout << "#warning " << endl;
																				inter_type[token_container_inter[0]] = left;

																			}
																		}
																		else {
																			inter_type.insert({ token_container_inter[0], left });
																		}

																		//cout << token_container[0]<<endl;
																	}
																}
																//need to focus on concatonation and overriding previously existing datatypes

															}

															break;
														}

														else if (i == "+" || i == "*") {
															string left = checkDataType_exists(token_container_inter[count_inter - 1], inter_type);
															string right = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
															if (left != right) {
																cout << "#error" << endl;
															}
														}

														count_inter++;
													}
												}

												/////this is when the return line hits
												else {
													bool eval_inter = true;

													for (int i = count_inter + 1; i < token_container_inter.size(); i++) {
														if (token_container_inter[i] == "+" || token_container_inter[i] == "*") {
															//cout << "line number: " << n << " has + or -" << endl;
															eval_inter = true;
															break;
														}
														else {
															//cout << "entering eval false condition for line "<<n << endl;
															eval_inter = false;

														}
													}

													if (eval_inter == false) {




														//string type = checkDataType_add(token_container_inter[0], token_container_inter[count_inter + 1], inter_type);
														string dataT = checkDataType_exists(token_container_inter[count_inter + 1], inter_type);
														inter_type[token_container_inter[0]] = dataT;
														data_type.insert({ message_right, dataT });
													}




													for (auto it = token_container_inter.begin() + 1; it != token_container_inter.end(); ++it) {
														if (*it == "+" || *it == "*") {

															//eval = true;
															/////the mistake exists in this block of ccode that turns a = blank 
															string left = checkDataType_exists(*(it - 1), inter_type);
															string right = checkDataType_exists(*(it + 1), inter_type);
															if (left != right) {
																if (*it == "+") {

																	cout << "#warning " << endl;
																	inter_type[token_container_inter[0]] = "string";
																	data_type.insert({ message_right, "string" });
																	//cout << "im here" << endl;
																	//break;
																}
																else {
																	cout << "#error" << endl;
																	inter_type[token_container_inter[0]] = "error";
																	//data_type.insert({ message_right, "string" });

																	break;
																}
															}
															else {
																if (isPresent(token_container_inter[0], inter_type)) {
																	string ttype = checkDataType_exists(token_container_inter[0], inter_type);
																	if (ttype != left) {

																		cout << "#warning " << endl;
																		inter_type[token_container_inter[0]] = left;

																		data_type.insert({ message_right, left });

																	}
																}
																else {
																	inter_type.insert({ token_container_inter[0], left });

																	data_type.insert({ message_right, left });
																}

																//cout << token_container[0]<<endl;
															}
														}
													}
												}


												/////end copy//////


											}
											/*map<string, string>::iterator itr;
											for (itr = inter_type.begin(); itr != inter_type.end(); ++itr) {
												cout << '\t' << itr->first
													<< '\t' << itr->second << '\n';
											}
											cout << endl;*/


										}
									}
								}

								string left = checkDataType_exists(*(it - 1), data_type);
								string right = checkDataType_exists(*(it + 1), data_type);
								if (left != right) {
									

										cout << "#error" << endl;
										//data_type[token_container[0]] = "string";
										break;
									
									
								}
								else {
									if (isPresent(token_container[0], data_type)) {
										string ttype = checkDataType_exists(token_container[0], data_type);
										if (ttype != left) {

											cout << "#warning" << endl;
											data_type[token_container[0]] = left;

										}
									}
									else {
										data_type.insert({ token_container[0], left });
									}

									//cout << token_container[0]<<endl;
								}
							}
							//need to focus on concatonation and overriding previously existing datatypes

						}

						break;
					}

					else if (i == "+" || i == "*") {
						string left = checkDataType_exists(token_container[count - 1], data_type);
						string right = checkDataType_exists(token_container[count + 1], data_type);
						if (left != right) {
							cout << "#error " << endl;
						}
					}

					count++;
				}


				///////check if multiplication of two strings are allowed or not


			}

			cout << temp << endl;
			///////////////////////////////////////ASSIGNMENT PROBLEM, ASSIGN ONE VARIABLE TO THE OTHER DOESNT WORK; FIX IT-----ALSO FUNCTION ASSIGNMENT BASED ON THE RETURN TYPE
			/////////////////////////////////////////HANDLE BLANK LINES, SKIP THEM [TICK]
			//////////////////////////////////////INPUT PARSING
			/////////////////////////////////////CHECK HOW TO DEAL WITH STRING*STRING; INT*STRING
			///////////////////////////////////PRINT ERROR/WARNING DURING INPUT OF DIFFERENT DATA TYPE IN LIST
			/////////////////////////////FIX ISSUE WHEN A VARIABLE INCLUDEDS A NUMBER, IT CONSIDERS ITSELF AS AN INT LIKE STR1[TICK]
			n++;
		}
	}





	//string s = checkDataType("\"okay\"");
	//cout << s << endl;
	map<string, string>::iterator itr3;
	for (itr3 = data_type.begin(); itr3 != data_type.end(); ++itr3) {
		cout << itr3->first << " : " << itr3->second << '\n';
	}
	system("PAUSE");
	return 0;
}