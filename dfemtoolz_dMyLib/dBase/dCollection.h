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
 * File:   dCollection.h
 *
 *
 *
 *
 *
 */

#ifndef _DCOLLECTION_H
#define	_DCOLLECTION_H


#include "../dfemtoolz_dMyLib.h"

#include <vector>

template<class T>
class Collection
{
private:
    bool m_bFlag;

public:

    vector <T> m_vCollection;

    void insert(const T &item);

    void set_flag();
    void set_flag(bool flag);
    bool get_flag() const;

    UINT get_size() const;

    void sort_collection();
    void no_overlapping();

    void make_duplicate_from(Collection <T> & otherCollection);

    void clear_collection();
    void Limin8(UINT itemID);
    void Limin8_flagged(bool flag);

    void clear_collection_p();
    void Limin8_p(UINT itemID);
    void Limin8_flagged_p(bool flag);

    void concaten8(Collection <T> & otherCollection);

    Collection& operator = (const Collection &a);
    bool operator < (const Collection & a) const;
    T& operator [] (UINT itemID);

    Collection();
//    Collection(Collection <T> & otherCollection);
};

template <class T>
Collection<T>::Collection()
{
    m_bFlag = false;
}

/*
template <class T>
Collection<T>::Collection(Collection & a <T>)
{
    m_bFlag = false;
    vector <T> m_vCollection(Collection::m_vCollection);
}
*/

template <class T>
void Collection<T>::insert(const T & item)
{
    m_vCollection.push_back(item);
}

template <class T>
void Collection<T>::set_flag()
{
    m_bFlag = !m_bFlag;
}

template <class T>
void Collection<T>::set_flag(bool flag)
{
    m_bFlag = flag;
}

template <class T>
bool Collection<T>::get_flag() const
{
    return m_bFlag;
}

template <class T>
UINT Collection<T>::get_size() const
{
    return m_vCollection.size();
}

template <class T>
void Collection<T>::sort_collection()
{
    sort(m_vCollection.begin(), m_vCollection.end());
}

template <class T>
void Collection<T>::no_overlapping()
{
    m_vCollection.erase( unique( m_vCollection.begin(), m_vCollection.end() ), m_vCollection.end() );
}

template <class T>
void Collection<T>::make_duplicate_from(Collection <T> & otherCollection)
{
    m_vCollection.swap(otherCollection.m_vCollection);
}

template <class T>
void Collection<T>::clear_collection()
{
    m_bFlag = false;
    m_vCollection.clear();
}

template <class T>
void Collection<T>::clear_collection_p()
{
    m_bFlag = false;

    if(!m_vCollection.empty())
    for (UINT i = 0; i < m_vCollection.size(); i++)
        delete m_vCollection[i];

    m_vCollection.clear();
}

template <class T>
void Collection<T>::Limin8(UINT itemID)
{
    m_vCollection.erase(m_vCollection.begin() + itemID - 1);
}

template <class T>
void Collection<T>::Limin8_p(UINT itemID)
{
    delete m_vCollection[itemID - 1];
    m_vCollection.erase(m_vCollection.begin() + itemID - 1);
}

template <class T>
void Collection<T>::Limin8_flagged(bool flag)
{
    for (UINT i = 0; i < m_vCollection.size();)
    {
        if (m_vCollection[i].get_flag() == flag)
            m_vCollection.erase(m_vCollection.begin() + i);
        else
            i++;
    }
}

template <class T>
void Collection<T>::Limin8_flagged_p(bool flag)
{
    for (UINT i = 0; i < m_vCollection.size();)
    {
        if (m_vCollection[i].get_flag() == flag)
        {
            delete m_vCollection[i];
            m_vCollection.erase(m_vCollection.begin() + i);
        }
        else
            i++;
    }
}

template <class T>
void Collection<T>::concaten8(Collection <T> & otherCollection)
{
    m_vCollection.insert(m_vCollection.end(), otherCollection.m_vCollection.begin(), otherCollection.m_vCollection.end());
}

template <class T>
bool Collection<T>::operator < (const Collection & a) const
{
    return (this->get_size() < a.get_size());
}

template <class T>
Collection<T>& Collection<T>::operator = (const Collection &otherCollection)
{
    m_bFlag = otherCollection.m_bFlag;
    m_vCollection = otherCollection.m_vCollection;
    return (*this );
}

template <class T>
T& Collection<T>::operator [] (UINT itemID)
{
    return m_vCollection[itemID - 1];
}

#endif	/* _DCOLLECTION_H */
