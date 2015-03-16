#############################
#GLPK write routine
#############################
open (OUTFILE, ">./lp/petersen.cc");

$durr = "\n";

print OUTFILE "#include <stdio.h>\n#include <stdlib.h>\n#include <glpk.h>\n\nint main(void)\n{\n\tglp_prob *lp;\n\tint ia[1+1000], ja[1+1000];\n\tdouble ar[1 + 1000], z,";

for ($i = 1; $i <=14; $i++) {print OUTFILE " x". $i . ", "; }print OUTFILE "x15;\n";

print OUTFILE "\tlp = glp_create_prob();\n\tglp_set_prob_name(lp, \"sample\");\n\tglp_set_obj_dir(lp, GLP_MAX);\n\tglp_add_rows(lp,23);\n\tglp_add_cols(lp,15);";

for ($j = 1; $j <= 23; $j++) {
	print OUTFILE "\tglp_set_row_name(lp, " . $j .", \"r" . $j . "\");\n\tglp_set_row_bnds(lp, " . $j . ", GLP_UP, 0.0, 1.0);\n"; }

for ($j = 1; $j <= 15; $j++) {
	print OUTFILE "\tglp_set_col_name(lp, " . $j .", \"x" . $j . "\");\n\tglp_set_col_bnds(lp, " . $j . ", GLP_LO, 0.0, 0.0);\n\tglp_set_obj_coef(lp, " . $j . ", 1);\n"; }

#close OUTFILE;
$array_data = `./petersen_main 5`;# ("./petersen_main 5 >> testing.txt");#./lp/petersen.cc");

print OUTFILE $array_data;
#open (OUTFILE2, '>>',"testing.txt"); #./lp/petersen.cc") or die "blarg";

print OUTFILE "\tglp_load_matrix(lp, 60, ia, ja, ar);\n\tglp_simplex(lp,NULL);\n\tz = glp_get_obj_val(lp);\n\t";

for ($j = 1; $j <= 15; $j++) {
	print OUTFILE "\n\tx" . $j . " = glp_get_col_prim(lp, ". $j . ");"; }
print OUTFILE "\n\t" . 'printf("\nz = \%g; ';

for ($j = 1; $j <= 15; $j++) { print OUTFILE "x" . $j . " = \%g; ";}
 
print OUTFILE '\n' . "\", z, ";

for ($j = 1; $j <= 14; $j++) { print OUTFILE "x" . $j . ", ";}

print OUTFILE "x15);\n\t glp_delete_prob(lp);\n\treturn 0;\n\n}";

##########################
#Complie and run glpk code
##########################

system ( "g++ ./lp/petersen.cc -lglpk -lm -o glpk_exec");
$glpk_output = `./glpk_exec`;
print $glpk_output;
