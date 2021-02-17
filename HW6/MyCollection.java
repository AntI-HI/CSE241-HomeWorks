import java.util.Iterator;

/** 
 * Represents the Collection interface.
 * @param E object-type to be held in collection. 
 * @author Kamil Kaya
 * @version 1.0
 * @since 2021-01-22
*/

public interface MyCollection<E> extends Iterable<E> {

    /**
     * Returns an iterator over the collection
     * @return MyIterator, iterator over collection.
     * @see Iterator
     */
    @Override
    public Iterator<E> iterator();

    /**
     * Ensures that this collection contains the specified element.
     **/
    public void add(E e);

    /**
     * Adds all of the elements in the specified collection to this
     * collection.
     **/
    public void addAll(MyCollection c);

    /**
     * Removes all of the elements from this collection.
     **/
    public void clear();

    /**
     * Returns true if this collection contains the specified element.
     * @return true if collection contains specified element, false if
     * collection does not contain the specified element.
     **/
    public boolean contains(E e);

    /**
     * Returns true if this collection contains all of the elements in the
     * specified collection.
     * @return true if collection contains the specified collection's all
     * elements, false if the collection does not contain at least one element
     * from the specified collection.
     **/
    public boolean containsAll(MyCollection c);

    /**
     * Returns true if this collection contains no elements.
     * @return true if collection is empty, false if it's not empty.
     **/
    public boolean isEmpty();

    /**
     * Removes a single instance of the specified element from this
     * collection, if it is present.
     **/
    public void remove(E e);

    /**
     * Removes all of this collection's elements that are also contained
     * in the specified collection.
     **/
    public void removeAll(MyCollection c);

    /**
     * Retains only the elements in this collection that are contained in
     * the specified collection.
     **/
    public void retainAll(MyCollection c);

    /**
     * Returns the number of elements in this collection.
     * @return size of the collection.
     **/
    public int size();
}
