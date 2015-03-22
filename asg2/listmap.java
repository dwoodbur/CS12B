// $Id: listmap.java,v 1.3 2013-01-24 19:44:02-08 - - $

import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import static java.lang.System.*;

class listmap implements Iterable<Entry<String,intqueue>> {

   private class node implements Entry<String,intqueue> {
      String key;
      intqueue queue = new intqueue();
      node link;
      public String getKey() {
         return key;
      }
      public intqueue getValue() {
         return queue;
      }
      public intqueue setValue (intqueue queue) {
         throw new UnsupportedOperationException();
      }
   }
   private node head = null;

   public listmap() {
      // Not needed, since head defaults to null anyway.
   }

   public void insert (String key, int linenr) {
   //   misc.trace ("insert", key, linenr);
	 node prev = null;
	 node curr = head;
	 int cmp = 1;
	 while(curr != null) {
	    cmp = curr.key.compareTo (key);
	    if(cmp > 0) break;
            if(cmp == 0) { curr.queue.insert(0); break; } 
	    prev = curr;
	    curr = curr.link;
	 }
	 if(cmp != 0){ 
	    node tmp = new node();
	    tmp.key = key;	
	    tmp.link = curr;

	    tmp.queue.insert(linenr);
	    if(prev == null) head = tmp;
	        else prev.link = tmp;
   }
}
   public Iterator<Entry<String,intqueue>> iterator() {
      return new iterator();
   }

   private class iterator implements Iterator<Entry<String,intqueue>> {
      node curr = head;

      public boolean hasNext() {
         return curr != null;
      }

      public Entry<String,intqueue> next() {
         if (curr == null) throw new NoSuchElementException();
         node next = curr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }

   }

}
