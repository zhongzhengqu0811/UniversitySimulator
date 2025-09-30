#ifndef UNIVERSITY_H_
#define UNIVERSITY_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <random>
#include <algorithm>
#include "Date.h"
using namespace std;
extern int COHORT_SIZE;
extern double inflation;
//namespace
//{
//	int COHORT_SIZE;
//	double inflation;
//};
// Size of a cohort (i.e. # of students in the same year)
namespace
{
	std::string fmt(long long number)
	{
		bool isNegative = number < 0;
		if (isNegative) {
			number = -number;  // Make the number positive for formatting
		}

		// Convert the number to a string
		std::string result = std::to_string(number);

		// Insert commas into the string at appropriate places
		int n = result.length();
		int commaCount = (n - 1) / 3; // Calculate how many commas will be needed
		int newLength = n + commaCount;

		// Resize the result string to accommodate commas
		result.resize(newLength);

		// Start inserting commas from the right side
		int j = newLength - 1;
		int count = 0;

		for (int i = n - 1; i >= 0; --i) {
			result[j--] = result[i];
			count++;
			if (count == 3 && i > 0) {  // After every 3 digits, insert a comma
				result[j--] = ',';
				count = 0;
			}
		}

		// If the number was negative, prepend the minus sign
		if (isNegative) {
			result.insert(result.begin(), '-');
		}

		return result;
	}
};

//typedef double GradeArray[6]; 
#define START_YEAR 2025

class Student
{
	string firstName, middleName, lastName;
//	int studentNumber;
	int since; // Since when has this student been enrolled?
	int year; // Which year is this studnet currently in?
	int grades[6]; // the grades (out of 100) of the 6 units the student is taking for this academic year
	double learning[6]; // Amount of "learning" they have done, out of 100
	bool repeatingYear; // Is this student repeating a year?
	string getRandomFirstName()
	{
		ifstream fin("first-names-list.txt");
		string name;
		double randomNum = rand() / (double)RAND_MAX, frequency = 0;
		while(frequency < randomNum)
			fin >> name >> frequency;
		fin.close();
		return name;
	}
	
//	string getRandomMiddleName()
//	{
//		ifstream fin("middle-names-list.txt");
//		string name;
//		double randomNum = rand() / (double)RAND_MAX, frequency = 0;
//		while(frequency < randomNum)
//			fin >> name >> frequency;
//		fin.close();
//		return name;
//	}
	
	string getRandomLastName()
	{
		ifstream fin("last-names-list.txt");
		string name;
		double randomNum = rand() / (double)RAND_MAX, frequency = 0;
		while(frequency < randomNum)
			fin >> name >> frequency;
		fin.close();
		return name;
	}
	
public:
	Student(int since = -1)
	{
		firstName = getRandomFirstName();
		lastName = getRandomLastName();
	//	studentNumber = 0;
		year = 1;
		this->since = since;
		for(int i = 0; i < 6; i++) { grades[i] = -1; learning[i] = 0; }
		repeatingYear = false;
	}
	string getName() { return firstName + " " + lastName; }
	
	int getYear() { return year; }
	
//	int getStudentNumber() { return studentNumber;  }
	
	int getSince() { return since; }
	
	void setSince(int year) { since = year; }
	
	void setGrade(int index, int grade) { if(grade > 100) grade = 100; grades[index] = grade; }
	
	int getGrade(int index) { return grades[index]; }
	
	double getLearning(int index) { return learning[index]; }
	
	string getProjection(int index)
	{
		if(learning[index] < 40)
			return "Fail";
		else if(learning[index] < 50)
			return "3rd";
		else if(learning[index] < 60)
			return "2:2";
		else if(learning[index] < 70)
			return "2:1";
		else
			return "1st";
	}

	string getGradeStrings()
	{
		string result;
		for (int i = 0; i < 6; i++)
		{
			if (grades[i] >= 0)
				result += to_string(grades[i]) + "  ";
			else
				result += getProjection(i) + "  ";
		}
		return result;
	}

	void setAsRepeatingYear() { repeatingYear = true; }
	
	bool isRepeatingYear() { return repeatingYear; }
	
	void learn(int index, double learningEfficiency = 1)
	{
		static default_random_engine generator(time(0));
		normal_distribution<double> distribution(learningEfficiency, sqrt(100 / 60.));
		learning[index] += distribution(generator);
		if(learning[index] > 100) learning[index] = 100;
	}
	
	void resetAllGrades() { for(int i = 0; i < 6; i++) { grades[i] = -1; learning[i] = 0; } }
	
	// a student can advance to the next year if and only if they get
	// at least 40 marks on all 6 units
	bool canAdvanceToNextYear()
	{
		for(int i = 0; i < 6; i++)
		{
			if(grades[i] < 40)
				return false;
		}
		return true;
	}
	
	// a student can graduate if and only if they are in the fourth year
	// and they get at least 40 marks on all 6 units
	bool canGraduate() { return year == 3 && canAdvanceToNextYear(); }
	
	// a student has to withdraw without a degree if they fail any unit again
	// after repeating a year
	bool mustWithdraw() { return repeatingYear && !canAdvanceToNextYear(); }
	
	void advanceToNextYear() { if(canAdvanceToNextYear()) { year++; repeatingYear = false; } }
	
	void writeToFile(ofstream& fout)
	{
		fout << firstName << endl << lastName << endl;
		fout << year << endl << since << endl;;
		for(int i = 0; i < 6; i++)
		{
			fout << grades[i] << endl;
			fout << learning[i] << endl;
		}
		fout << repeatingYear << endl;
	}
	
	void readFromFile(ifstream& fin)
	{
		fin >> firstName >> lastName;
		fin >> year >> since;
		for(int i = 0; i < 6; i++)
			fin >> grades[i] >> learning[i];
		fin >> repeatingYear;
	}
};

class Staff
{
	string firstName, lastName;
	int overall, potential; // 60 - 100
	Date dateOfBirth;
	string getRandomFirstName()
	{
		ifstream fin("first-names-list.txt");
		string name;
		double randomNum = rand() / (double)RAND_MAX, frequency = 0;
		while(frequency < randomNum)
			fin >> name >> frequency;
		fin.close();
		return name;
	}
	
	string getRandomLastName()
	{
		ifstream fin("last-names-list.txt");
		string name;
		double randomNum = rand() / (double)RAND_MAX, frequency = 0;
		while(frequency < randomNum)
			fin >> name >> frequency;
		fin.close();
		return name;
	}
	int getSalaryModifier() { int r = 0; string name = firstName + lastName; for(int i = 0; name[i]; i++) r += name[i] - 97; return r; }
public:
	string getName() { return firstName + " " + lastName; }
	
	string dob() { return dateOfBirth.toAbbrString(); }
	
	long long getSalary() { return inflation * ((overall - 40.0) * 200.0 + getSalaryModifier()); } // Monthly salary ($)
	
	string getRating()
	{
		if(overall < 65) return "Rookie";
		else if(overall < 70) return "Amateur";
		else if(overall < 75) return "Lower Intermediate";
		else if(overall < 80) return "Intermediate";
		else if(overall < 85) return "Upper Intermediate";
		else if(overall < 90) return "Advanced";
		else if(overall < 95) return "Expert";
		else return "Master";
	}
	
	int getOverall() { return overall; }
	
	void develop() { if(rand() % 5 && overall < potential) overall++; }
	
	int getAge(Date currentDate)
	{
		int age = currentDate.getYear() - dateOfBirth.getYear();
		if(currentDate < dateOfBirth.getAnniversary(age)) age--;
		return age;
	}
	
	Staff(Date currentDate)
	{
		// University staff must be at least 35 years old at the end of the current calendar year
		int age = rand() % 30 + 35;
		dateOfBirth = Date::getRandomDate(currentDate.getYear() - age);
		firstName = getRandomFirstName();
		lastName = getRandomLastName();
		overall = rand() % 8 + 60 + .8 * (age - 35 + rand() % ((age - 35) / 3 + 1)) + 0.5;
		potential = 100 - rand() % 8;
		if(overall > potential) overall = potential;
	}
	
	Staff() = default;
	
	void writeToFile(ofstream& fout)
	{
		fout << firstName << endl << lastName << endl;
		fout << dateOfBirth.getMonth() << endl << dateOfBirth.getDay() << endl << dateOfBirth.getYear() << endl;
		fout << overall << endl << potential << endl; 
	}
	
	void readFromFile(ifstream& fin)
	{
		fin >> firstName >> lastName;
		int m, d, y;
		fin >> m >> d >> y;
		dateOfBirth = Date(m, d, y);
		fin >> overall >> potential;
	}
};

struct financialRecord
{
	int year;
	long long tuition;
	long long salary;
	long long runningCost;
	long long money;
};

class University
{
	vector <Student> students;
	vector <Staff> staff;
	vector <financialRecord> financialRecords;
	Date currentDate;
	int totalGraduates, totalWithdrawals;
	long long funds;
	long long tuition, salary, runningCost;
	void speakString(string s)
	{
		cout << s << endl;
	//	system(("\"espeak\\command_line\\espeak.exe -ven-us+f3 \"" + s + "\"").c_str());
	}
	
//	int getStaffCapacity() { return 10 * staff.size(); }
	
	double getLearningEfficiency()
	{
		if(staff.empty()) return 0;
		int totalRating = 0;
		for(Staff st : staff)
			totalRating += st.getOverall();
		double averageRating = totalRating / double(staff.size());
		double result = (averageRating + 14) / 100.00;
		double ratio = students.size() / double(staff.size());
		double multiplier;
		if (ratio >= 10) multiplier = 10.0 / ratio;
		else multiplier = 1 + 0.03 * (10 - ratio);
		return result * multiplier;
	}
	
	Student *getStudentByName(string name)
	{
		for(Student& s : students)
		{
			if(s.getName() == name)
				return &s;
		}
		return nullptr;
	}

	Staff* getStaffByName(string name)
	{
		for (Staff& s : staff)
		{
			if (s.getName() == name)
				return &s;
		}
		return nullptr;
	}
	
public:
	bool withdrawStudent(string studentName)
	{
		Student* st = getStudentByName(studentName);
		if (!st) return false;
		int index = 0;
		for (int i = 0; i < students.size(); i++)
		{
			if (students[i].getName() == studentName)
			{
				index = i;
				break;
			}
		}
		students.erase(students.begin() + index);
		totalWithdrawals++;
		return true;
	}

	bool fireStaff(string staffName)
	{
		Staff* st = getStaffByName(staffName);
		if (!st) return false;
		int index = 0;
		for (int i = 0; i < staff.size(); i++)
		{
			if (staff[i].getName() == staffName)
			{
				index = i;
				break;
			}
		}
		staff.erase(staff.begin() + index);
		return true;
	}

	// Returns the date of the start of the academic year in the specified *calendar year*
	// The academic year starts on the second Monday in September
	static Date getAcademicYearStart(int year) { return Date::fromMonthAndWeekday(2, 1, 9, year); }
	
	// Returns the date of the end of the academic year that *started* in the specified *calendar year*
	static Date getAcademicYearEnd(int year) { return getAcademicYearStart(year) + 7 * (1 + 12 + 1 + 4 + 9 + 3 + 3 + 4); }
	
	// Returns the current week number in the academic year
	// Returns -1 if the date is inside winter or spring break; -2 if it is inside an exam period
	int getWeekNumber()
	{
		int weekNumber;
		// Current date is after the start of the academic year in the *calendar year*
		if(currentDate >= getAcademicYearStart(currentDate.getYear()))
		{
			weekNumber = (currentDate - getAcademicYearStart(currentDate.getYear())) / 7;
			if(weekNumber == 13) return -2;
			else if(weekNumber > 12) return -1;
			return weekNumber;
		}
		// Current date is before the start of the academic year in the *calendar year*
		// This indicates the academic year started in the previous calendar year
		else
		{
			Date startOfYear = getAcademicYearStart(currentDate.getYear() - 1);
			// If weeks were counted normally, we would arrive at 14-17
			// if the date is in the winter break
			weekNumber = (currentDate - startOfYear) / 7;
			if(weekNumber <= 17) return -1;
			// Convert normal week number into academic week number
			// Subtract 5 weeks (1 week of exams + 4 weeks of winter break)
			weekNumber -= 5;
			// If the week number goes to 22-24 we know that we are in the spring break
			if(weekNumber >= 22 && weekNumber <= 24) return -1;
			// If we find ourselves after the spring break,
			// correct the week number again by subtracting 3 weeks of spring break
			if(weekNumber > 24) weekNumber -= 3;
			// If the week number goes to 25-28 we know that we are in the summer exam period
			if(weekNumber >= 25 && weekNumber <= 28) return -2;
			else if(weekNumber > 28) return -1;
			return weekNumber;
		}
	}
	
	// Returns whether the current day is an offday; no learning happens on offdays
	bool isOffday()
	{
		// Weekends are offdays
		return currentDate.getDayOfWeek() == 0 || currentDate.getDayOfWeek() == 6
			// and so are vacation / exam days
			|| getWeekNumber() < 0;
	}

	void hireStaff(vector<Staff> candidates, int choice)
	{
		staff.push_back(candidates[choice]);
	}

	void hireStaff(Staff s) { staff.push_back(s); }

	Date getDate() { return currentDate;  }

	vector<Student> getStudentList() { return students; }

	vector<Staff> getStaffList() { return staff;  }

	int getStudentCount() { return students.size();  }

	int getStaffCount() { return staff.size();  }

	int getTotalGraduates() { return totalGraduates;  }

	int getTotalWithdrawals() { return totalWithdrawals;  }
	
	// Saves the university's state into a file
	void save(string filename)
	{
		ofstream fout(filename);
		fout << students.size() << endl;
		for(Student st : students)
			st.writeToFile(fout);
		fout << staff.size() << endl;
		for(Staff st : staff)
			st.writeToFile(fout);
		fout << currentDate.getMonth() << endl;
		fout << currentDate.getDay() << endl;
		fout << currentDate.getYear() << endl;
		fout << totalGraduates << endl;
		fout << totalWithdrawals << endl;
		fout << funds << endl;
		fout << setprecision(10) << inflation << endl << COHORT_SIZE << endl;
		fout << financialRecords.size() << endl;
		for(financialRecord r : financialRecords)
		{
			fout << r.year << ' ' << r.tuition << ' ' << r.salary << ' ' << r.runningCost << ' ' << r.money << endl;
		}
		fout << tuition << ' ' << salary << ' ' << runningCost << endl;
	}

	
	
	// Loads the save file if present
	// Returns true if a save file is found; false otherwise
	bool load(string filename = "university.dat")
	{
		ifstream fin(filename);
		if(!fin)
			return false;
		int studentCount;
		fin >> studentCount;
		students.clear();
		for(int i = 0; i < studentCount; i++)
		{
			Student st;
			st.readFromFile(fin);
			students.push_back(st);
		}
		int staffCount;
		fin >> staffCount;
		for(int i = 0; i < staffCount; i++)
		{
			Staff st;
			st.readFromFile(fin);
			staff.push_back(st);
		}
		int m, d, y;
		fin >> m >> d >> y;
		currentDate.setMonth(m);
		currentDate.setDay(d);
		currentDate.setYear(y);
		fin >> totalGraduates >> totalWithdrawals >> funds >> inflation >> COHORT_SIZE;
		int count;
		fin >> count;
		for(int i = 0; i < count; i++)
		{
			int year;
			long long tuition, salary, runningCost, money;
			fin >> year >> tuition >> salary >> runningCost >> money;
			financialRecord r;
			r.year = year;
			r.tuition = tuition;
			r.salary = salary;
			r.runningCost = runningCost;
			r.money = money;
			financialRecords.push_back(r);
		}
		fin >> tuition >> salary >> runningCost;
		return true;
	}
	
	University()
	{
	//	inflation = 5;
	//	COHORT_SIZE = 10;
		srand(time(0));
		
		if(load("university.dat"))
			return;
		currentDate = getAcademicYearStart(START_YEAR);
		// Generate first-year students
		for(int i = 0; i < COHORT_SIZE; i++)
			students.push_back(Student(currentDate.getYear()));
	//	hireNewStaff();
		totalGraduates = totalWithdrawals = 0;
		funds = 15000 * inflation;
		tuition = salary = runningCost = 0;
		
		
	//	atexit(saveAtExit);
	}
	
	bool expand(int count)
	{
		while (COHORT_SIZE + count > 9999)
			count--;
		long long cost = 100000LL * count * inflation;
		if (funds < cost)
			return false;
		COHORT_SIZE += count;
		funds -= cost;
		return true;
	}

	long long getUniversityFunds() { return funds;  }

	financialRecord getCurrentYearFinancialRecord()
	{
		financialRecord r = { currentDate.getYear(), tuition, salary, runningCost };
		if (currentDate.getMonth() >= 9)
			r.year++;
		return r;
	}

	vector<financialRecord> getFinancialRecords() { return financialRecords;  }
	
	// Handles the end of an academic year.
	void endOfAcademicYear()
	{
		// Inflate in-game currency
		//inflation *= 1.015 + 0.01 * rand() / RAND_MAX;
		// Handle graduations and withdrawals (remove those students)
		vector<Student> copy = students;
		students.clear();
		int graduates = 0, withdrawals = 0;
		int total = 0;
		double average, passingRate = 0;
		
		for(Student st : copy)
		{
			bool passed = true;
			for(int i = 0; i < 6; i++)
			{
				if(st.getGrade(i) < 40)
					passed = false;
				total += st.getGrade(i);
			}
			passingRate += passed;
		}
		passingRate /= copy.size();
		passingRate *= 100;
		average = total / 6. / double(copy.size());
		for(Student st : copy)
		{
			if(st.canGraduate())
			{
				totalGraduates++;
				graduates++;
			}
			else if(st.mustWithdraw())
			{
				totalWithdrawals++;
				withdrawals++;
			}
			else
			{
				students.push_back(st);
			}
				
		}
		// Staff retirement - staff retire at the end of the academic year when they turn 75 years old
		vector <Staff> copy1 = staff;
		staff.clear();
		for(Staff st : copy1)
		{
			bool isRetiring = false;
			if(st.getAge(currentDate) >= 75)
			{
				isRetiring = true;
			}
			if(!isRetiring) staff.push_back(st);
		}
		// Develop staff
		for(Staff& st : staff)
			st.develop();
		// Add financial record for this year
		financialRecord r;
		r.year = currentDate.getYear();
		r.tuition = tuition;
		r.salary = salary;
		r.runningCost = runningCost;
		r.money = funds;
		financialRecords.push_back(r);
		
		tuition = salary = runningCost = 0;
		while(currentDate < getAcademicYearStart(currentDate.getYear()) - 3)
			advanceDate();
	}
	
	// Handles the beginning of a new academic year
	void newAcademicYear()
	{
		
		// Move eligible students up a year, then reset all student grades
		// Ineligible students will need to repeat their current year
		for(Student& st : students)
		{
			if(st.canAdvanceToNextYear())
				st.advanceToNextYear();
			else
				st.setAsRepeatingYear();
			st.resetAllGrades();
		}
		// Generate new first-year students
		for(int i = 0; i < COHORT_SIZE; i++)
		{
			students.push_back(Student(currentDate.getYear()));
		}
	}
	
	// Handles the passing of each day
	void advanceDate()
	{
		currentDate++;
		// Pay staff salaries on salary day (10th of each month)
		if(currentDate.getDay() == 10)
		{
			cout << "Pay day\n";
			for(Staff st : staff)
			{
				cout << "Salary for " << st.getName() << " paid, -?" << fmt(st.getSalary()) << endl;
				funds -= st.getSalary();
				salary += st.getSalary();
			}
		}
		// Collect tuition fees from students on the 15th of each month
		if(currentDate.getDay() == 15 && (currentDate.getMonth() >= 9 || currentDate.getMonth() <= 5))
		{
			cout << "Collecting tuition: \n";
			for(Student st : students)
			{
				long long tuitionFee = inflation * (27000 + 3000 * (st.getYear() - 1));
				tuitionFee /= 9;
				cout << "Student " << st.getName() << " pays tuition of ?" << fmt(tuitionFee) << endl;
				funds += tuitionFee;
				tuition += tuitionFee;
			}
		}
		// Monthly running costs are incurred based on # of currently enrolled students; lower costs during summer vacation
		if(currentDate.getDay() == 1)
		{
			long long cost = 1800 * students.size();
			if(currentDate.getMonth() >= 7 && currentDate.getMonth() <= 9)
				cost = 200 * COHORT_SIZE;
			cost *= inflation;
			cout << "Monthly running cost: ?" << fmt(cost) << endl;
			funds -= cost;
			runningCost += cost;
		}
		// Bankruptcy check at end of calendar year; cash negative on Dec 31 = bankrupt
		if(currentDate.getMonth() == 12 && currentDate.getDay() == 31)
		{
			if(funds < 0)
			{
				system("cls");
				cout << "Your university is bankrupt!\nPress any key to start a new university\n";
				//getch();
				*this = University();
				exit(0);
				return;
			}
		}
	//	system(("\"espeak\\command_line\\espeak.exe \"" + currentDate.toFullString() + "\"").c_str());
		if(currentDate == getAcademicYearStart(currentDate.getYear()))
			newAcademicYear();
		if (currentDate == getAcademicYearEnd(currentDate.getYear() - 1))
		{
			inflation *= 1.015 + 0.01 * rand() / RAND_MAX;
			endOfAcademicYear();
		}
			
		// If this is an offday but not an exam day, return without doing anything
		if(isOffday() && getWeekNumber() != -2)
			return;
		// No learning happens during Week 0 (welcome week)
		if(getWeekNumber() == 0)
			return;
		// Handle exam day
		if(getWeekNumber() == -2)
		{
			// Check if it's the December exams or the summer exams
			// December exams last one week; summer exams last 4 weeks
			int totalDays = (currentDate.getMonth() == 12 ? 5 : 26);
			double d = students.size() / (double)totalDays;
			d -= int(d);
			double randomNum = rand() / (double)RAND_MAX + 0.1;
			int numberOfStudents = students.size() / totalDays + 1;
			int index = 0;
			for(int i = 0; i < numberOfStudents && index < students.size(); index++)
			{
				bool processed = true;
				// Check if a student's exam results have already been generated
				if(totalDays == 5)
				{
					for(int j = 0; j <= 2; j++)
					{
						if(students[index].getGrade(j) < 0)
							processed = false;
					}
				}
				else
				{
					for(int j = 3; j <= 5; j++)
					{
						if(students[index].getGrade(j) < 0)
							processed = false;
					}
				}
				if(processed)
					continue;
				// Generate exam results
				i++;
				if(totalDays == 5)
				{
					for(int j = 0; j <= 2; j++)
						students[index].setGrade(j, students[index].getLearning(j) + rand() % 10 - 5);
					speakString(students[index].getName() + ": " + to_string(students[index].getGrade(0)) + ", " + to_string(students[index].getGrade(1)) + ", " 
						+ to_string(students[index].getGrade(2)));
				}
				else
				{
					for(int j = 3; j <= 5; j++)
						students[index].setGrade(j, students[index].getLearning(j) + rand() % 10 - 5);
					speakString(students[index].getName() + ": " + to_string(students[index].getGrade(3)) + ", " + to_string(students[index].getGrade(4)) + ", " 
						+ to_string(students[index].getGrade(5)));
				}
			}
			return;
		}

		// Handle student learning
		for(Student& st : students)
		{
			if(currentDate >= getAcademicYearStart(currentDate.getYear())) // first semester
			{
				for(int i = 0; i <= 2; i++)
					st.learn(i, getLearningEfficiency());
			}
			else // second semester
			{
				for(int i = 3; i <= 5; i++)
					st.learn(i, getLearningEfficiency());
			}
		}
	}
};

#endif // UNIVERSITY_H_

