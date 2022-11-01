#include "pch.h"
#include "List.h"

template<typename T>
 List<T>::List()
{
}

template<typename T>
 List<T>::List(const List<T>& list)
{
	 List<T> result;
	 for (POSITION pos = list.GetHeadPosition(); pos != NULL; list.GetNext(pos))
	 {
		 T value = list.GetAt(pos);
		 result.AddTail(value);
	 }
	 return result;
}

template<typename T>
 void List<T>::Remove(T value)
{
	 for (POSITION pos = GetHeadPosition(); pos != NULL; GetNext(pos))
	 {
		 if (GetAt(pos) == value) {
			 RemoveAt(pos);
		 }
	 }
}

template<typename T>
 List<T> List<T>::FilterIf(BOOL Predicate(T value)) const
{
	 List<T> result;

	 for (POSITION pos = GetHeadPosition(); pos != NULL; GetNext(pos))
	 {
		 T value = GetAt(pos);
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
	 for (POSITION pos = GetHeadPosition(); pos != NULL; GetNext(pos))
	 {
		 T value = GetAt(pos);
		 if (Predicate(value)) {
			 count++;
		 }
	 }
	 return count;
}