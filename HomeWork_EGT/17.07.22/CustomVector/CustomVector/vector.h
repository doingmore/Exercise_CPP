#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>

#define incrementStep 2

template<typename T>
class Vector
{
public:

	Vector() : m_size{ 0 }, m_capacity{ 0 }
	{}
	Vector& operator= (const Vector& other) // only for types without members pointers
	{
		if (this == &other)
		{
			return *this;
		}
		if (this->m_list != NULL)
		{
			delete[] m_list;
		}

		m_size = other.m_size;
		m_capacity = other.m_capacity;

		m_list = new T[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_list[i] = other.m_list[i];
		}

		return *this;
	}

	Vector(const Vector& other) // only for types without members pointers
		: m_size{ other.m_size }
		, m_capacity{ other.m_capacity }
	{
		m_list = new T[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_list[i] = other.m_list[i];
		}
	}

	~Vector()
	{
		erase();   // don't calling virtual functions from constructor or destructor , but other functions ??? 
	}

	// ================================================== Operations  =====================================================

	void push_back(const T& element);
	void pop_back();

	// ================================================= Element access ======================================================

	T& operator[] (const size_t& index)
	{
		if (index < 0 || index > m_size)
		{
			std::cout << "EXCEPTION" << '\n';
			throw _EXCEPTION_;
		}
		return m_list[index];
	}
	T& first() { return m_list[0]; }           // reference to the first element 
	T& back() { return m_list[m_size - static_cast<size_t>(1) ]; }  // Reference to the last element. 
	T& at(const size_t& index)
	{
		return m_list[index];
	}

	// =================================================== Iterators  ==================================================
	
	struct iterator {
		using pointer = T*;  // or also value_type*
		using reference = T&;  // or also value_type&
		iterator(pointer ptr)  // pass return address from begin() or end()
			: m_ptr(ptr)
		{}

		reference   operator*  () const { return *m_ptr; }
		pointer     operator-> () { return m_ptr; }

		iterator& operator++   ()    { m_ptr++; return *this; }
		iterator  operator++   (int) { iterator temp = *this; ++(*this); return temp; } // this++

		friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		pointer m_ptr;
	};

	iterator begin() {
		T* parameter = &m_list[0];          
		iterator answer{ parameter };
		return answer;
	}

	iterator end() {
		T* parameter = &m_list[m_size];
		iterator answer{ parameter };
		return answer;
	}


	 
	// =================================================== Capacity ==================================================

	size_t size()     const { return m_size; }
	size_t capacity() const { return m_capacity; }
	bool   empty()    const { return m_list == NULL; }
	void   reserve(const size_t& newCapacity);  //Increase the capacity of the vector the total number of elements that the vector can hold without requiring reallocation. use for performance

	// ================================================== Modifiers  ==================================================

	void resize(const size_t& newSizeAndCapacity);   // after resize pushback must work after resized elements ! 
	void erase();
private:
	
	size_t m_size;                                     
	size_t m_capacity;
	T* m_list = NULL;

};


template<typename T>
void Vector<T>::push_back(const T& element)
{
	
	if ( m_size == m_capacity  && m_size == 0)
	{
		m_capacity++; // 0*2=0
		m_list = new T[m_capacity];      
	}
	else if (m_size == m_capacity && m_size != 0)  // case when I reach the capacity of vector
	{
		m_capacity = m_capacity * incrementStep;

		T* oldArray = m_list;
		m_list = NULL;

		m_list = new T[m_capacity];             
		for (int i = 0; i < m_size; i++)
		{
			m_list[i] = oldArray[i];
		}

		delete[] oldArray;
	}

	m_list[m_size] = element;
	m_size++;
}


template<typename T>
void Vector<T>::pop_back()                        // can will be more performance  
{
	T* oldArray = m_list;

	m_list = new T[m_capacity];

	for (int i = 0; i < m_size - 1; i++)
	{
		m_list[i] = oldArray[i];
	}
	delete[] oldArray;
}

template<typename T>
void   Vector<T>::reserve(const size_t& newCapacity)
{
	// Requests that the vector capacity be at least enough to contain n elements.
	// This function has no effect on the vector size and cannot alter its elements.

	if (newCapacity > m_capacity)
	{
		T* oldArray = m_list;

		m_list = new T[newCapacity];

		// do copy if old array have some allocate memory
		if (oldArray != NULL)
		{
			for (int i = 0; i < m_size; i++)    //  attention! copy only elements until m_size 
			{
				m_list[i] = oldArray[i];
			}
			delete[] oldArray;
		}

		m_capacity = newCapacity;
	}
	// else do nothing
}

template<typename T>
void Vector<T>::resize(const size_t& n)   // n - new size , after resize pushback must work after resized elements ! 
{
	// in all cases function changes the actual content of the container by inserting or erasing elements from it.
	if ( m_size < n && m_capacity < n )
	{
		// case 1 when we use resize,  n > size and n > capacity  example first action with vector
		// other example push two element and resize on 4 previously two element must be copy and keep alive
		// new size and new capacity must be equal on n

		T* oldArray = m_list;

		m_list = new T[n]{};   // create default objects
		if (oldArray != NULL ) // do copy 
		{
			for (size_t i = 0; i < m_size; i++)
			{
				m_list[i] = oldArray[i];
			}
                                     
			delete[] oldArray;                     
		}

		m_size = n;
		m_capacity = n;
	}
	else if (n < m_size )
	{
		// Case 2 : If n is smaller than the current container size, the content is reduced to its first n elements,
		// removing those beyond (and destroying them). Capacity will keep same.

		T* oldArray = m_list;

		m_list = new T[m_capacity];   //  same capacity
		for (size_t i = 0; i < n; i++)   //  attention! copy only elements until newSize n
		{
			m_list[i] = oldArray[i];
		}

		delete[] oldArray;
		
		m_size = n;                   //   for this case res ONLY size
	}
}

template<typename T>
void Vector<T>::erase()
{
	m_size = 0;
	m_capacity = 0;

	delete[] m_list;

	m_list = NULL;
}



#endif // !VECTOR_H

