#include<iostream>
#include<fstream>
#include<string>
#include <unordered_map>
using namespace std;

int sID;


struct sdetails {   //sizeof(sdetails); is 20
	int sid;
	char sname[10];
	char sdomain[5];
	bool sb;
};

unordered_map<int, sdetails> umap;

void add_student() {
	// to get student count
	ifstream read;
	read.open("student/student_count.txt");
	if (!read.fail()) {
		read >> sID;
	}
	else {
		sID = 0;
	}
	read.close();
	// ----- x ----- //

	//get inputs of student details
	sdetails sd;
	sd.sid = sID++;
	cout << "enter student:" << endl;
	cin >> sd.sname;
	cout << "enter student domain:" << endl;
	cin >> sd.sdomain;
	sd.sb = 0;
	// ----- x ----- //


	fstream file("student/sdata.bin", ios::out | ios::in | ios::binary);
	file.seekp(sd.sid * sizeof(sdetails), ios::beg);  // seeking to the id we got from count

	file.write((char*)&sd, sizeof(sd));  //  and write(which basically appends)

	/*sdetails ob;
	for (int i = 0; i < sID; i++) {
		file.seekg(i * sizeof(sdetails), ios::beg);
		file.read((char*)&ob, sizeof(sdetails));
		cout << ob.sid << endl;
		cout << ob.sname << endl;
		cout << ob.sdomain << endl;
		cout << ob.sb << endl;
	}*/

	// update the count in student count sheet
	ofstream write;
	write.open("student/student_count.txt");
	write << sID;
	write.close();
	// ----- x ----- //
}

void store_student() {
	// to get student count
	ifstream read;
	read.open("student/student_count.txt");
	if (!read.fail()) {
		read >> sID;
	}
	else {
		sID = 0;
	}
	read.close();
	// ----- x ----- //

	fstream file("student/sdata.bin", ios::out | ios::in | ios::binary);

	sdetails ob;
	for (int i = 0; i < sID; i++) {
		file.seekg(i * sizeof(sdetails), ios::beg);
		file.read((char*)&ob, sizeof(sdetails));

		umap[ob.sid] = ob;
	}

}

void display_student() {
	sdetails ob;
	for (int i = 0; i < sID; i++) {

		ob = umap[i];

		cout << ob.sid << " ";
		cout << ob.sname << " ";
		cout << ob.sdomain << " ";
		cout << ob.sb << endl;


	}
}

int main() {
	//add_student();
	store_student();
	display_student();
}
