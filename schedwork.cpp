#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool schedulehelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row_index, int col_index, std::vector<size_t>& num_shifts /*std::set<size_t> workers*/); 

//create 
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed, //daily need is number of workers needed per day
    const size_t maxShifts, //max shifts any workers is allowed over n day period
    DailySchedule& sched //sched has nothing right now
)
{
    //we need to initialise sched, for loop
    
    //created by n * d matrix for sched,

    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    for(int i = 0; i < avail.size(); i++){ //avail.size() = # of days
        sched.push_back(std::vector<Worker_T>(dailyNeed, -1)); 
    }



    //availability matrix to loop through the workers
    //use data structure need to keep track of # of workers that have worked, increment and decrement vector, numshifts
    
    //need to keep track of num shifts, increment once go through for loop, decrement if you return
    
    
    // Add your code below

    //avail is an n by k (row =  one day of schedule, by col = one worker's availability) matrix of each of the k workers' availability over n-day period

    //sched is an n by d matrix with d workers IDs who are schedule to work on each of the n days
    int row_index = 0;
    int col_index = 0; 

    std::vector<size_t> num_shifts(avail[0].size(), 0); //initialise size to # of workers, and to 0 shifts per worker
    
    //std::set<size_t> workers; 
    return schedulehelper(avail, dailyNeed, maxShifts, sched, row_index, col_index, num_shifts /*workers*/); 

    //schedulehelper(avail, dailyNeed, maxShifts, sched, row_index, col_index, num_shifts, workers); 
    
    }



    








bool schedulehelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row_index, int col_index, std::vector<size_t>& num_shifts/*, std::set<size_t>workers*/){

//std::cout << row_index << " " << avail.size() << std::endl;

if(row_index == avail.size()){ //BC, we pass the final row

    return true; 
}


if(sched[row_index][col_index] == -1){ //hits an invalid ID, we can fill it in

for(size_t i = 0; i < avail[0].size(); i++){ //iterates through the avail columns in singular row
//check if they are working that day, 
    if(avail[row_index][i] == 1 /*worker available on specific day*/ /*workers.find(i) == workers.end()*/ /*can't find in set*/  && num_shifts[i] < maxShifts){ //i = worker id (given current row and availability)
    
    //workers.insert(i); 
    num_shifts[i]++; //increment numshifts for user by 1 
    //recursive call?
    sched[row_index][col_index] = i; //userID gets filled in
    //worker 1 is not able to work on day 1
    bool check = true; 
        if(col_index == dailyNeed - 1){
        check = schedulehelper(avail, dailyNeed, maxShifts, sched, row_index + 1, 0, num_shifts/* workers*/);

        }
        else{
    check = schedulehelper(avail, dailyNeed, maxShifts, sched, row_index, col_index + 1, num_shifts/*workers*/);
        } 
            if(check == true){
            return true; 
            }

    //un do everything +set to normal 
    //workers.erase(i); 
     num_shifts[i]--;
    sched[row_index][col_index] = -1;

    }
    

}
 


}

return false;


}



