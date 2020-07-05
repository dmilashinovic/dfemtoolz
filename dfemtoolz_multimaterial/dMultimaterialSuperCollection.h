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
 * File:   dSuperCollection.h
 *
 *
 *
 *
 *
 */

#ifndef _MULTIMATERIALSUPERCOLLECTION_H
#define	_MULTIMATERIALSUPERCOLLECTION_H


#include "../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../dfemtoolz_dMyLib/dBase/dCollection.h"
#include "../dfemtoolz_dMyLib/dBase/dSuperCollection.h"


#include <algorithm>
#include <vector>

template<class T>
class MultiaterialSuperCollection
{
private:
    vector <Collection <T> > m_vSuperCollection;

    bool supercollection_by_colection_size_compare_function
    (Collection <T> coll1, Collection <T> coll2);

public:

    void insert(const Collection <T> &collection);

    UINT get_size();

    void clear_superCollection();
    void Limin8(UINT collectionID);
    void Limin8_flagged(bool flag);

    void clear_superCollection_p();
    void Limin8_p(UINT collectionID);
    void Limin8_flagged_p(bool flag);

    void sort_supercollection_by_colection_size();

    void transfer_items_from_collectionA_2_collectionB(UINT collectionA_ID, UINT collectionB_ID);

    SuperCollection& operator = (const SuperCollection &a);
    Collection <T> & operator [] (UINT collectionID);

//    template<class U> friend class Collection;
};

template <class T>
bool compare_collections(Collection<T> a, Collection<T> b)
{
    return (a.get_size() < b.get_size());
}

template <class T>
void SuperCollection<T>::insert(const Collection <T> &collection)
{
    m_vSuperCollection.push_back(collection);
}

template <class T>
UINT SuperCollection<T>::get_size()
{
    return m_vSuperCollection.size();
}

template <class T>
void SuperCollection<T>::clear_superCollection()
{
    m_vSuperCollection.clear();
}

template <class T>
void SuperCollection<T>::clear_superCollection_p()
{
    if (!m_vSuperCollection.empty())
    for (UINT i = 0; i < m_vSuperCollection.size(); i++)
    if (m_vSuperCollection[i].get_size() != 0)
    for (UINT j = 1; j <= m_vSuperCollection[i].get_size(); j++)
        delete m_vSuperCollection[i][j];

    m_vSuperCollection.clear();
}

template <class T>
void SuperCollection<T>::Limin8(UINT collectionID)
{
    m_vSuperCollection.erase(m_vSuperCollection.begin() + collectionID - 1);
}

template <class T>
void SuperCollection<T>::Limin8_p(UINT collectionID)
{
    if(!m_vSuperCollection[collectionID - 1].empty())
    for (UINT i = 0; i < m_vSuperCollection[collectionID - 1].size(); i++)
        delete m_vSuperCollection[collectionID - 1][i];

    m_vSuperCollection.erase(m_vSuperCollection.begin() + collectionID - 1);
}

template <class T>
void SuperCollection<T>::Limin8_flagged(bool flag)
{
    for (UINT i = 0; i < m_vSuperCollection.size();)
    {
        if (m_vSuperCollection[i].get_flag() == flag)
            m_vSuperCollection.erase(m_vSuperCollection.begin() + i);
        else
            i++;
    }
}

template <class T>
void SuperCollection<T>::Limin8_flagged_p(bool flag)
{
    for (UINT i = 0; i < m_vSuperCollection.size();)
    {
        if (m_vSuperCollection[i].get_flag() == flag)
        {
            m_vSuperCollection[i].clear_collection_p();
            m_vSuperCollection.erase(m_vSuperCollection.begin() + i);
        }
        else
            i++;
    }
}

template <class T>
void SuperCollection<T>::sort_supercollection_by_colection_size()
{
//    typename vector <T*>::iterator it;
    sort(m_vSuperCollection.begin(), m_vSuperCollection.end());
}

template <class T>
bool SuperCollection<T>::supercollection_by_colection_size_compare_function
(Collection <T> coll1, Collection <T> coll2)
{
    return (coll1.get_size() < coll2.get_size());
}

template <class T>
void SuperCollection<T>::transfer_items_from_collectionA_2_collectionB
(UINT collectionA_ID, UINT collectionB_ID)
{
/*
    m_vSuperCollection[collectionB_ID - 1].insert(
    m_vSuperCollection[collectionB_ID - 1].m_vCollection.end(),
    m_vSuperCollection[collectionA_ID - 1].m_vCollection.begin(),
    m_vSuperCollection[collectionA_ID - 1].m_vCollection.end());

    m_vSuperCollection[collectionA_ID - 1].clear_collection();
*/
    for (UINT i = 1; i <= m_vSuperCollection[collectionA_ID - 1].get_size(); i++)
        m_vSuperCollection[collectionB_ID - 1].insert(m_vSuperCollection[collectionA_ID - 1][i]);
    m_vSuperCollection[collectionA_ID - 1].clear_collection();
}

template <class T>
SuperCollection<T>& SuperCollection<T>::operator = (const SuperCollection &otherSuperCollection)
{
    m_vSuperCollection = otherSuperCollection.m_vSuperCollection;
    return (*this );
}

template <class T>
Collection <T> & SuperCollection<T>::operator [] (UINT collectionID)
{
    return m_vSuperCollection[collectionID - 1];
}


#endif	/* _DGEOM_COLLECTION_H */
