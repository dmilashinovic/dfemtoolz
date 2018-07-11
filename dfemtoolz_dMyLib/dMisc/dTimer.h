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

/*
 * File:   dTimer.h
 *
 *
 *
 *
 *
 */

#ifndef _TIMER_H
#define	_TIMER_H

#include "../dfemtoolz_dMyLib.h"
#include <time.h>


class Timer
{
private:
    static Timer * m_pTimerSingleton;
    clock_t m_cStart, m_cEnd;

protected:
    Timer();

public:
    void set_start_time();
    void set_end_time();

    double get_time_interval_in_seconds_from_start_to_end();
    double get_time_interval_in_seconds_from_start_to_now();
    double get_time_interval_in_miliseconds_from_start_to_end();
    double get_time_interval_in_miliseconds_from_start_to_now();
    double get_time_interval_in_microseconds_from_start_to_end();
    double get_time_interval_in_microseconds_from_start_to_now();
    double get_clock_count_from_start_to_end();
    double get_clock_count_from_start_to_now();


    void print_time_interval_in_seconds_from_start_to_end();
    void print_time_interval_in_seconds_from_start_to_now();
    void print_time_interval_in_miliseconds_from_start_to_end();
    void print_time_interval_in_miliseconds_from_start_to_now();
    void print_time_interval_in_microseconds_from_start_to_end();
    void print_time_interval_in_microseconds_from_start_to_now();

    static Timer * createTimer();

    ~Timer();
};

#endif	/* _TIMER_H */


