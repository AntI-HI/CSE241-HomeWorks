/** 
 * Represents the Queue interface.
 * @param E object-type to be held in collection. 
 * @author Kamil Kaya
 * @version 1.0
 * @since 2021-01-22
*/

public interface MyQueue<E> extends MyCollection<E> {

    /**
     * Retrieves, but does not remove, the head of this queue.
     * @return the head of the queue which is Generic type E.
     */
    public E element();

    /**
     * Inserts the specified element into this queue.
     * @param e element
     */
    public void offer(E e);

    /**
     *
     * @return Retrieves and removes the head of this queue, or throws if this
     *         queue is empty.
     * @throws Exception
     */
    public E poll() throws Exception;

}
