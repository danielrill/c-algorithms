#include <iomanip>
#include <iostream>
#include <string>

struct mydate_t {
    int d;
    int m;
    int y;
};

std::string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int doom[12] = {3,28,14,4,9,6,11,8,5,10,7,12};
int doom_leap[12] = {4,29,14,4,9,6,11,8,5,10,7,12};


bool print_date(mydate_t &d)
{
   std::cout << std::setw(2) << std::setfill('0') << d.d
 	     << '-' << std::setw(2) << std::setfill('0') << d.m
 	     << '-' << d.y << std::endl;
	return true;
}


int calc_doom(mydate_t &d)
{
	// Formula for century code
    int century = (9 - ((d.y / 100) % 4) * 2) % 7;
    // Last 2 digits of the year divided by 2
    int temp = (d.y % 100) / 12;
    int remainder = ( d.y % 100) % 12;
    int temp_r = remainder / 4;

    int doomsday = century + temp + remainder + temp_r;

	return doomsday;
}

void get_day(mydate_t &d)
{
    // Decides between leap year and regular year
    int temp = calc_doom(d);
    int day;
    if ( (d.y % 400) == 0 )
    {
	    day = (d.d - doom[d.m -1] + temp) %7;
    }
    else if ( (d.y % 100) != 0)
    {
	    day = (d.d - doom_leap[d.m -1] + temp) % 7;
    }
    std::cout << days[day] << std::endl;
}

int main(void)
{

    struct mydate_t test;
    test.d = 12;
    test.m = 11;
    test.y = 2021;
    //print_date(test);
    //get_day(test);
    
    std::string input;
    
    std::cout << "Enter a Date [ddmmyyyy] (as one String)" << std::endl;
    std::cin >> input;
    
    struct mydate_t in;
    
    in.d = std::stoi(input.substr(0,2));
    in.m = std::stoi(input.substr(2,2));
    in.y = std::stoi(input.substr(4,9));
    
    std::cout << "you've entered " << std::endl;
    print_date(in);
    std::cout << "the Day was a: " << std::endl;
    get_day(in);
}
