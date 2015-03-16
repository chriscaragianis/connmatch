#########################################################
#
# mtx2dot.pl
#
# input is a plain text file containing the entries of 
# an adjacency matrix.  Output is a .dot file suitable
# for input into graphviz.
#
#########################################################
open(MATRIX,"./matrix.dat") or die;
open(GRAPH, ">graph1.dot");
#Print graph header

print GRAPH "graph G {\n\tnode[shape=point];\n\t";


#Parse adjacency matrix file into edges

$linecount = 0;
$charcount = 0;
$char = "a";
$dim = "0";
#print $dim;


while (<MATRIX>) {	
	chop;
	if ($linecount == 0) {$dim = $_; $linecount++; next;} 
	$charcount = $dim;
	
	$row = $_;
	chop $row;
	while ($row) {
		$char = chop $row;
		chomp $charcount;
		print GRAPH $linecount . "--" . $charcount . ";\n\t" if ($char == "1");
		$charcount--;
		last if ($charcount <= $linecount);
		#print $linecount;
	}
	
	$linecount++;
	$charcount = $dim;
}

#Print closing brace
print GRAPH "}\n";
