#include "pch.h"
#include "List.h"

template<typename T>
 List<T>::List()
{
	 
}

template<typename T>
 List<T>::List(const List<T>& list)
{
	 for (POSITION pos = list.GetHeadPosition(); pos != NULL; list.GetNext(pos))
	 {
		 T value = list.GetAt(pos);
		 m_list.AddTail(value);
	 }
}

template<typename T>
 void List<T>::Remove(T value)
{
	 for (POSITION pos = m_list.GetHeadPosition(); pos != NULL; m_list.GetNext(pos))
	 {
		 if (m_list.GetAt(pos) == value) {
			 m_list.RemoveAt(pos);
		 }
	 }
}

template<typename T>
 List<T> List<T>::FilterIf(BOOL Predicate(T value)) const
{
	 List<T> result;

	 for (POSITION pos = m_list.GetHeadPosition(); pos != NULL; m_list.GetNext(pos))
	 {
		 T value = m_list.GetAt(pos);
		 if (Predicate(value)) {
			 result.AddTail(value);
		 }
	 }
	 return result;
}

template<typename T>
 int List<T>::CountIf(BOOL Predicate(T value)) const
{
	 int count = 0;
	 for (POSITION pos = m_list.GetHeadPosition(); pos != NULL; m_list.GetNext(pos))
	 {
		 T value = m_list.GetAt(pos);
		 if (Predicate(value)) {
			 count++;
		 }
	 }
	 return count;
}