import java.util.Iterator;
import java.util.concurrent.atomic.AtomicInteger;

/** 
 * Implementation of the Linked List Class.
 * @see MySet
 * @see MyQueue
 * @param E object-type to be held in collection. 
 * @author Kamil Kaya
 * @version 1.0
 * @since 2021-01-22
*/


public class MyLinkedList<E> implements MyList<E>, MyQueue<E> {

    private E[] Container;
    private AtomicInteger size;
    private int capacity;
    private E lastElement;
    private E firstElement;

    public MyLinkedList() {

        capacity = 10;
        Container = (E[]) new Object[capacity];
        size = new AtomicInteger(0);
        lastElement = null;
        firstElement = null;
    }

    public MyIterator<E> iterator() {

        E[] temp = Container;

        return new MyIterator<E>(temp, size);
    }

    @Override
    public void add(E e) {
        if (size.get() < capacity) {
            Container[size.get()] = e;
            size.set(size.get()+1);
        }
        else {
            capacity = 2*capacity;
            E[] temp = (E[]) new Object[capacity];

            for (int i = 0; i < size(); ++i)
                temp[i] = Container[i];

            temp[size.get()] = e;
            size.set(size.get()+1);
            Container = temp;
        }
        lastElement = e;
        if(size() == 1)
            firstElement = e;

        
    }

    @Override
    public void addAll(MyCollection c) throws ClassCastException {

        Iterator<E> itr = c.iterator();
        while (itr.hasNext())
            add(lastElement = itr.next());
    }

    @Override
    public void clear() {
        size.set(0);
    }

    @Override
    public boolean contains(E e) {

        if (isEmpty())
            return false;

        for (int i=0; i < size(); i++)
            if(Container[i].equals(e))
                return true;

        return false;
    }

    @Override
    public boolean containsAll(MyCollection c) {

        if(c.size() == 0)
            return false;

        Iterator<E> itr = c.iterator();
        while (itr.hasNext())
            if (!contains(itr.next()))
                return false;

        return true;
    }

    @Override
    public boolean isEmpty() {

        return size() == 0;
    }

    @Override
    public void remove(E e) {

        if(!contains(e))
            return;

        E[] temp = (E[]) new Object[capacity];
        boolean first_encounter = false;

        for (int i=0, j=0; i<size(); ++i)
            if (Container[i] == e && !first_encounter)
                first_encounter = true;
            else
                temp[j++] = Container[i];

        Container = temp;
        size.set(size()-1);
    }

    @Override
    public void removeAll(MyCollection c) {

        Iterator<E> itr = c.iterator();

        while(itr.hasNext())
            remove(itr.next());

    }

    @Override
    public void retainAll(MyCollection c) {

        Iterator<E> itr = iterator();
        E temp;

        while(itr.hasNext())
            if (!c.contains(temp = itr.next()))
                remove(temp);
    }

    @Override
    public int size() { return size.get(); }

    /**
     * Retrieves, but does not remove, the head of this queue.
     * @return the head of the queue which is Generic type E.
     */
    public E element(){

        if (size() == 0)
            throw new ArrayStoreException("There is no element in the container yet.");

        return firstElement;
    }

    /**
     * Inserts the specified element into this queue.
     * @param e element
     */
    public void offer(E e){
        add(e);
    }

    /**
     *
     * @return Retrieves and removes the head of this queue, or throws if this
     *         queue is empty.
     * @throws Exception
     */
    public E poll() throws ArrayStoreException{

        if (size() == 0)
            throw new ArrayStoreException("There is no element in the container yet.");

        E temp = Container[0];
        firstElement = Container[1];
        remove(Container[0]);

        return temp;
    }

    @Override
    public String toString() {
        String temp= "[";
        for(int i =0; i < size(); ++i) {
            temp += Container[i].toString();
            if (i == size()-1)
                temp += "]";
            else
                temp += ", ";
        }
        return "LinkedList{" +
                "Container=" + temp +
                ", size=" + size() +
                ", capacity=" + capacity +
                ", lastElement=" + lastElement +
                '}';
    }
}
