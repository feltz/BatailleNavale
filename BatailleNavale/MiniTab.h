#pragma once
template <class T>
class MiniTab
{
public:
	int m_nb_elems;
	T* m_elems;
	inline MiniTab (const int nb_elems) : m_nb_elems(nb_elems) {
		m_elems = new T[nb_elems]; }
	inline MiniTab(const MiniTab& tab) : m_nb_elems(tab.m_nb_elems) {
		m_elems = new T[m_nb_elems]; 
		for (int i = 0; i < m_nb_elems; i++) 
			m_elems[i] = tab.m_elems[i];  
		}
	inline ~MiniTab() { delete m_elems; }
};