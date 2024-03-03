
# Car Rental System
This repository consists of the codebase for a Car Rental System for the OOPS C++ Assignment-1 as a part of the course CS253

## Contents
This repository has the following contents &rarr;
1. [`headers.hpp`](/hraders.hpp) file which consists of all the constants used in the programme and the header files to be included &rarr;
    - Header files to be included like vector, string and regex
    - Discount for the employees 
    - Defualt values for eligibility score (when the average is not available during registration of customers)
2. [`checks.cpp`](/checks.cpp) file containing the various functions to provide checks on the input data which will be used to detect invalid inputs from the user.
3. [`classses.cpp`](/classes.cpp) file containing the user superclass, customer, employee and manager class with attributes and operations along with the definition of the functions used.
4. [`date_time.cpp`](/date_time.cpp) file containing the date_time functions used in the program.
5. [`login_register.cpp`](/login_register.cpp) file containing the login and register function for users.
6. [`read_write_display_funcs.cpp`](/raed_write_display_funcs.cpp) file containing the functions to read, write and display required content in the program.
7. [`newmain.cpp`](/newmain.cpp) file containing the driver function for the program. It includes all the files mentioned above and it is sufficient to run this function alone to run the app.
8. [`newmain.exe`](/newmain.exe) the .exe file created during the first execution of the program.
9. `.csv` files for the databases &rarr;
    - [`cars.csv`](/cars.csv)
    - [`customers.csv`](/customers.csv)
    - [`employees.csv`](/employees.csv)
    - [`managers.csv`](/managers.csv)


## Instructions 
Run the following command to compile and run the programme 
bash
g++ -c newmain.cpp -o main.o
g++ newmain.o -o test_prog
./test_prog.exe


## Details
- Employees get a discount of 15% for renting cars, which can be changed by changing the constant emp_disc stored in the ['header.hpp'](/header.hpp) file.
- A user is limited to rent a maximum of n cars where n must be less than the eligibility score
  - When a new user registers he/she is given a default eligibility score of 3.5
  - The eligibility score shall always lie between 0 and 5
  - The eligibility score of a user will be increased by 0.05 if a user returns a car on time and the car is not damaged
  - The eligibility score shall be decreased by 0.1 for every day delayed and 0.2 for every unit of car condition decremented.
- Functionalities of each class of user
  - **User (employee/customer)**
    - View all cars
    - View available cars
    - View cars that he/she has rented
    - Search for a car based on its model
    - Return a car (with employee verification)
    - Clear Dues(with employee verification)
    - Show dues
    - Show self data
    - Book car (with employee verification)
    - view cars based on parameters such as transmission and fuel type
    - update self data (only name pwd and email)
  - **Admin**
    - View users
    - Search users
    - Update users
    - Delete users
    - Add users
    - Update car
    - Delete car
    - Add car
    - show cars
    - update self
    - add admin
    - search car
- An unexpected input will cause the program to return to a previous state such as the user menu and not affect the databases involved.

## Assumptions 
- A user can only rent a maximum of 5 cars globally.
- Every car has a rating 1-5 which says how damaged the car is. With 5 being the least damaged.
- Fines
  - For every unit decrement in condition a fine equal to the cost of car per day is imposed
  - For every day delayed the an extra cost of fine per day shall be imposed (fetched from the file) above and over the cost of car per day
