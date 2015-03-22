// Dylan Woodbury (dwoodbur)
// $Id: wordct.java,v 1.12 2013-01-14 17:26:13-08 - - $
//
// NAME
// 	wordct - count lines, words, characters in files
//
// SYNOPSIS
// 	wordct [-lwc] [filename...]
// DESCRIPTION
// 	The wordct utility reads one or more input files, and by default,
// 	writes out the number of lines, words, and bytes contained in the
// 	input files to stdout. If more than one input file is specified,
// 	the total count for all of the files is also written. If more
// 	than one input file is specified, the total count for all of the
// 	files is also written to stdout.
//
// NOTES
// 	This program assumes text files.
//
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;
import java.util.ArrayList;

class wordct {
	static final String STDIN_NAME = "-";

	//Inner convenience class for counting entities
	static class counts {
		int linecount;
		int wordcount;
		int charcount;
        	String filename;
	}
	
	static class options {
		boolean countlines = true;
		boolean countwords = true;
		boolean countchars = true;
	}
	
	//
	// NAME
	// 	checkWidth(MEASUREMENT)
	//
	// DESCRIPTION
	// 	Returns the value of how many spaces are needed to
	// 	display a number.
	public static int checkWidth(int measurement){
		int width = 0;

		if(measurement < 10){
			return 1;
		}
		else if(measurement < 100){
			return 2;
		}
		else if(measurement < 1000){
			return 3;
		}
		else if(measurement < 10000){
			return 4;
		}
		else if(measurement < 100000){
			return 5;
		}
		else if(measurement < 1000000){
			return 6;
		}
		else if(measurement < 10000000){
			return 7;
		}
		return width;
	} 
	//
	// NAME
	// 	displayStats(ARRAYLIST, OPTIONS)
	//
	// DESCRIPTION
	// 	Displays the number of lines, words, and characters in the
	// 	inputted files, depending on which stats the user wants to see,
	// 	and totals them. Displays stats depending on how much space
	// 	is needed.
	//
	
	public static void displayStats(ArrayList<counts> countsList, options opts, boolean usingStdIn){
		int maxWidth = 0;
		counts total = new counts();
		String format = "%7d";
		
		if(usingStdIn == false){
			for(int i = 0; i < countsList.size(); i++){
				counts count = new counts();
			
				counts thisCount = countsList.get(i);
				total.linecount += thisCount.linecount;
				total.wordcount += thisCount.wordcount;
				total.charcount += thisCount.charcount;
			}
			if(opts.countchars == true) maxWidth = checkWidth(total.charcount);
			else if(opts.countwords == true) maxWidth = checkWidth(total.wordcount);
			else maxWidth = checkWidth(total.linecount);
			format = "%" + maxWidth + "d"; 
		}
		for(int i = 0; i < countsList.size(); i++){
			counts thisCount = countsList.get(i);
			if(opts.countlines == true) out.printf(format + " ", thisCount.linecount);
			if(opts.countwords == true) out.printf(format + " ", thisCount.wordcount);
			if(opts.countchars == true) out.printf(format + " ", thisCount.charcount);
			if(thisCount.filename != "-") out.printf("%s", thisCount.filename);
			out.printf("%n");
		}
			
		if(countsList.size() > 1 ){
			if(opts.countlines == true) out.printf(format + " ", total.linecount);
			if(opts.countwords == true) out.printf(format + " ", total.wordcount);
			if(opts.countchars == true) out.printf(format + " ", total.charcount);
			out.printf("total%n"); 	
		}
	}


	
	
	//
	// NAME
	// 	countfile (SCANNER)
	//
	// DESCRIPTION
	// 	Uses nextLine to read lines from an open Scanner.
	// 	Counts chars/words/lines in file.
	//
        static counts countfile (String filename, Scanner scan, counts total) {
		counts count = new counts();
		if (scan != null) {
			while (scan.hasNextLine()) {
				String line = scan.nextLine();
				if(line.equals("")) count.wordcount--;
				count.charcount += line.length()+1;
				String trimmedLine = line.trim().replaceAll(" +", " ");
				trimmedLine = trimmedLine.replaceAll("\t"," ");/**/ 
				String[] words = trimmedLine.trim().split("\\s+");
				count.wordcount += words.length;
					
				++count.linecount;
			}
		}
		count.filename = filename;
		return count;
	}

	// NAME
	// 	main
	//
	// DESCRIPTION
	// 	Main function of the class. Causes a service function to
	// 	emit the contents of the standard input, if no args, and to
	// 	emit each file in turn, if args.
	//
	public static void main (String[] args) {
		counts total = new counts();
		options opts = new options();
		ArrayList<counts> countsList = new ArrayList<counts>();
		String details = " ";
		int newArrayStart = 0;
		boolean usingStdIn = false;		
		if(args.length != 0){ 
			if(args[0].charAt(0) == '-') {
				opts.countlines = false; opts.countwords = false; opts.countchars = false;
			}
			for(int i = 0; args[i].charAt(0) == '-'; i++){
				details = args[i].substring(1);
				for(int j = 0; j < details.length(); j++){
					switch(details.charAt(j)){
						case 'l': opts.countlines = true;
							  break;
						case 'w': opts.countwords = true;
							  break;
						case 'c': opts.countchars = true;
							  break;	
					}	
				}
				if(i == args.length-1) break;	
			}
			for(int i = 0; i < args.length; i++){
				if(args[i].charAt(0) == '-') newArrayStart++;
			}
		}
		else if(args.length == 0) usingStdIn = true;
		if (args.length < 1 || newArrayStart == args.length) {
			countsList.add(countfile (STDIN_NAME, new Scanner (System.in), total));
		}
		else {
			for (int itor = newArrayStart ; itor < args.length; ++itor) {
				String filename = args[itor];
				if (filename.equals (STDIN_NAME)) {
					countfile(filename, new Scanner (System.in), total);
				}
				else {
					try {
						Scanner scan = new Scanner (new File (filename));
						countsList.add(countfile (filename, scan, total));
						scan.close();
					}
					catch (IOException error) {
						misclib.warn (error.getMessage());
						countsList.add(countfile (filename, null, total));
					}
				}
			}
		}
		displayStats(countsList, opts, usingStdIn);
		exit (misclib.exit_status);
	}
}	
