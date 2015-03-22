// $Id: intqueue.java,v 1.3 2013-01-24 19:44:29-08 - - $

import java.util.Iterator;
import java.util.NoSuchElementException;

class intqueue implements Iterable<Integer> {

   private class node {
      int linenr;
      node link;
   }
   private int count = 0;
   private node front = null;
   private node rear = null;

   public void insert (int number) {
      ++count;
     // misc.trace (count);
     if(number != 0){
      node tmp = new node();	 
      tmp.linenr = number;
      tmp.link = null;	
      if(rear == null) front = tmp;
	else rear.link = tmp;
      rear = tmp; 
	}  
  }

   public boolean empty() {
      return count == 0;
   }

   public int getcount() {
      return count;
   }

   public Iterator<Integer> iterator() {
      return new iterator();
   }

   private class iterator implements Iterator<Integer> {
      node curr = front;

      public boolean hasNext() {
         return curr != null;
      }

      public Integer next() {
         if (curr == null) throw new NoSuchElementException();
         Integer next = curr.linenr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }

}

