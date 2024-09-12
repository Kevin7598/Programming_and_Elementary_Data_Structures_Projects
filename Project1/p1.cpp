#include "io.h"

string enter_payment = "Please enter the monthly payment: ";
string enter_interest = "Please enter the interest rate: ";
string enter_duration = "Please enter the duration of the loan, in years: ";
double monthly_payment;
double interest_rate;
int year_number;
int month_number;
double Balance = 0;
double Interest;
double Principal;
double Balance_new;
// define the needed values

int main(){
    monthly_payment = GetParam(enter_payment, 1, 100000);
    interest_rate = GetParam(enter_interest, 0, 1);
    year_number = GetParam(enter_duration, 1, 100);
    month_number = year_number * 12;
    // derive the three needed values
    PrintHeader();
    // print the header
    for (int month = month_number; month > 0; month--) {
        Balance_new = (Balance + monthly_payment) / (1 + interest_rate / 12);
        Principal = Balance_new - Balance;
        Interest = monthly_payment - Principal;
        Balance = Balance_new;
        //calculate the three needed results based on the formula given
        PrintMonthlyData(month, Principal, Interest, Balance);
    }
    // print the needed results, one month by one month
    return 0;
}