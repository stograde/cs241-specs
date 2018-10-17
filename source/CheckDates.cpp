#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include "json.hpp"				// https://github.com/nlohmann/json
#include "datetime_utils.hpp"	// http://www.partow.net/programming/datetime/index.html
#include "strtk.hpp"			// http://www.partow.net/programming/strtk/index.html

using json = nlohmann::json;
using namespace std;

string reformatNum( string );
string reformatNum( int );
vector<string> split( const string&, const string& );
string exec( const char* );
int exist( const char * );

int main( int argc, char ** argv ) {

	string assignment = argv[1];

	string assignmentID = assignment;

	assignment.append( ".json" );
	assignment.insert( 0, "./specs/_cache/" );

	json specFile;

	if (!exist( assignment.c_str() )) {
	
		cout << "Caching specs" << endl << endl;
		cout << exec( "cd .. && cs251tk" );

		cout << "\n\n\n\n" << endl;
	}

	ifstream specIn = ifstream( assignment );

	try {
		specIn >> specFile;
		cout << "Loaded spec file for " << assignmentID << endl;
	} catch (nlohmann::detail::parse_error e) {
		cout << "Invalid assignment id: " << assignmentID << endl;
		return 0;
	}
	json files = specFile.at( "files" );
	ifstream studentsIn = ifstream( "../students.txt" );
	char * student = new char[9];
	json students;

	for (int i = 0; ; i++) {
		studentsIn >> student;
		if (student[0] != '\0') students.push_back( student );
		else break;
		student[0] = '\0';
	}

	bool specifiedStudents = false;

	if (argc > 3 && argv[2][0] == '-' && argv[2][1] == 's') {
		vector<string> tempVector;
		for (int j = 3; j < argc; j++) {
			for (int i = 0; i < students.size(); i++) {
				string temp = students[i];
				if (argv[j] == temp) {
					specifiedStudents = true;

					tempVector.push_back( temp );
				}
			}
		}
		students.clear();
		students = tempVector;
		sort( students.begin(), students.end() );
	}

	bool specOk = false;

	dt_utils::datetime submission;
	dt_utils::datetime_format22 fmt( submission );

	string startcmd = "git log --reverse ";
	string endcmd = " 2> /dev/null | head -n 3 | tail -n 1";
	for (int j = 0; j < students.size(); j++) {

		cout << students[j] << '\t';

		string student2 = students[j];

		if (student2.size() < 6) cout << '\t';

		vector <dt_utils::datetime> submissions;

		for (int i = 0; i < files.size(); i++) {

			string directorypath = "cd ../students/";
			string studentName = students[j];
			directorypath.append( studentName );

			string filepath;
			filepath.append( assignmentID );
			filepath.append( "/" );

			string fileName = files[i]["filename"];

			filepath.append( fileName );

			string cmd = directorypath + " && " + startcmd + filepath + endcmd;
			string output = exec( cmd.c_str() );

			if (output[0] == 'D') {
				vector<string> dateVector = split( output, " " );

				string date = dateVector[1] + ", " + reformatNum( dateVector[3] ) + " " + dateVector[2] + " " + dateVector[5] + " " + dateVector[4] + " -0500";

				submission.clear();

				if (!strtk::string_to_type_converter( date, fmt )) cout << "Error" << endl;

				submissions.push_back( submission );
			}

		}


		if (submissions.size() != 0) {
			dt_utils::datetime firstSubmission = submissions[0];

			for (int i = 1; i < submissions.size(); i++) {
				if (dt_utils::lessthan_datetime( submissions[i], firstSubmission )) {
					firstSubmission = submissions[i];
				}
			}

			cout << "First Submission for " << assignmentID << ": " << reformatNum( firstSubmission.month ) << "/" << reformatNum( firstSubmission.day ) << "/" << firstSubmission.year << " " << reformatNum( firstSubmission.hour ) << ":" << reformatNum( firstSubmission.minute ) << ":" << reformatNum( firstSubmission.second ) << endl;
			specOk = true;
		} else cout << "No submission" << endl;



		submissions.erase( submissions.begin(), submissions.end() );

	}

	if (!specOk) cout << "=====spec may be wrong=====" << endl;

}


string reformatNum( string numIn ) {
	if (numIn == "0") return "00";
	else if (numIn == "1") return "01";
	else if (numIn == "2") return "02";
	else if (numIn == "3") return "03";
	else if (numIn == "4") return "04";
	else if (numIn == "5") return "05";
	else if (numIn == "6") return "06";
	else if (numIn == "7") return "07";
	else if (numIn == "8") return "08";
	else if (numIn == "9") return "09";
	else return numIn;
}

string reformatNum( int numIn ) {
	if (numIn == 0) return "00";
	else if (numIn == 1) return "01";
	else if (numIn == 2) return "02";
	else if (numIn == 3) return "03";
	else if (numIn == 4) return "04";
	else if (numIn == 5) return "05";
	else if (numIn == 6) return "06";
	else if (numIn == 7) return "07";
	else if (numIn == 8) return "08";
	else if (numIn == 9) return "09";
	else return to_string( numIn );
}

/* This method found online */
string exec( const char* cmd ) {
	array<char, 128> buffer;
	string result;
	shared_ptr<FILE> pipe( popen( cmd, "r" ), pclose );
	if (!pipe) throw runtime_error( "popen() failed!" );
	while (!feof( pipe.get() )) {
		if (fgets( buffer.data(), 128, pipe.get() ) != nullptr)
			result += buffer.data();
	}
	return result;
}

/* This method found online */
vector<string> split( const string& str, const string& delim ) {
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find( delim, prev );
		if (pos == string::npos) pos = str.length();
		string token = str.substr( prev, pos - prev );
		if (!token.empty()) tokens.push_back( token );
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

/* This method found online */
int exist( const char *name ) {
	struct stat   buffer;
	return (stat( name, &buffer ) == 0);
}