/*
    This file is part of dfemtoolz software package.
*
    dfemtoolz software package is free software: 
*   you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, 
*   either version 3 of the License, or (at your option) any later version.

*   dfemtoolz software package is distributed in the hope that 
    it will be useful, but WITHOUT ANY WARRANTY; without even the 
*   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
    See the GNU General Public License for more details.
*
    You should have received a copy of the GNU General Public License
*   along with dfemtoolz software package.  
    If not, see <http://www.gnu.org/licenses/>.
*
    For any additional info contact author of this software:
*   
    Danko Milasinovic
*   dmilashinovic@gmail.com
    dmilashinovic@kg.ac.rs    
*/

#include "dTimer.h"

Timer::Timer()
{
    m_cStart = clock();
}

Timer * Timer::m_pTimerSingleton = 0;
Timer * Timer::createTimer()
{
    if (m_pTimerSingleton == 0)
        m_pTimerSingleton = new Timer;
    return m_pTimerSingleton;
}

Timer::~Timer()
{
    delete m_pTimerSingleton;
    m_pTimerSingleton = 0;
}

void Timer::set_start_time()
{
    m_cStart = clock();
}

void Timer::set_end_time()
{
    m_cEnd = clock();
}

double Timer::get_time_interval_in_seconds_from_start_to_end()
{
    return ((double) ((m_cEnd - m_cStart) / CLOCKS_PER_SEC));
}

double Timer::get_time_interval_in_seconds_from_start_to_now()
{
    clock_t time_now = clock();
    return ((double) ((time_now - m_cStart) / CLOCKS_PER_SEC));
}

double Timer::get_time_interval_in_miliseconds_from_start_to_end()
{
    return ((double) ((m_cEnd - m_cStart) / (CLOCKS_PER_SEC / 1000)));
}

double Timer::get_time_interval_in_miliseconds_from_start_to_now()
{
    clock_t time_now = clock();
    return ((double) ((time_now - m_cStart) / (CLOCKS_PER_SEC / 1000)));
}

double Timer::get_time_interval_in_microseconds_from_start_to_end()
{
    double result = 0;
    if (CLOCKS_PER_SEC != 0)
        result = (double) ((m_cEnd - m_cStart) / (CLOCKS_PER_SEC / 1000000));
    return result;
}

double Timer::get_time_interval_in_microseconds_from_start_to_now()
{
    clock_t time_now = clock();
    double result = 0;
    if (CLOCKS_PER_SEC != 0)
        result = (double) ((time_now - m_cStart) / (CLOCKS_PER_SEC / 1000000));
    return result;
}

double Timer::get_clock_count_from_start_to_end()
{
    return ((double) (m_cEnd - m_cStart));
}

double Timer::get_clock_count_from_start_to_now()
{
    clock_t time_now = clock();
    return ((double) (time_now - m_cStart));
}

void Timer::print_time_interval_in_seconds_from_start_to_end()
{
    cout << endl << " time used: " << ((double) ((m_cEnd - m_cStart) / CLOCKS_PER_SEC))  <<
    " seconds" << endl << endl;
}

void Timer::print_time_interval_in_seconds_from_start_to_now()
{
    clock_t time_now = clock();
    cout << endl << " time used: " << ((double) ((time_now - m_cStart) / CLOCKS_PER_SEC)) <<
    " seconds" << endl << endl << endl <<
    "          ...   " << endl << endl << endl;
}

