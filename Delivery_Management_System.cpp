// This program is made to be used in an implementation of a delivery company.
// Date: 10/03/2024
// Project Summary: Delivery Company Management System (DCMS)

/* Description: DCMS is an application that helps manage the deliveries for a delivery company. It includes functionalities such a */

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <regex>

using namespace std;

class User_details // This is a class to store user information, such as name and contact details.
{
private:
    friend bool validateEmail(const User_details &user);

public:
    string first_name;
    string last_name;
    string mobile_number;
    string email;
    string house_number;
    string street_name;
    string aprtment_or_suite;
    string city;
    string sub_locality;
    string state;
    string country;
    string pinCode;
    int age;
};
struct parcel_info // Structure to store parcel information, such as parcel name & weight;
{
    string parcel_name;
    double parcel_weight;
};
bool validateMobile(const User_details &user)
{ // This is a function to check the mobile number.
    regex mobileRegex("(\\d{10})");
    return regex_match(user.mobile_number, mobileRegex);
}

bool validateEmail(const User_details &user)
{ // This is a function to check the email address.
    regex emailRegex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(user.email, emailRegex);
}

bool validatePincode(const User_details &user)
{ // This is a function to check the PIN-CODE.
    regex mobileRegex("(\\d{6})");
    return regex_match(user.pinCode, mobileRegex);
}
double calcCost_local(double parcel_weight) // Function to calculate shipping cost in local.
{
    const double base_charge_per_kg = 40.0;
    double cost = parcel_weight * base_charge_per_kg;
    cout << endl
         << "\033[1m\tTotal Parcel Cost: \033[0m" << cost;
}

double calcCost_National(double parcel_weight) // Function to calculate shipping cost in Nation.
{
    const double base_charge_per_kg = 80.0;
    double cost = parcel_weight * base_charge_per_kg;
    cout << endl
         << "\033[1m\tTotal Parcel Cost: \033[0m" << cost;
}

double calcCost_International(double parcel_weight) // Function to calculate shipping cost in International.
{
    const double base_charge_per_kg = 150.0;
    double cost = parcel_weight * base_charge_per_kg;
    cout << endl
         << "\033[1m\tTotal Parcel Cost: \033[0m" << cost;
}

string generateRandomPickupDateTime()
{ // Function to generate random pickup date and time.
    time_t now = time(0);
    struct tm futureTime;
    const int daysAhead = 1;

    now += daysAhead * 24 * 60 * 60;
    futureTime = *localtime(&now);

    futureTime.tm_hour = 10;
    futureTime.tm_min = 0;
    futureTime.tm_sec = 0;

    srand(time(0));
    int randomMinutes = rand() % 50 + 10;
    futureTime.tm_min += randomMinutes;
    futureTime.tm_hour += randomMinutes / 60;
    futureTime.tm_min = futureTime.tm_min % 60;

    if (futureTime.tm_hour >= 19)
    {
        futureTime.tm_hour = 10;
        futureTime.tm_min = 0;
        futureTime.tm_sec = 0;
        futureTime.tm_mday += 1;
    }

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &futureTime);
    return buffer;
}

// Function to generate unique 6 digit ONE TIME PASSWORD (OTP) for each order.
string generateOTP()
{
    const int OTP_LENGTH = 6;
    string digits = "0123456789";
    string otp;

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < OTP_LENGTH; ++i)
    {
        otp += digits[rand() % digits.size()];
    }
    return otp;
}
// MAIN FUNCTION STARTS HERE!
int main()
{
    // Rules to fill the form...
    cout << "\033[1mRULES TO FULL THE FORM: " << endl;
    cout << "1. Choose between firm and personal delivery. " << endl;
    cout << "2. Use underscore (_) as space or separator." << endl;
    cout << "3. If you don't want to provide a particular information, write 'N/A (Not Applicable)' in that field." << endl;
    cout << "4. Weight must entered in Kilograms only." << endl;
    cout << "5. Any information of a sender or receiver must not be the same." << endl;
    cout << "6. Mobile number must a 10 digit number." << endl;
    cout << "7. PINCODE must be a 6 digit number." << endl;
    cout << "8. Age must be atleast 18 years old to less than 100 years old." << endl;
    cout << "9. No order will be cancelled once the form is submitted. A decided fee will be charged if the provided information is wrong or the parcel order is cancelled." << endl;
    cout << "10. Re-submittion of form will be mandatory on any wrong information.\033[0m" << endl;
    cout << endl
         << endl;

    // Taking Parcel Information.
    parcel_info parcel;
    cout << "\033[1mENTER THE DETAILS OF PARCEL: " << endl;
    cout << "---------------------------- \033[0m" << endl;
    cout << "\tEnter the name of the parcel: ";
    getline(cin, parcel.parcel_name);
    cout << "\tEnter the weight of the parcel (in kg's): ";
    cin >> parcel.parcel_weight;
    cout << endl
         << endl;

    // Taking User Details of the Sender.
    User_details sender;
    cout << "\033[1mENTER THE DETAILS OF SENDER: " << endl;
    cout << "---------------------------- \033[0m" << endl;

    cout << "\tEnter the first name of the sender: "; // First name of the sender.
    cin >> sender.first_name;

    cout << "\tEnter the last name of the sender: "; // Last name of the sender.
    cin >> sender.last_name;

    cout << "\tEnter the mobile number of the sender: "; // Mobile number of the sender.
    cin >> sender.mobile_number;

    // Validate Mobile Number of the sender.
    if (validateMobile(sender))
    {
        cout << "\033[32m\t\tSender's mobile number is verified. You may continue!\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m\t\tSender's mobile number is invalid. It must have 10 digits! Please Re-Submit the Form!\033[0m " << endl;
        exit(0);
    }

    cout << "\tEnter the email of the sender: "; // Email ID of the sender.
    cin >> sender.email;

    // Validate E-mail Address of the sender.
    if (validateEmail(sender))
    {
        cout << "\033[32m\t\tSender's email verified. You may continue!\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m\t\tSender's email is invalid. Please Re-Submit the form!!\033[0m" << endl;
        exit(0);
    }

    cout << "\tEnter the age of the sender: "; // Age of the sender.
    cin >> sender.age;
    // Validate Age of the sender.
    if (sender.age < 1 || sender.age > 100)
    {
        cout << "\033[31m\tSender's age is invalid. Please Re-Submit the form!!\033[0m" << endl;
    }
    cout << endl
         << endl;

    cout << "\033[1mENTER THE DETAILS OF ADDRESS OF THE SENDER: " << endl; // Taking the address of the sender.
    cout << "------------------------------------------ \033[0m" << endl;
    cout << "\tEnter the house number of the sender: ";
    cin >> sender.house_number;

    cout << "\tEnter the aprtment or suite name of the sender: ";
    cin >> sender.aprtment_or_suite;

    cout << "\tEnter the street name of the sender: ";
    cin >> sender.street_name;

    cout << "\tEnter the sub locality of the sender: ";
    cin >> sender.sub_locality;

    cout << "\tEnter the city of the sender: ";
    cin >> sender.city;

    cout << "\tEnter the state of the sender: ";
    cin >> sender.state;

    cout << "\tEnter the country of the sender: ";
    cin >> sender.country;

    cout << "\tEnter the pin code of the sender: ";
    cin >> sender.pinCode;
    // Validate PINCODE of the sender.
    if (validatePincode(sender))
    {
        cout << "\033[32m\t\tSender's PINCODE is verified. You may continue!\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m\t\tSender's PIN-CODE is invalid. Please Re-Submit the form!!\033[0m" << endl;
        exit(0);
    }
    cout << endl
         << endl;
    // Taking User Details of the receiver.
    User_details receiver;
    cout << "\033[1mENTER THE DETAILS OF RECEIVER: " << endl;
    cout << "----------------------------- \033[0m" << endl;

    cout << "\tEnter the first name of the receiver: "; // First name of the receiver.
    cin >> receiver.first_name;

    cout << "\tEnter the last name of the receiver: "; // Last name of the receiver.
    cin >> receiver.last_name;

    cout << "\tEnter the mobile number of the receiver: "; // Mobile number of the receiver.
    cin >> receiver.mobile_number;

    // Validate Mobile Number of the receiver.
    if (validateMobile(receiver))
    {
        cout << "\033[32m\t\tReceiver's mobile number is verified. You may continue!\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m\t\tReceiver's mobile number is invalid. It must have 10 digits! Please Re-Submit the Form!\033[0m" << endl;
        exit(0);
    }

    cout << "\tEnter the email of the receiver: "; //  Email ID of the receiver.
    cin >> receiver.email;

    // Validate E-mail Address of the receiver.
    if (validateEmail(receiver))
    {
        cout << "\033[32m\t\tReceiver's email verified. You may continue!\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m\t\tReceiver's email is invalid. Please Re-Submit the Form!\033[0m" << endl;
        exit(0);
    }

    cout << "\tEnter the age of the receiver: "; // Age of the receiver.
    cin >> receiver.age;

    // Validate Age of the receiver.
    if (receiver.age < 1 || receiver.age > 100)
    {
        cout << "\033[31m\t\tReceiver's age is invalid. Please Re-Submit the form!!\033[0m" << endl;
        exit(0);
    }
    cout << endl
         << endl;
    cout << "\033[1mENTER THE DETAILS OF ADDRESS OF THE RECEIVER: " << endl; // Taking the address of the receiver.
    cout << "------------------------------------------ \033[0m" << endl;
    cout << "\tEnter the house number of the receiver: ";
    cin >> receiver.house_number;

    cout << "\tEnter the aprtment or suite name of the receiver: ";
    cin >> receiver.aprtment_or_suite;

    cout << "\tEnter the street name of the receiver: ";
    cin >> receiver.street_name;

    cout << "\tEnter the sub locality of the receiver: ";
    cin >> receiver.sub_locality;

    cout << "\tEnter the city of the receiver: ";
    cin >> receiver.city;

    cout << "\tEnter the state of the receiver: ";
    cin >> receiver.state;

    cout << "\tEnter the country of the receiver: ";
    cin >> receiver.country;

    cout << "\tEnter the pin code of the receiver: "; // Pincode of the receiver.
    cin >> receiver.pinCode;

    // Validate PINCODE of the receiver.
    if (validatePincode(receiver))
    {
        cout << "\033[32m\t\tReceiver's PINCODE is verified. You may continue!\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m\t\tReceiver's PIN-CODE is invalid. Please Re-Submit the Form! \033[0m" << endl;
        exit(0);
    }
    cout << endl
         << endl;

    // Asking for place of shipment.
    int choice;
    cout << "\033[4m \033[1m\tENTER YOUR CHOICE FROM THE FOLLOWING TO CONTINUE THE PROCESS\033[0m\033[0m:" << endl
         << endl;
    cout << "\t1. Local Region. (Rs. 40 per KG)" << endl;
    cout << "\t2. National. (Rs. 80 per KG)" << endl;
    cout << "\t3. International. (Rs. 150 per KG)" << endl;
    cout << "\t4. Changed your mind? You can exit!" << endl;
    cout << "\tEnter your choice (1-4): ";
    cin >> choice;
    cout << endl
         << endl;

    // Display Summary of the Order.
    cout << "\033[1mORDER SUMMARY: " << endl;
    cout << "------------- \033[0m" << endl;

    cout << "YOUR PARCEL WILL BE SHIPPED AT THE FOLLOWING DETAILS: " << endl;
    cout << "---------------------------------------------------- \033[0m" << endl;
    cout << endl;

    cout << "\tParcel Name: " << parcel.parcel_name << endl;
    cout << "\tParcel Weight: " << parcel.parcel_weight << endl
         << endl;
    cout << "\tSender's Name: " << sender.first_name << " " << sender.last_name << endl;
    cout << "\tSender's Phone Number: " << sender.mobile_number << endl;
    cout << "\tSender's E-mail: " << sender.email << endl;
    cout << "\tSender's Address: " << sender.house_number << " - " << sender.aprtment_or_suite << ", " << sender.street_name << ", " << sender.sub_locality << ", " << sender.city << ", " << sender.state << ", " << sender.country << " - " << sender.pinCode << endl
         << endl;
    cout << "\tReceiver's Name: " << receiver.first_name << " " << receiver.last_name << endl;
    cout << "\tReceiver's Phone Number: " << receiver.mobile_number << endl;
    cout << "\tReceiver's E-mail: " << receiver.email << endl;
    cout << "\tReceiver's Address: " << receiver.house_number << " - " << receiver.aprtment_or_suite << ", " << receiver.street_name << ", " << receiver.sub_locality << ", " << receiver.city << ", " << receiver.state << ", " << receiver.country << " - " << receiver.pinCode << endl
         << endl;
    cout << "\033[1m\tPickup Date & Time: \033[0m";
    string pickupDateTime = generateRandomPickupDateTime(); // Generating Random Date & Time.
    cout << pickupDateTime << endl;
    switch (choice)
    {
    case 1:
        calcCost_local(parcel.parcel_weight); // Calculate cost for local region parcel.
        cout << endl;
        break;
    case 2:
        calcCost_National(parcel.parcel_weight); // Calculate cost for National region parcel.
        cout << endl;
        break;
    case 3:
        calcCost_International(parcel.parcel_weight); // Calculate cost for International region parcel.
        cout << endl;
        break;
    case 4:
        cout << "\033[32m\tThanks for choosing us. Please visit again. Thankyou!";
        exit(0);
    default:
        cout << "\033[31m\tInvalid choice! Please enter your choice between 1 and 4 only.\033[0m" << endl;
        break;
    }
    string otp = generateOTP();
    cout << "\tThanks for choosing us! Please visit again!" << endl
         << "\tDear customer, your OTP for pickup of your parcel is: \033[34m" << otp << "\033[0m. Use this OTP for validation while pickup of your parcel. Please do not share this OTP with anyone." << endl;
    cout << endl
         << endl;
    cout << " ";

    return 0;
}