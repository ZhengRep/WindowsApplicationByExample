#pragma once

template<typename T>
class List : public CList<T>
{
public:
	List();
	List(const List<T>& list);

	void Remove(T value);
	List<T> FilterIf(BOOL Predicate(T value)) const;
	int CountIf(BOOL Predicate(T value)) const;
};


