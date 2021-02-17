import java.util.Iterator;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

/** 
 * Implementation of the Iterator Class.
 * @see Iterator
 * @param E object-type to be held in collection. 
 * @author Kamil Kaya
 * @version 1.0
 * @since 2021-01-22
*/


public class MyIterator<E> implements Iterator<E> {

    private E[] array;  // Container.
    private E lastmove; // Last move returned so far.
    private int index;  // Position Indicator for Container.
    private AtomicInteger size;

    /**
     * Constructor
     * @param container Takes a container that we want to iterate.
     */
    public MyIterator(E[] container, AtomicInteger size) {

        array = container;
        this.size = size;
        index = 0;

    }

    /**
     * Returns true if the iteration has more elements.
     * @return true if the index value is less than length of the array.
     */
    @Override
    public boolean hasNext() {

        return index < size.get();

    }

    /**
     * Returns the next element in the iteration and advances the
     * iterator.
     * @return the next element.
     */
    @Override
    public E next() throws ArrayIndexOutOfBoundsException{
        if(hasNext()) {
            lastmove = array[index++];
            return lastmove;
        }
        else throw new ArrayIndexOutOfBoundsException("There is no next element in this container.");
    }

    /**
     * Removes from the underlying collection the last element returned
     * by this iterator. This method does not work for Queues, it throws
     * an exception.
     * @throws ArrayIndexOutOfBoundsException if there is no last move
     * returned so far then throws exception
     */
    public void remove() throws ArrayIndexOutOfBoundsException {

        if (index == 0)
            throw new ArrayIndexOutOfBoundsException("There is no element to remove in the container.");
        
        E[] temp = (E[]) new Object[size.get()-1];

        for (int i = 0, j = 0; i < size.get(); ++i)
            if (array[i] != lastmove)
                temp[j++] = array[i];

        size.set(size.get()-1);  

        for (int i = 0; i < size.get(); ++i)
            array[i] = temp[i];

        lastmove = array[--index];

    }
}
