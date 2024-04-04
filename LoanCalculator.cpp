// Name: Shane Reall
// File Name: prog1a.cpp
// Date: 01 February, 2023
// Program Description: Calculates Infomation Involving Loans and Intrest. Outputs Information in the Consol.

#include <iomanip>
#include <iostream>
using namespace std;

int getLoanAmount(); // getLoanAmount Prototype
float getInterestRate(); // getInterestRate Prototype
int getMonthlyPayment(); // getMonthlyPayment Prototype
float calculate(int a, float r, int mp, float& lb, int month, float& lp, float& ti);// calculate Prototype (Also includes all parameter that are used with the calculate function)

int main()
{
	//Variables
	int amount = 0;
	float rate = 0.0;
	int monthlyPayment = 0;
	float remaingLoanBalance = 0;
	int month;
	float lastPayment;
	float totalIntrest = 0;

	amount = getLoanAmount(); // Gives amount a value
	rate = getInterestRate(); // Gives rate a value
	monthlyPayment = getMonthlyPayment(); // Gives monthlyPayment a value

	remaingLoanBalance = amount;

	cout << "Month   Interest Paid   Loan Balance" << endl // Displays Divisors in the Consol
		<< "------------------------------------" << endl;

	for (month = 1; month <= 12; month++)
	{
		calculate(amount, rate, monthlyPayment, remaingLoanBalance, month, lastPayment, totalIntrest);
	}

	cout << "Last payment: $" << lastPayment << endl; //Shows Last Payment
	cout << "Total interest: $" << totalIntrest << endl; //Shows Total Interest

}
//functions
int getLoanAmount()
{
	int x;
	cout << "Enter loan amount: ";
	cin >> x;
	return x;
}

float getInterestRate()
{
	float x;
	cout << "Enter interest rate: ";
	cin >> x;
	return x;
}

int getMonthlyPayment()
{
	int x;
	cout << "Enter monthly payment amount: ";
	cin >> x;
	return x;
}

float calculate(int a, float r, int mp, float &lb, int month, float &lp, float &ti)
{
	float interestPaid = lb * r / 1200; // Creation and Valueing of interestPaid
	cout << setw(5) << month; // Sets Month #
	cout << setw(12) << fixed << setprecision(2) << interestPaid; // Sets Intrest Paid
	lp = lb + interestPaid; // Values lp(Last Payment) to use inside main()
	lb = lb - (mp - interestPaid); // Values lb(Loan Balence) for use in the next line
	cout << setw(17) << lb << endl; // Sets Loan Balance

	ti += interestPaid; // Increases the Value of ti(Total Interest)

	return 0;
}