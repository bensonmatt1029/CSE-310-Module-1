/****************************************************************
* Matt Benson
* CSE 310 Module 1
* Calculator Application
****************************************************************/

#include <map>
#include <functional>
#include <stdexcept>
#include <iostream>
using namespace std;

/****************************************************************
* CALCULATOR CLASS
****************************************************************/
class Calculator
{
public:
   Calculator()
   {
      // Initialize the map with function pointers for arithmetic operations
      operations['+'] = [](double a, double b) { return a + b; }; // Addition
      operations['-'] = [](double a, double b) { return a - b; }; // Subtraction
      operations['*'] = [](double a, double b) { return a * b; }; // Multiplication
      operations['/'] = [](double a, double b) {
         if (b == 0) throw invalid_argument("Division by zero"); // Division
         return a / b;
         };
   }

   // Perform the operation based on user input
   double calculate(double a, char op, double b)
   {
      if (operations.find(op) != operations.end())
      {
         return operations[op](a, b);
      }
      else
      {
         throw invalid_argument("Invalid operator");
      }
   }

private:
   map<char, function<double(double, double)>> operations;
};

// Function to get user input and validate it
bool getInput(double& num1, char& op, double& num2)
{
   cout << "Enter expression (e.g., 3 + 4): ";
   cin >> num1 >> op >> num2;

   // Input validation
   if (cin.fail())
   {
      cin.clear(); // clear error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
      cerr << "Invalid input. Please try again.\n";
      return false;
   }
   return true;
}

/****************************************************************
* MAIN
* There can be only one.
****************************************************************/
int main()
{
   // Create object of Calculator.
   Calculator calc;
   double num1, num2, result;
   char op;
   char choice;

   do
   {
      if (getInput(num1, op, num2))
      {
         try
         {
            result = calc.calculate(num1, op, num2);
            cout << "Result: " << result << '\n';
         }

         catch (const invalid_argument& e)
         {
            cerr << "Error: " << e.what() << '\n';
         }
      }

      // Conditional to continue the program.
      cout << "Do you want to perform another calculation? (y/n): ";
      cin >> choice;
   } while (choice == 'y' || choice == 'Y');

   // End of program!
   cout << "Goodbye!\n";
   return 0;
}