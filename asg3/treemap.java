// $Id: treemap.java,v 1.1 2012-02-07 15:43:17-08 - - $

// Development version of treemap.
// To be deleted and replaced by an actual implementation that
// does *NOT* use java.util.TreeMap.

import static java.lang.System.*;

class treemap {

   class tree {
      String key;
      String value;
      tree left;
      tree right;
      int depth;
      public tree(String k, String v){
         key = k;
	 value = v;
      }
   }

   
   tree root = null;
   tree tmp = new tree(null, null);

   public void runToString(String key) {
      toString(root, key, 0);
   }

   public void toString(tree root, String key, int depth) {
      if(root == null) return;
      toString(root.left, key, depth + 1); 
      if(root.key.equals(key))
           out.printf("%3d \"%s\" \"%s\" %s %s%n", depth, root.key, root.value, root.left, root.right); 
      toString(root.right, key, depth + 1);

   }

   public void runInOrder(){
      inOrder(root, 0);
   }

   public void inOrder (tree root, int depth) {
      if(root == null) return;
      inOrder(root.left, depth + 1);
      out.println(depth + " " + root.key + " " +  root.value + " " + 
            root.left + " " + root.right); 
      inOrder(root.right, depth + 1);
   }

   public String get (String key) {
      return findInTree(root, key);
   }
 
   public String findInTree (tree curr, String key){
      while (curr != null) {
	 int cmp = curr.key.compareTo(key);
	 if(cmp == 0) return curr.value;
	 if(cmp > 0) curr = curr.right;
	 else curr = curr.left;
         }
   return null;
   }
   

   public void put (String key, String value) {
      if(get(key) == null)
         root = insertInTree(root, key, value);   
   }

   public tree insertInTree(tree curr, String key, String value) {
      if (curr == null) return new tree(key, value);
      if (curr.key.compareTo(key) < 0)
         curr.left = insertInTree(curr.left, key, value);
      else
	 curr.right = insertInTree(curr.right, key, value);
      return curr;	  
   }

   public void debug_tree (String key) {
      debug_tree_recur (root, key, 0);
   }

   private void debug_tree_recur (tree root, String key, int depth) {
    /* if(node.left != null) {
         debug_tree_recur (node.left, depth + 1);
      }
      if(node.right != null) {
         debug_tree_recur (node.right, depth +1);
      }*/
      out.printf("%s: \"%s\" \"%s\"\n", "Root node contains", 
	     root.key, root.value);
      while(true) {
         if(key.equals(root.key)){
	    out.println("Key Found");
	    out.printf("%s:%3d \"%s\" \"%s\" %s %s\n", 
	          "DEBUG INFORM.", depth, root.key, root.value,
		  root.left, root.right);
	    out.print("Enter Again? ");
	    break;
	 }
	 else if (key.compareTo(root.key) < 0) {
	    depth++;
	    out.printf("%s%s: \"%s\" \"%s\"\n",
		 "Going to left of tree..",
		 "node containts", root.key, root.value);
	    root = root.left;
	    if(root == null) {
	       out.println("null found on left node");  
	       break;
	    }
	 }
	 else {
	    depth++;
	    out.printf("%s%s: \"%s\" \"%s\"\n",
		 "Going to right of tree..",
		 "node contains", root.key, root.value);
	    root = root.right;
	    if(root == null) {
	       out.println("null found on right node");
	       break;
	    }		     
         } 
      }
   }
}
