#include "pch.h"
#include "CppUnitTest.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "C:\Users\Timur\proga\ОС\LAB-1\main\employee.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Lab1Tests
{
	TEST_CLASS(Lab1Tests)
	{
	public:
		
		TEST_METHOD(Employee_Values)
		{
			employee e{};
			Assert::AreEqual(0, e.num);
			Assert::AreEqual(0.0, e.hours);
			Assert::AreEqual('\0', e.name[0]);
		}

		TEST_METHOD(Employee_Assignment)
		{
			employee e{ 5, "Ivanov", 10.5 };
			Assert::AreEqual(5, e.num);
			Assert::AreEqual(10.5, e.hours);
			Assert::AreEqual('I', e.name[0]);
		}

		TEST_METHOD(BinaryFile_WriteAndRead)
		{
			const char* filename = "single.bin";
			employee e1 = { 1, "Alex", 12.0 };
			ofstream out(filename, ios::binary);
			out.write((char*)&e1, sizeof(employee));
			out.close();

			ifstream in(filename, ios::binary);
			employee e2;
			in.read((char*)&e2, sizeof(employee));
			in.close();

			Assert::AreEqual(e1.num, e2.num);
			Assert::AreEqual(e1.hours, e2.hours);
			Assert::AreEqual(string(e1.name), string(e2.name));
		}

		TEST_METHOD(BinaryFile_MultipleRecords)
		{
			const char* filename = "multi.bin";
			employee e1 = { 1, "A", 1.0 };
			employee e2 = { 2, "B", 2.0 };
			employee e3 = { 3, "C", 3.0 };

			ofstream out(filename, ios::binary);
			out.write((char*)&e1, sizeof(employee));
			out.write((char*)&e2, sizeof(employee));
			out.write((char*)&e3, sizeof(employee));
			out.close();

			ifstream in(filename, ios::binary);
			int count = 0;
			employee e;
			while (in.read((char*)&e, sizeof(employee)))
				count++;
			in.close();

			Assert::AreEqual(3, count);
		}

		TEST_METHOD(Salary_Correct)
		{
			employee e{ 1, "Ivan", 10.0 };
			double payment = 100.0;
			double salary = e.hours * payment;
			Assert::AreEqual(1000.0, salary);
		}

		TEST_METHOD(Salary_RoundedPrecision)
		{
			employee e{ 2, "Test", 2.345 };
			double payment = 43.21;
			double salary = e.hours * payment;
			std::ostringstream ss;
			ss << std::fixed << std::setprecision(2) << salary;
			Assert::AreEqual(string("101.33"), ss.str());
		}

		TEST_METHOD(Salary_NegativePayment_ShouldThrow)
		{
			try {
				double payment = -5.0;
				if (payment < 0)
					throw runtime_error("Payment can't be negative");
				Assert::Fail(L"Ожидалось исключение");
			}
			catch (const runtime_error& ex) {
				Assert::AreEqual(true, string(ex.what()).find("negative") != string::npos);
			}
		}

		TEST_METHOD(Reporter_CreatesCorrectText)
		{
			const char* bin = "report_in.bin";
			const char* txt = "report_out.txt";
			double payment = 50.0;

			employee e1 = { 1, "Ivanov", 8.0 };
			employee e2 = { 2, "Petrov", 4.0 };

			ofstream out(bin, ios::binary);
			out.write((char*)&e1, sizeof(employee));
			out.write((char*)&e2, sizeof(employee));
			out.close();

			ifstream in(bin, ios::binary);
			ofstream report(txt);
			report << "File report: " << bin << "\n";
			report << "Number\tName\tHours\tSalary\n";
			employee e;
			while (in.read((char*)&e, sizeof(employee))) {
				double pay = e.hours * payment;
				report << e.num << "\t" << e.name << "\t"
					<< e.hours << "\t" << std::fixed << std::setprecision(2) << pay << "\n";
			}
			in.close();
			report.close();

			ifstream check(txt);
			string content((istreambuf_iterator<char>(check)), istreambuf_iterator<char>());

			Assert::AreEqual(true, content.find("Ivanov") != string::npos);
			Assert::AreEqual(true, content.find("Petrov") != string::npos);
			Assert::AreEqual(true, content.find("400.00") != string::npos); 
			Assert::AreEqual(true, content.find("200.00") != string::npos); 
		}

		TEST_METHOD(Reporter_EmptyFile_ShouldWriteHeaderOnly)
		{
			const char* bin = "empty.bin";
			const char* txt = "empty.txt";
			ofstream(bin, ios::binary).close(); 

			ifstream in(bin, ios::binary);
			ofstream out(txt);
			out << "File report: " << bin << "\n";
			out << "Number\tName\tHours\tSalary\n";
			employee e;
			while (in.read((char*)&e, sizeof(employee))) {} 
			in.close();
			out.close();

			ifstream check(txt);
			string content((istreambuf_iterator<char>(check)), istreambuf_iterator<char>());
			Assert::AreEqual(true, content.find("Salary") != string::npos);
			Assert::AreEqual(true, content.find("Ivanov") == string::npos);
		}

		TEST_METHOD(Employee_LargeHours)
		{
			employee e{ 3, "Max", 99999.99 };
			Assert::IsTrue(e.hours > 10000.0);
		}

		TEST_METHOD(Employee_ZeroHours)
		{
			employee e{ 4, "Idle", 0.0 };
			Assert::AreEqual(0.0, e.hours);
		}
	};
}
