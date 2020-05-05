#define  _CRT_SECURE_NO_WARNINGS ;
#include <iostream>
#include<string>
#include<stdio.h>
#include<cstring>
#include<fstream>

#define max_childrens 20 // maxium number of task
#define INFINITY -10000 
using namespace std;


//declaration to a node

class NODE {
public :
	char task_name[16];
	double duration;//time in the node
	int count = 0;
	int index;
	int childern[max_childrens];
	//double start_time;
	bool discoverd;
	int parent;
	int start_time;
	
};

//graph functions
class graph {
public :
	NODE **nod_array;
	graph(int size);//to take the size of the graph 
	void make_vertix(int ind , char s[16] , double du);

	void initilaize(int size, int start);
	void longest_path(int size);
	void print_graph(int end, int start);


};
graph::graph(int size) {
	nod_array = new NODE *[size];
}
void graph ::make_vertix(int ind , char name[16],double du )  {
	nod_array[ind] = new NODE;
	nod_array[ind]->duration = du;
	nod_array[ind]->index = ind;
	strcpy(nod_array[ind]->task_name , name);
}


void print_menu() {
	cout << "\n"<<"*********************MAIN MENU**********************" << endl;
	cout << "*		1-Load New File.                         *" << endl;
	cout << "*		2-Find The Starting Task.                *" << endl;
	cout << "*		3-Find The Ending Task.                  *" << endl;
	cout << "*		4-Find And Print The Crictal Path.       *" << endl;
	cout << "*		5-Exit.                                  *" << endl;
	cout << "****************************************************" << endl;
	cout << "Please enter you choice : " << endl;
}

void graph::initilaize(int size, int start) {
	for (int i = 0;i < size;i++) {
		nod_array[i]->discoverd = false;
		nod_array[i]->start_time = INFINITY;
		nod_array[i]->parent = -1;
	}
	nod_array[start]->discoverd = 0;
	longest_path(size);
}
void graph::longest_path(int size) {
	for (int i = 0; i < size;i++) {
		int sum = 0;
		sum = nod_array[i]->start_time + nod_array[i]->duration;
		for (int j = 0;j < nod_array[i]->count;j++) {
			if (sum > nod_array[nod_array[i]->childern[j]]->start_time) {
				nod_array[nod_array[i]->childern[j]]->start_time = sum;
				nod_array[nod_array[i]->childern[j]]->parent = i;
			}
		}
	}
}

void graph::print_graph(int end, int start) {
	if (nod_array[end]->parent == start) {
		cout << start << "=>" << end;
	}
	else {
		print_graph(nod_array[end]->parent, start);
		cout << "=>" << end;
	}
}


void main() {

	int choice, index;
	double last_task;
	double duration;
	char task_name[16];
	int child;
	int num_line ,num_edge ; //number of the nodes and numbers of children
	char file_name[16];
	ifstream read;
//////////////////////////////////////////////////////////////////////////////////////
	cout << "You should load a new file :  " << endl;
	cin >> file_name;
	read.open(file_name, ios::in);
	read >> num_line;
	//cout << "This is number of nodes : " << num_line << endl;
	graph u1(num_line);//creating a object u1
	for (int i = 0; i < num_line;i++) {
		read >> index >> task_name >> duration;
		u1.make_vertix(index, task_name, duration);
	}
	//cout << "This is the awnser yess : " << u1.nod_array[7]->duration << endl;// Testing if nodes are working
	read >> num_edge;
	for (int i = 0; i < num_edge;i++) {
		read >> index;
		read >> child;
		u1.nod_array[index]->childern[u1.nod_array[index]->count] = child;
		//u1.nod_array[index]->weight[u1.nod_array[index]->count] = u1.nod_array[index]->duration;
		u1.nod_array[index]->count++;
	}
	cout << "File is ready !" << endl;


	while (true)
	{
		print_menu();
		cin >> choice;
		
		if (choice == 1) {
			main();	
		}
		else if (choice == 2) {
			cout << "This is the first Task : \"" << u1.nod_array[0]->task_name << "\"" << endl;
		}
		else if (choice == 3) {
			for (int i = 0; i < num_line;i++) {
				if (u1.nod_array[i]->count == 0) {
					//last_task = u1.nod_array[i]->duration;
					cout << "The ending task is : " << u1.nod_array[i]->task_name << endl;
					last_task = u1.nod_array[i]->index;
					//cout << "ssssssssssss " << last_task << endl;
				}
			}
		}
		else if (choice == 4) {
			u1.initilaize(num_line,0);
			u1.print_graph(last_task,0);
		}
		else if (choice == 5) {
			break;
		}

	}

	system("pause");
}