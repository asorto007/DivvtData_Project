/* program_4.cpp
    Divvy Bike Data Analysis program.
    Author: Anthony Sorto
    Date: 11/1/2021
    Class: CS 141, Fall 2021, UIC
    System: Clion Windows
    Menu Option 5 Extra Credit URL: https://www.google.com/maps/d/u/0/edit?mid=1kEBEpX9wK7_L-cxFBnXy6ZYR_u0mVIs6&usp=sharing
    Coordinates for Home I would like to live in:  41.8645	-87.6292
    Running Program looks like
        Analyze Divvy bike ride information using September trip data.
        First select option 1 to read and clean the data.
        Select a menu option:
        1. Select datafile, display rides totals and clean data
        2. Display overall trip information
        3. Display percentage of members vs. casual riders
        4. Display weekday vs weekend usage
        5. Extra Credit: find closest station
        6. Exit
        Your choice -->
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

// DivvyData class which stores information pulled from the CVS file.
// In public are the default constructor, get and set functions for all the variable types, as well as
// Copy Constructor and destructor
class DivvyData
{
    public:
        DivvyData(  string ride_id = "null",       // Overloaded Default constructor
                    string rideable_type = "null", // which takes in the values to be
                    string started_at = "null",    // stored in private, with
                    string ended_at = "null",      // initialization given if no value present.
                    string start_station_name = "null",
                    string end_station_name = "null",
                    long double start_lat = 0,
                    long double start_lng = 0,
                    long double end_lat = 0,
                    long double end_lng = 0,
                    string member_casual = "null");
        DivvyData(const DivvyData &newDivvy);
        ~DivvyData();
        string getID()const{return ride_id;} //getFunctions for individual variables stored in private.
        string getType()const{return rideable_type;}//const prepended to get functions.
        string getStartTime() const {return started_at;}
        string getEndTime()const{return ended_at;}
        string getStartStation() const {return start_station_name;}
        string getEndStation()const{return end_station_name;}
        long double getLat1() const {return start_lat;}
        long double getLong1() const {return start_lng;}
        long double getLat2()const{return end_lat;}
        long double getLong2()const{return end_lng;}
        string getMember() const {return member_casual;}
        void display();
    private:// Private contains all the values for the different types of data
        string ride_id; // Stored in the CSV file
        string rideable_type;
        string started_at;
        string ended_at;
        string start_station_name;
        string end_station_name;
        long double start_lat;// Start and end coordinates are the only values not stored as strings
        long double start_lng;
        long double end_lat;
        long double end_lng;
        string member_casual;
};//end of DivvyData class declaration.
//-------------------------------------------------------------------------------------------------
// DivvyData overloaded constructor definition;
DivvyData:: DivvyData(string ride_id, string rideable_type, string started_at,
                      string ended_at, string start_station_name, string end_station_name,
                      long double start_lat, long double start_lng, long double end_lat,
                      long double end_lng, string member_casual)
{   //This pointer refers to the variables stored in private
    // to differentiate from the values used as parameters
    this-> ride_id = ride_id;
    this-> rideable_type = rideable_type;
    this-> started_at = started_at;
    this-> ended_at = ended_at;
    this-> start_station_name = start_station_name;
    this-> end_station_name = end_station_name;
    this-> start_lat = start_lat ;
    this-> start_lng = start_lng;
    this-> end_lat = end_lat;
    this-> end_lng = end_lng;
    this-> member_casual = member_casual;
}
//DivvyData destructor
DivvyData::~DivvyData() {}
// DivvyData Copy Constructor
// DivvyData used as parameter with & and const
// added to pass as reference while not changing the object
DivvyData::DivvyData(const DivvyData &newDivvy)
{
    this-> ride_id = newDivvy.ride_id;
    this-> rideable_type = newDivvy.rideable_type;
    this-> started_at = newDivvy.started_at;
    this-> ended_at = newDivvy.ended_at;
    this-> start_station_name = newDivvy.start_station_name;
    this-> end_station_name = newDivvy.end_station_name;
    this-> start_lat = newDivvy.start_lat ;
    this-> start_lng = newDivvy.start_lng;
    this-> end_lat = newDivvy.end_lat;
    this-> end_lng = newDivvy.end_lng;
    this-> member_casual = newDivvy.member_casual;
}
//Display function for DivvyData class.
void DivvyData::display()
{
    cout << ride_id << endl
        << rideable_type<< endl
        <<  started_at<< endl
        << ended_at<< endl
        << start_station_name<< endl
        <<  end_station_name<< endl
        << start_lat<< endl
        << start_lng<< endl
        <<  end_lat<< endl
        <<  end_lng<< endl
        <<  member_casual << endl;
}
// Utility functions getting distant between two map points
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/
// converting degrees to radians
long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
            cos(lat1) * cos(lat2) *
            pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}
//--------------------------------------------------------------------------------------
// readFile function takes the file name as a parameter along with vector string
// of DivvyDataType passed as reference so changes reflected in main.
// The function itself reads from a CSV inputting each line into the vector DivvyData.
// Data from file not cleaned or input into DivvyData class.
void readFile(string fileName, vector<string> &DivvyDataType)
{
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( fileName);               // Opens file
    assert( inStream.fail() == false );     // Ensure file open worked

    // Clear vector in case it already had some words in it
    DivvyDataType.clear();
    // Will hold a string of data from file til end of line.
    string line;
    // getline will read to end of line then store value in line
    while( getline(inStream, line))
    {   // line is then appended to vector
        DivvyDataType.push_back(line);
    }   // repeats until end of file
    inStream.close();//closes file
}// end of readFile
//-----------------------------------------------------------------------------------------
// CleanDataFunction uses vectors DataFromFile and ListOfDivvyClasses both passed as references
// for changes to reflect in main while latter is a vector of DivvyData type.
// Function takes the string of values stored in DataFromFile and checks for missing
// data, appending them to ListOfDivvyClasses as an object of DivvyData.
// function returns int value of ListOfDivvyClasses size.
int CleanDataFunction( vector<string> &DataFromFile, vector<DivvyData> &ListOfDivvyClasses)
{   // string Variable names correspond to their value in CSV file
    string id, type, start, end, startStation, endStation, SstartLat, SstartLng, SendLat, SendLng, memberType;
    long double startLat, startLng, endLat, endLng;  // hold coordinate values after conversion

    stringstream ss; // Allows data Stream to be read from string rather than keyBoard

    ListOfDivvyClasses.clear();  //Clears list

    // for-loop iterates through the size of the vector. Starts at 1 to avoid labels from CSV file.
    // While being read as stream, getline is used to parse string until comma at which point
    // it is then stored in one of the variables.
    // It is then checked to make sure value stored is not empty.
    // if empty, loop continues and entry is not stored as Object.
    for(int line = 1; line < DataFromFile.size(); line++) // loop begins at first element of vector
    {   //clears previous entry
        ss.clear();
        // inputs string from vector, so it may be read as a stream by getline
        ss.str(DataFromFile.at(line));

        getline(ss,id, ',' );
        if( id == ""){continue;}
        getline(ss,type, ',' );
        if( type == ""){continue;}
        getline(ss,start, ',' );
        if( start == ""){continue;}
        getline(ss,end, ',' );
        if( end == ""){continue;}
        getline(ss,startStation, ',' );
        if( startStation == ""){continue;}
        getline(ss,endStation, ',' );
        if( endStation == ""){continue;}
        getline(ss,SstartLat, ',' );
        if( SstartLat == ""){continue;}
        getline(ss,SstartLng, ',' );
        if( SstartLng == ""){continue;}
        getline(ss,SendLat, ',' );
        if( SendLat == ""){continue;}
        getline(ss,SendLng, ',' );
        if( SendLng == ""){continue;}
        getline(ss,memberType, '\n' );
        if( memberType == ""){continue;}

        //if all the values had characters stored inside then coordinates converted to long double
        startLat = stod(SstartLat);
        startLng = stod(SstartLng);
        endLat = stod(SendLat);
        endLng = stod(SendLng);
        
        //after coordinates converted, DivvyData Object created using constructor
        DivvyData divvy( id,type,start,end,startStation,
                         endStation,startLat, startLng, endLat, endLng,memberType);
        ListOfDivvyClasses.push_back(divvy);  //appended to DivvyData vector.
    }
    return ListOfDivvyClasses.size(); //return number of clean data rides
}//end of CleanDataFunction
//------------------------------------------------------------------
// FindDisplayLongestTrip uses const Vector <DivvyData> vector passed
// to find the index of the longest trip in the list, while also updating the
// sum total of TotalMilesTraveled.
// Nothing returned and ListOfDivvyClasses unchanged.
void FindDisplayLongestTrip(const vector<DivvyData> &ListOfDivvyClasses)
{
    float AverageLength;           // average trip length
    int indexLongestTrip;          // position in vector
    float LongestTripDistance;     // Longest trip distance found
    long double TotalMilesTraveled;// Sum of total miles traveled
    long double lat1;              // Start station latitude
    long double long1;             // Start station longitude
    long double lat2;              // End station latitude
    long double long2;             // End station longitude

    TotalMilesTraveled = 0;   // values initialized to 0.0
    indexLongestTrip = 0;
    LongestTripDistance = 0.0;

    // uses for-loop to get the longest ride along with index of corresponding element
    for (int rides = 0; rides < ListOfDivvyClasses.size(); rides++)
    {
        lat1 = ListOfDivvyClasses.at(rides).getLat1();
        long1 = ListOfDivvyClasses.at(rides).getLong1();
        lat2 = ListOfDivvyClasses.at(rides).getLat2();
        long2 = ListOfDivvyClasses.at(rides).getLong2();

        // calls distance and assigns value to trip length
        long double tripLength = distance(lat1, long1, lat2, long2);

        if(LongestTripDistance < tripLength)
        {   // checks condition updates index and Longest trip so far
            indexLongestTrip = rides;
            LongestTripDistance = tripLength;
        }
        // updates Total Miles Traveled.
        TotalMilesTraveled = TotalMilesTraveled + tripLength;
    }

    AverageLength = TotalMilesTraveled / ListOfDivvyClasses.size();
    //displays trip info below.
    cout << endl;// round() rounds value
    cout << "Total # of miles traveled: "  << round(TotalMilesTraveled) << endl
        << "Average length of trips in miles: " << fixed << setprecision(1)<< AverageLength << endl
        << endl
        << "Longest trip information below: " << endl
        << "-------------------------------" << endl
        << "Trip ID: " << ListOfDivvyClasses.at(indexLongestTrip).getID() << endl
        << "Trip start location: "<< ListOfDivvyClasses.at(indexLongestTrip).getStartStation() << endl
        << "Trip end location: " << ListOfDivvyClasses.at(indexLongestTrip).getEndStation() << endl
        << "Trip distance in miles: "<< fixed << setprecision(1) << LongestTripDistance << endl
        << endl;
}// end of FindDisplayLongestTrip() function
//-------------------------------------------------------------------------------------------------------
// GetRiderPercentage uses Vector<DivvyData> passed as reference to output the percentage of members
// to casual riders. Uses getMember() to access data stored in string member of DivvyData class.
// Compares string retrieved to "member" and tallies members and casual, outputting the result.
void GetRiderPercentage( const vector<DivvyData> &ListOfDivvyClasses)
{
    float CasualRidePrcnt; // percent of casuals
    float MemberPrcnt;     // percent of members
    float numData = ListOfDivvyClasses.size();
    float members = 0;     // number of members
    float casual = 0;      // number of casuals

    // for-loop checks is value stored in members is equivalent to "member\r"
    // increments value if true.
    for(int ride = 0; ride < numData ; ride++)
    {
        if(ListOfDivvyClasses.at(ride).getMember() == "member")
        {
            members++;
        }
        else
        {
            casual++; //else increments casual
        }
    }

    // ratio stored as fractions
    float casualRideFract = (casual / numData);
    float memberFract = (members / numData);

    // Final percentage calculated by multiplying by 100.0 to store floating point.
    CasualRidePrcnt = casualRideFract * 100.0;
    MemberPrcnt = memberFract * 100.0;

    // outputs following with setprecision set to 1 to get 10ths place.
    cout << "Casual Rider Percentage: " << fixed << setprecision(1) << CasualRidePrcnt << "%" << endl
         << "Member Rider Percentage: " << MemberPrcnt << "%" << endl;
    cout << endl;
}//end of GetRiderPercentage
//---------------------------------------------------------------------------------------
// RiderPerHourSortFunction uses DivvyData vector of weekType and int vector of weekTypeHours both passed
// as references. Function takes the data stored in weekType and uses for-loop to iterate through loop
// checking start time of ride. String value is then converted to int hour, which corresponds
// to the element position in vector. Element of that vector is then incremented by one.
// RidesPerHourSortFunction called from SortWeekendWeekDay function below.
// Changes reflected back in main.
void RidesPerHourSortFunction(vector<DivvyData> &weekType, vector<int> &weekTypeHours)
{
    string tempString;   // stores start time
    int indexSpace;      // index of characters
    int indexColon;      // index of Colon
    int hour;            // hour value converted from string

    // for-loop iterate through DivvyData vector
    // parsing the values held in startTime
    // then converting them to an int stored in hour
    for(int dataEntry = 0; dataEntry < weekType.size(); dataEntry++)
    {
        tempString = weekType.at(dataEntry).getStartTime();
        indexSpace = tempString.find(' ');
        indexColon = tempString.find( ':', indexSpace + 1);

        hour = stod(tempString.substr(indexSpace, indexColon));//stod converts to int

        weekTypeHours.at(hour)++; // hour then used to increment corresponding element in vector.
    }
} // end of RidesPerHourSortFunction()
//-----------------------------------------------------------------------------------------------------------------
// SortWeekendWeekDay function takes parameter vector<DivvyData> list and vector<int> weekdayHours and weekendHours
// all passed as references. Function sorts object in list by weekday and weekend, appending them to
// the two DivvyData vectors declared in the function.
// After ListOfDivvyClasses sorted through, function then calls RidesPerHourSortFunction to further
// tally number of rides per hour.
void SortWeekendWeekDay( const vector<DivvyData> &ListOfDivvyClasses, vector<int> &weekdayHours, vector<int> &weekendHours)
{
    string tempString;          // hold start date
    vector<DivvyData> weekday;  // will hold data of rides which occurred on a week day
    vector<DivvyData> weekend;  // will hold data of rides which occurred on a weekend.

    int index;  // hold index of character

    // for loop iterates through ListOfDivvyClasses
    // storing the start time in temp string,
    // then finding the index of the 2nd
    // '/' after which tempString is updated
    // to hold only the values up until the 2nd '/'
    for (int dataEntry = 0; dataEntry < ListOfDivvyClasses.size(); dataEntry++)
    {
        tempString = ListOfDivvyClasses.at(dataEntry).getStartTime();
        index = tempString.find('/');
        index = tempString.find( '/', index + 1);

        tempString = tempString.substr(0, index);

        // temp string is then checked to see if its values match the strings
        // below which correspond to the weekends of september.
        if( tempString == "9/4" ||tempString == "9/5"||tempString == "9/11"||
            tempString == "9/12"||tempString ==  "9/18"||tempString ==  "9/19"||
            tempString ==  "9/25"||tempString ==  "9/26")
        {
            //if true added to weekend DivvyData vector
            weekend.push_back(ListOfDivvyClasses.at(dataEntry));
        }
        else
        {   // else appended to weekday DivvyData Vector
            weekday.push_back(ListOfDivvyClasses.at(dataEntry));
        }
    }

    // RidesPerHourSortFunction called twice to tally rides per hour
    RidesPerHourSortFunction(weekend, weekendHours);
    RidesPerHourSortFunction(weekday, weekdayHours);
} // end of SortWeekendWeekDay function
//------------------------------------------------------------------------------------
// findMax functions uses const vector<int> &weekdayHours, const vector<int> &weekendHours as
// parameters. Runs a for loop checking that at least one of the vectors is greater than the max.
// If either are true, checks which vector element is greater, then updates value of max rides to
// the element of the vector containing more rides. No changes should be made to vector so declared
// as const. float returned representing maxRides.
float findMax(const vector<int> &weekdayHours, const vector<int> &weekendHours)
{   // maxRides initialized, declared as float type to store floating point.
    float maxRides = 0;
    for(int hour = 0; hour < weekdayHours.size(); hour++)
    {   // checks that maxRides is less than either
        if( maxRides < weekdayHours.at(hour) || maxRides < weekendHours.at(hour))
        {   //if condition met, checks which vector was greater
            if(weekdayHours.at(hour) < weekendHours.at(hour))
            {   // maxRides updated to value of winner
                maxRides = weekendHours.at(hour);
            }
            else if(weekdayHours.at(hour) > weekendHours.at(hour) )
            {
                maxRides = weekdayHours.at(hour);
            }
        }
    }
    return maxRides;// value returned to main.
}//end of findMax function
//--------------------------------------------------------------------------------------------------
// closestDivvyStation function takes vector<DivvyData> &ListOfDivvyData, long double userLat, long double userLng
// as parameters with the vector passed as reference but prepended with const since function should not
// change List. Function uses for-loop to iterate through data, calling distance function to store distance in d1
// which is then compared to shortestDistance variable updating it and the index in the process.
// Nothing returned to main, but outputs to user the closest divvy station to them
// along with the distance from their coordinates.
void closestDivvyStation(const vector<DivvyData> &ListOfDivvyData, long double userLat, long double userLng)
{
    long double lat1, long1;  // coordinates of station
    float d1;                 // distance from each station
    float shortestDistance;   // shortestDistance from house
    string StationName;       // station closest to house
    int indexOfClosest = 0;   // element position in vector

    // for loop will continually update
    // shortestDistance
    // when shorter distance found
    // Index of data in vector updated as well.
    shortestDistance = 1000000;
    for(int dataEntry = 0; dataEntry < ListOfDivvyData.size(); dataEntry++)
    {   //for loop initializes values of lat1 and lat2 for each ride stored in vector
        lat1 = ListOfDivvyData.at(dataEntry).getLat1();
        long1 = ListOfDivvyData.at(dataEntry).getLong1();

        d1 = distance(userLat, userLng, lat1, long1);

        if(shortestDistance > d1)
        {   // Variables updated.
            shortestDistance = d1;
            indexOfClosest = dataEntry;
        }
    }
    
    //indexOfClosest stores value of vector element where shortestDistance found.
    cout << "Closest Divvy station is: " << ListOfDivvyData.at(indexOfClosest).getStartStation()
         << " at " << setprecision(10)
         << ListOfDivvyData.at(indexOfClosest).getLat1() << ", "
         << ListOfDivvyData.at(indexOfClosest).getLong1() << ", "
         << fixed << setprecision(1) << shortestDistance << " miles away."
         << endl;
}//end of closestStation function
//--------------------------------------------------------------------------------------------------------------
// The program analyses divvy bike ride information from september reading from a file selected in option one, then
// cleaned. If ListOfDivvyClasses, which contains data from the file, is empty, the user will only be able
// to select 1 ( or exit) until data is read into a file. The program makes uses of classes to store
// data from the CSV file corresponding to ride_id,rideable_type,started_at,ended_at,
// start_station_name,end_station_name,start_lat,start_lng,end_lat,end_lng,member_casual
// from file which can then be accessed through the use of accessors. Users can display overall trip
// information, the percent of members to casual riders, graphically display rides per hours, and determine
// the closest divvy station to their location. Options stored in a while loop, which when accessed call to other
// functions to complete their request. Program exits when 6 selected.
int main()
{
    int userChoice;         // first user choice updates in main body of while loop
    int fileChoice;         // 2nd user choice updated when 1st option selected
    int userChoiceOption4;  // user choice updated in option 4 to select options
    int totalTrips;         // contains total amount of uncleaned trips
    int cleanDataTrips;     // contains total trips after cleaning
    float maxRides;         // contains maxRides per hour

    vector <string> DataFromFile; // will contain string of lines from CSV file
    vector<DivvyData> ListOfDivvyClasses; // will contain objects of Divvy data

    cout << "Analyze Divvy bike ride information using September trip data.\n"
         << "First select option 1 to read and clean the data. \n";

    while(true)
    {   // displays menu options
        cout << "Select a menu option: \n"
            << "1. Select datafile, display rides totals and clean data \n"
            << "2. Display overall trip information\n"
            << "3. Display percentage of members vs. casual riders \n"
            << "4. Display weekday vs weekend usage \n"
            << "5. Extra Credit: find closest station \n"
            << "6. Exit \n"
            << "Your choice --> \n";
        cin >> userChoice;

        if(userChoice == 6)
        {
            break; // exits program when 6 selected
        }
        if( userChoice == 1) // must be chosen before 2-5
        {
            cout << "Select datafile: \n"
                << "1. Small subset of data with 14 rides to help create your program \n"
                << "2. Week day vs weekend rides \n"
                << "3. All September 2021 data (not tested in Zybooks) \n"
                << "Your selection--> ";
                cin >> fileChoice;

            switch(fileChoice) // readFile function called for all options
            {
                case 1:readFile("divvyridesampledata.csv", DataFromFile);break;
                case 2:readFile("weekdayweekend.csv", DataFromFile); break;
                case 3:readFile("all_divvy_rides_september.csv", DataFromFile); break;
            }

            // totalTrips will be the total size of vector - 1 (first line are labels)
            totalTrips = DataFromFile.size() - 1;
            cleanDataTrips = CleanDataFunction(DataFromFile, ListOfDivvyClasses); //returns size of list
            // ListOfDivvyClasses now store objects of cleaned data.
            cout << "Total # of trips found in datafile: " << totalTrips << endl
                 << "Total # of trips in clean data: " << cleanDataTrips << endl
                 << endl;
        }
        // if ListOfDivvyClasses.empty() evaluates to true
        // program will continue looping prompting user to select
        // file to be read.
        if(!ListOfDivvyClasses.empty()) // after Data read from file options 2-5 accessible.
        {
            if(userChoice == 2)
            {   //Function finds and displays the longest Trip information
                FindDisplayLongestTrip(ListOfDivvyClasses);
                continue;
            }
            if(userChoice == 3)
            {   //Function called which will display the rider percentage
                GetRiderPercentage(ListOfDivvyClasses);
                continue;
            }
            if(userChoice == 4)
            {   // new int vectors declared and initialized to (24, 0)
                // with each element corresponding
                // to the number of rides for each
                // 24-hour day.
                vector<int> weekdayHours(24, 0);
                vector<int> weekendHours(24, 0);

                cout << "Select type of display: \n"
                     << "1. Counts of rides per hour in the day \n"
                     << "2. Proportional 50 column graph with @ for weekday and + for weekend \n"
                     <<  "Your selection-->";
                cin >> userChoiceOption4;

                //function sorts weekend and weekday rides
                SortWeekendWeekDay(ListOfDivvyClasses, weekdayHours, weekendHours);
                maxRides = findMax(weekdayHours, weekendHours);  // finds max rides per hour

                if(userChoiceOption4 == 1)   // output weekDay values and weekend
                {
                    cout << "LargestNumberOfRides is:" << maxRides << endl
                         << "Rides per hour for weekday and weekend: " << endl;
                    for(int hour = 0; hour < weekdayHours.size(); hour++)
                    {
                        cout << setw(2);
                        cout << hour << ":";
                        cout << setw(6) << setfill(' ') << weekdayHours.at(hour)
                             << setw(6) << setfill(' ') << weekendHours.at(hour) << endl;
                    }

                }
                else if(userChoiceOption4 == 2)  // outputs graph of weekend rides vs weekDay
                {
                    for(int hour = 0; hour < 24; hour++)
                    {
                        cout << hour << ":";
                        int multiplier = (weekdayHours.at(hour) / maxRides) * 50;
                        for(int k = 0; k < multiplier; k++)
                        {
                            cout << "@";
                        }
                        cout << endl << "  ";
                        int multiplier2 = (weekendHours.at(hour) / maxRides) * 50;
                        for(int j = 0; j < multiplier2; j++)
                        {
                            cout << "+";
                        }
                        cout << endl;
                    }
                }
            }
            if(userChoice == 5)
            {   // option prompts user to input coordinates
                // to determine the closest divvy station
                long double userLat, userLng;
                string StationName;

               cout << "Input latitude and longitude of the home: ";
               cin >> userLat >> userLng;
               cout << endl
                    << "You entered: "
                    << setprecision(3)
                    << userLat
                    << " for latitude and "
                    << userLng
                    << " for longitude"
                    << endl;
                // calls function determining the shortest distance and outputting
                // station information.
               closestDivvyStation(ListOfDivvyClasses, userLat, userLng);
               continue;
            }
        }
        else
        {
            cout << "First read in data by selecting menu option 1" << endl;
        }
    }
    return 0;
}