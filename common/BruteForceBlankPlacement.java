/* Read a string from the standard input and determine if it is
 * a concatenation of words from the dictionary. Allowed words are
 * in the file words.txt, which we store in a balanced binary search
 * tree. This program uses the brue-force approach of considering all
 * possible positions for blanks.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;
import java.util.TreeSet;

public class BruteForceBlankPlacement {

	public static void main(String[] args) {

		// Read dictionary file, store in balanced tree.
		File file = new File("/afs/cad/courses/ccs/s19/cs/435/common/words.txt");
		TreeSet<String> dict = new TreeSet<String>();

		try {
			Scanner scanner = new Scanner(file);
			while (scanner.hasNext()) {
				String line = scanner.next();
				dict.add(line);
			}
			scanner.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		// Read the input string from standard input.
		Scanner input = new Scanner(System.in);
		String str = input.next();

		int n = str.length();
		
		// Consider all 2^{n-1} possible blank positions.
		for (int i = 0; i < Math.pow(2, n - 1); ++i) {
			boolean[] b = new boolean[n - 1];
			// b[j] indicates if blank goes after j-th character.
			for (int j = 0; j < n - 1; ++j) {
				b[j] = ((i & (1 << (j))) >= 1) ? true : false;
			}
			
			// x is the original string with blanks inserted.
			String x = str.substring(0, 1);
			for (int j = 0; j < n - 1; ++j) {
				if (b[j])
					x += " " + str.substring(j + 1, j + 2);
				else
					x += str.substring(j + 1, j + 2);
			}
			x += str.substring(n - 1, n - 1);
			String[] words = x.split(" ");

			// Now see if we have a sequence of dictionary words.
			boolean success = true;
			for (String s : words) {
				if (!dict.contains(s))
					success = false;
			}
			if (success) {
				for (String s : words)
					System.out.print(s + " ");
				System.out.println();
			}

		}
	}
}
