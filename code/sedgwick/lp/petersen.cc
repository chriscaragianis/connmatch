#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{
	glp_prob *lp;
	int ia[1+1000], ja[1+1000];
	double ar[1 + 1000], z, x1,  x2,  x3,  x4,  x5,  x6,  x7,  x8,  x9,  x10,  x11,  x12,  x13,  x14, x15;
	lp = glp_create_prob();
	glp_set_prob_name(lp, "sample");
	glp_set_obj_dir(lp, GLP_MAX);
	glp_add_rows(lp,23);
	glp_add_cols(lp,15);	glp_set_row_name(lp, 1, "r1");
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 2, "r2");
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 3, "r3");
	glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 4, "r4");
	glp_set_row_bnds(lp, 4, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 5, "r5");
	glp_set_row_bnds(lp, 5, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 6, "r6");
	glp_set_row_bnds(lp, 6, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 7, "r7");
	glp_set_row_bnds(lp, 7, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 8, "r8");
	glp_set_row_bnds(lp, 8, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 9, "r9");
	glp_set_row_bnds(lp, 9, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 10, "r10");
	glp_set_row_bnds(lp, 10, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 11, "r11");
	glp_set_row_bnds(lp, 11, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 12, "r12");
	glp_set_row_bnds(lp, 12, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 13, "r13");
	glp_set_row_bnds(lp, 13, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 14, "r14");
	glp_set_row_bnds(lp, 14, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 15, "r15");
	glp_set_row_bnds(lp, 15, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 16, "r16");
	glp_set_row_bnds(lp, 16, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 17, "r17");
	glp_set_row_bnds(lp, 17, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 18, "r18");
	glp_set_row_bnds(lp, 18, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 19, "r19");
	glp_set_row_bnds(lp, 19, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 20, "r20");
	glp_set_row_bnds(lp, 20, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 21, "r21");
	glp_set_row_bnds(lp, 21, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 22, "r22");
	glp_set_row_bnds(lp, 22, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 23, "r23");
	glp_set_row_bnds(lp, 23, GLP_UP, 0.0, 1.0);
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 1, 1);
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 2, 1);
	glp_set_col_name(lp, 3, "x3");
	glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 3, 1);
	glp_set_col_name(lp, 4, "x4");
	glp_set_col_bnds(lp, 4, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 4, 1);
	glp_set_col_name(lp, 5, "x5");
	glp_set_col_bnds(lp, 5, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 5, 1);
	glp_set_col_name(lp, 6, "x6");
	glp_set_col_bnds(lp, 6, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 6, 1);
	glp_set_col_name(lp, 7, "x7");
	glp_set_col_bnds(lp, 7, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 7, 1);
	glp_set_col_name(lp, 8, "x8");
	glp_set_col_bnds(lp, 8, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 8, 1);
	glp_set_col_name(lp, 9, "x9");
	glp_set_col_bnds(lp, 9, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 9, 1);
	glp_set_col_name(lp, 10, "x10");
	glp_set_col_bnds(lp, 10, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 10, 1);
	glp_set_col_name(lp, 11, "x11");
	glp_set_col_bnds(lp, 11, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 11, 1);
	glp_set_col_name(lp, 12, "x12");
	glp_set_col_bnds(lp, 12, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 12, 1);
	glp_set_col_name(lp, 13, "x13");
	glp_set_col_bnds(lp, 13, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 13, 1);
	glp_set_col_name(lp, 14, "x14");
	glp_set_col_bnds(lp, 14, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 14, 1);
	glp_set_col_name(lp, 15, "x15");
	glp_set_col_bnds(lp, 15, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 15, 1);

//***Edge Pair Conditions***
ia[1] = 1,	 ja[1] = 1,	 ar[1] = 1;
ia[2] = 1,	 ja[2] = 9,	 ar[2] = 1;
ia[3] = 2,	 ja[3] = 1,	 ar[3] = 1;
ia[4] = 2,	 ja[4] = 15,	 ar[4] = 1;
ia[5] = 3,	 ja[5] = 2,	 ar[5] = 1;
ia[6] = 3,	 ja[6] = 7,	 ar[6] = 1;
ia[7] = 4,	 ja[7] = 2,	 ar[7] = 1;
ia[8] = 4,	 ja[8] = 13,	 ar[8] = 1;
ia[9] = 5,	 ja[9] = 3,	 ar[9] = 1;
ia[10] = 5,	 ja[10] = 6,	 ar[10] = 1;
ia[11] = 6,	 ja[11] = 3,	 ar[11] = 1;
ia[12] = 6,	 ja[12] = 14,	 ar[12] = 1;
ia[13] = 7,	 ja[13] = 4,	 ar[13] = 1;
ia[14] = 7,	 ja[14] = 10,	 ar[14] = 1;
ia[15] = 8,	 ja[15] = 4,	 ar[15] = 1;
ia[16] = 8,	 ja[16] = 12,	 ar[16] = 1;
ia[17] = 9,	 ja[17] = 5,	 ar[17] = 1;
ia[18] = 9,	 ja[18] = 8,	 ar[18] = 1;
ia[19] = 10,	 ja[19] = 5,	 ar[19] = 1;
ia[20] = 10,	 ja[20] = 11,	 ar[20] = 1;
ia[21] = 11,	 ja[21] = 6,	 ar[21] = 1;
ia[22] = 11,	 ja[22] = 14,	 ar[22] = 1;
ia[23] = 12,	 ja[23] = 7,	 ar[23] = 1;
ia[24] = 12,	 ja[24] = 13,	 ar[24] = 1;
ia[25] = 13,	 ja[25] = 8,	 ar[25] = 1;
ia[26] = 13,	 ja[26] = 11,	 ar[26] = 1;
ia[27] = 14,	 ja[27] = 9,	 ar[27] = 1;
ia[28] = 14,	 ja[28] = 15,	 ar[28] = 1;
ia[29] = 15,	 ja[29] = 10,	 ar[29] = 1;
ia[30] = 15,	 ja[30] = 12,	 ar[30] = 1;

//***Vertex Conditions***
ia[31] = 16,	 ja[31] = 1,	 ar[31] = 1;
ia[32] = 16,	 ja[32] = 2,	 ar[32] = 1;
ia[33] = 16,	 ja[33] = 3,	 ar[33] = 1;
ia[34] = 17,	 ja[34] = 1,	 ar[34] = 1;
ia[35] = 17,	 ja[35] = 4,	 ar[35] = 1;
ia[36] = 17,	 ja[36] = 5,	 ar[36] = 1;
ia[37] = 18,	 ja[37] = 4,	 ar[37] = 1;
ia[38] = 18,	 ja[38] = 6,	 ar[38] = 1;
ia[39] = 18,	 ja[39] = 7,	 ar[39] = 1;
ia[40] = 19,	 ja[40] = 6,	 ar[40] = 1;
ia[41] = 19,	 ja[41] = 8,	 ar[41] = 1;
ia[42] = 19,	 ja[42] = 9,	 ar[42] = 1;
ia[43] = 20,	 ja[43] = 2,	 ar[43] = 1;
ia[44] = 20,	 ja[44] = 8,	 ar[44] = 1;
ia[45] = 20,	 ja[45] = 10,	 ar[45] = 1;
ia[46] = 21,	 ja[46] = 3,	 ar[46] = 1;
ia[47] = 21,	 ja[47] = 11,	 ar[47] = 1;
ia[48] = 21,	 ja[48] = 12,	 ar[48] = 1;
ia[49] = 22,	 ja[49] = 5,	 ar[49] = 1;
ia[50] = 22,	 ja[50] = 13,	 ar[50] = 1;
ia[51] = 22,	 ja[51] = 14,	 ar[51] = 1;
ia[52] = 23,	 ja[52] = 7,	 ar[52] = 1;
ia[53] = 23,	 ja[53] = 11,	 ar[53] = 1;
ia[54] = 23,	 ja[54] = 15,	 ar[54] = 1;
ia[55] = 24,	 ja[55] = 9,	 ar[55] = 1;
ia[56] = 24,	 ja[56] = 12,	 ar[56] = 1;
ia[57] = 24,	 ja[57] = 13,	 ar[57] = 1;
ia[58] = 25,	 ja[58] = 10,	 ar[58] = 1;
ia[59] = 25,	 ja[59] = 14,	 ar[59] = 1;
ia[60] = 25,	 ja[60] = 15,	 ar[60] = 1;
	glp_load_matrix(lp, 54, ia, ja, ar);
	glp_simplex(lp,NULL);
	z = glp_get_obj_val(lp);
	
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);
	x4 = glp_get_col_prim(lp, 4);
	x5 = glp_get_col_prim(lp, 5);
	x6 = glp_get_col_prim(lp, 6);
	x7 = glp_get_col_prim(lp, 7);
	x8 = glp_get_col_prim(lp, 8);
	x9 = glp_get_col_prim(lp, 9);
	x10 = glp_get_col_prim(lp, 10);
	x11 = glp_get_col_prim(lp, 11);
	x12 = glp_get_col_prim(lp, 12);
	x13 = glp_get_col_prim(lp, 13);
	x14 = glp_get_col_prim(lp, 14);
	x15 = glp_get_col_prim(lp, 15);
	printf("\nz = \%g; x1 = %g; x2 = %g; x3 = %g; x4 = %g; x5 = %g; x6 = %g; x7 = %g; x8 = %g; x9 = %g; x10 = %g; x11 = %g; x12 = %g; x13 = %g; x14 = %g; x15 = %g; \n", z, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
	 glp_delete_prob(lp);
	return 0;

}