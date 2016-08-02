#!/usr/bin/gnuplot
plot \
"TempFluxProfile__N_20__A_4.00.DAT"  u 1:2 w l ls 1 t "$N= 20$" ,\
"TempFluxProfile__N_50__A_4.00.DAT"  u 1:2 w l ls 2 t "$N= 50$" ,\
"TempFluxProfile__N_100__A_4.00.DAT" u 1:2 w l ls 3 t "$N=100$" ,\
"TempFluxProfile__N_200__A_4.00.DAT" u 1:2 w l ls 4 t "$N=200$" #,\
