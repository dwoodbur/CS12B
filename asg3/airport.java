// $Id: airport.java,v 1.2 2013-01-31 17:00:19-08 - - $

//
// Starter code for the airport utility.
//

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class airport {
   private static final String STDIN_FILENAME = "-";

   public static treemap load_database (String database_name) {
      treemap tree = new treemap ();
      try {
         Scanner database = new Scanner (new File (database_name));
         for (int linenr = 1; database.hasNextLine(); ++linenr) {
            String line = database.nextLine();
            if (line.matches ("^\\s*(#.*)?$")) continue;
            String[] keyvalue = line.split (":");
            if (keyvalue.length != 3) {
               misc.warn (database_name, linenr, "invalid line");
               continue;
            }
            tree.put (keyvalue[0], keyvalue[1]);
         }
         database.close();
      }catch (IOException error) {
         misc.warn (error.getMessage());
      }
      return tree;
   } 

   public static void main (String[] args) {
      int pos=0;
      if(args[0].equals("-d")) pos = 1;
      treemap tree = load_database (args[pos]);
      Scanner stdin = new Scanner (in);
         tree.runInOrder();
         while (stdin.hasNextLine()) {
            String airport = stdin.nextLine().toUpperCase().trim();
            String airport_name = tree.get (airport);
            if(args[0].equals("-d")) {
		tree.debug_tree(airport);
	    }
	    else {
               if (airport_name == null) {
                  out.printf ("%s: no such airport%n", airport);
               }
               else {
                  tree.runToString(airport);
               }
            }
         }
      exit (misc.exit_status);
   }

}
