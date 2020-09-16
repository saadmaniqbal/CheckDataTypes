The program checkdatatype.cpp is compiled on linux using 

g++ -std=c++11 checkdatatype.cpp -o checkdatatype

because without using c++11, there were very silly errors which i couldnt get rid of. This has been talked about with the TA as well.

Also, to avoid any clash between windows systems and the linux servers, i chose to code it without using regex or flex/bison, as many of us expressed concerns about the incompatibility of the server to run them properly. As a result, i built my parser frrom the ground up.

As for opening the program properly on the terminal, i have chosen to directly pick the second argument as the file name, as there is no mention of any dirty command calls in the homework prompt, and since the actual call is provided.
 

Due to the complicated and very limited scope of this homework, some lines may give #error when it is #warning, and this is a concern me and all my collegues share.
I hope this is taken into consideration when grading the homework, as sometimes, even the test cases were not consistent about what actually the homework has exactly asked us to evaluate.

Thank you.