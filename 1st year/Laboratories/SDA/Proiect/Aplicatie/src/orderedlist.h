#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#define OLNIL -1

// forward declarations
template<typename T> struct OLNode;
template<typename T> class OLIterator;
template<typename T> class OrderedList;

/**
 * Ordered list node
 */
template<typename T>
struct OLNode
{
    T data;
    int prev;
    int next;
};

/**
 * Ordered list iterator
 */
template<typename T>
class OLIterator
{
private:
    int current;
    int position;
    OrderedList<T>& list;

public:
    OLIterator(OrderedList<T>& list) : position{ 0 }, list{ list }
    {
        current = list.head;
    }

    ~OLIterator() {}

    /**
     * @brief element
     * @return
     */
    T element() const
    {
        if (!valid())
        {
            throw "Iterator has finished iterating!";
        }
        return list.link_table[current].data;
    }

    /**
     * @brief remove
     * @return
     */
    T remove()
    {
        if (!valid())
        {
            throw "Iterator has finished iterating!";
        }
        return list.remove(position);
    }

    /**
     * @brief valid
     * @return
     */
    bool valid() const
    {
        return current != OLNIL;
    }

    /**
     * @brief next
     */
    void next()
    {
        if (!valid())
        {
            throw "Iterator has finished iterating!";
        }
        ++position;
        current = list.link_table[current].next;
    }
};

/**
 * Ordered list
 */
template<typename T>
class OrderedList
{
    friend class OLIterator<T>;
private:
    int head;
    int tail;
    int size;
    int capacity;
    bool* is_free;
    OLNode<T>* link_table;

    void validate_position(int position) const
    {
        if (position >= size || position < 0)
        {
            throw "Out of range position!";
        }
    }

    int get_index(int position) const
    {
        int index = head;
        while (position)
        {
            index = link_table[index].next;
            --position;
        }
        return index;
    }

    int get_free_index() const
    {
        int index;
        for (index = 0; !is_free[index]; ++index);
        return index;
    }

public:
    OrderedList(int capacity) : capacity{ capacity }
    {
        size = 0;
        head = tail = OLNIL;
        is_free = new bool[capacity];
        link_table = new OLNode<T>[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            is_free[i] = true;
        }
    }

    ~OrderedList()
    {
        delete[] this->link_table;
        delete[] this->is_free;
    }

    /**
     * @brief insert
     * @param element
     */
    void insert(const T& element)
    {
        // throw exception if list is full
        if (size == capacity)
        {
            throw "Cannot add more elements!";
        }
        // find free space for the new element
        int ins_index = get_free_index();
        link_table[ins_index] = { element, OLNIL, OLNIL };
        is_free[ins_index] = false;
        ++size;
        // empty list insertion
        if (size == 1)
        {
            head = tail = ins_index;
        }
        // insertion before the first element
        else if (element <= link_table[head].data)
        {
            link_table[ins_index].next = head;
            link_table[head].prev = ins_index;
            head = ins_index;
        }
        // insertion after the last element
        else if (link_table[tail].data <= element)
        {
            link_table[ins_index].prev = tail;
            link_table[tail].next = ins_index;
            tail = ins_index;
        }
        // insertion between elements
        else
        {
            int prev, next = head;
            while (link_table[next].data <= element)
            {
                prev = next;
                next = link_table[next].next;
            }
            link_table[next].prev = ins_index;
            link_table[prev].next = ins_index;
            link_table[ins_index].prev = prev;
            link_table[ins_index].next = next;
        }
    }

    /**
     * @brief remove
     * @param position
     * @return
     */
    T remove(int position)
    {
        validate_position(position);
        int index = get_index(position);
        is_free[index] = true;
        --size;
        // last element in list
        if (size == 0)
        {
            head = tail = OLNIL;
        }
        // element at the beginning of the list
        else if (position == 0)
        {
            int next = link_table[index].next;
            link_table[next].prev = OLNIL;
            head = link_table[head].next;
        }
        // element at the end of the list
        else if (position == size)
        {
            int prev = link_table[index].prev;
            link_table[prev].next = OLNIL;
            tail = link_table[tail].prev;
        }
        // element in the middle of the list
        else
        {
            int prev = link_table[index].prev;
            int next = link_table[index].next;
            link_table[prev].next = next;
            link_table[next].prev = prev;
        }
        return link_table[index].data;
    }

    /**
     * @brief find
     * @param element
     * @return
     */
    int find(const T& element) const
    {
        int current = head;
        int position = 0;
        while (current != OLNIL)
        {
            if (link_table[current].data == element)
            {
                return position;
            }
            current = link_table[current].next;
            ++position;
        }
        return OLNIL;
    }

    /**
     * @brief at
     * @param position
     * @return
     */
    T at(int position) const
    {
        validate_position(position);
        int index = get_index(position);
        return link_table[index].data;
    }

    /**
     * @brief empty
     * @return
     */
    bool empty() const
    {
        return size == 0;
    }

    /**
     * @brief length
     * @return
     */
    int length() const
    {
        return size;
    }

    /**
     * @brief iterator
     * @return
     */
    OLIterator<T> iterator()
    {
        return OLIterator<T>(*this);
    }
};

#endif // ORDEREDLIST_H
