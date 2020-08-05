# cpm-project
Critical Path Management(C++ Development)
Documentation
Project Duration : 5 weeks
Features available :
1.	Prompts project details and inputs in a recursive manner.
2.	Calculation of minimum time taken for a project and information in each activity such as Earliest Start time.
3.	Generates an .sql file that contains SQL query that inserts project details into a server.

Requirements:
1. C++ compiler in Path of machine
2. main.cpp file
3. MySql server connection
4. Platform to run SQL queries (Suggestion: VScode with MySQL(Jun Han) extension installed)

Setting up MySql Server
1.	Install MySql from their official website https://www.mysql.com/downloads/
2.	Remember the local root password during the setup(will be needed later).
3.	Once installed, open the MySql Workbench and create a new instance
4.	Setup a user with privileges and connect to Vscode using a MySQL(Jun Han) extension.

How to run project from terminal:
(Assumes the C++ Compiler is downloaded and saved in PATH)
1. Go to terminal or the folder where the main.cpp is downloaded and open terminal from the folder by typing CMD at the file explorer’s address bar.
2. type in “g++ -o (your output file name) main.cpp” and press enter in terminal.
3. then type “(your output file name)./” and press enter and the program should start running in the terminal.
4. Each project wil create an output .sql file which you can open and run the mysql query to insert into your server(assuming you have connected to a server).



Lessons Learned through the project:
As a C++ Programmer:
1.	Better use of recursive functions instead of loops
2.	From unable to understand the use of pointers in C++, I have mastered the efficient use of pointers and how it saves more memory (instead of creating a copy of the variable).
3.	Learned how to use ostreams and fstreams and other libraries efficiently to output the results.

As a Developer:
1.	Since in the middle of the project, I switched from CodeBlocks IDE into using Visual studio code, I have learnt how to use both the IDE and editor for my project.(Transition to vscode was due to the growing significance of it among developers, hence I’ve decided that using it for my project would be a good practice)
2.	Usage of VScode thought me how to run commands to build and run projects from terminal.
3.	Learned how to use git feature until I am able to push my project to my GiTHub account
4.	Learned SQL language and how to setup a MySQL server as a localhost, create an instance and a user with privileges to connect with VScode database(MySQL) extension.
5.	Learned how to prepare exception handling for project and realized this part takes up the most time before execution.

Project Flaw/Bug:
I couldn’t find a way to connect C++ from VSCode directly to MySQL which can be done using IDE’s as shown in a number of tutorials. It can be done, and if you’re able to connect it a lot more can be done faster without having to run the SQL queries separately.
