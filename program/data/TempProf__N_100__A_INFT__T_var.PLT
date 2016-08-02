#!/usr/bin/gnuplot 

plot \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_INFT.DAT' u 1:($2-0.40) w lp t "T=0.40", \
'TempFluxProfile__N_100__T1_0.70__T2_0.50__A_INFT.DAT' u 1:($2-0.60) w lp t "T=0.60", \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_INFT.DAT' u 1:($2-0.80) w lp t "T=0.80", \
'TempFluxProfile__N_100__T1_1.30__T2_1.10__A_INFT.DAT' u 1:($2-1.20) w lp t "T=1.20", \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_INFT.DAT' u 1:($2-1.80) w lp t "T=1.80", \
'TempFluxProfile__N_100__T1_2.50__T2_2.30__A_INFT.DAT' u 1:($2-2.40) w lp t "T=2.40"#, \

#'TempFluxProfile__N_100__T1_0.81__T2_0.79__A_INFT.DAT' u 1:($2-0.80) w lp t "T=0.80", \
#'TempFluxProfile__N_100__T1_0.95__T2_0.65__A_INFT.DAT' u 1:($2-0.80) w lp t "T=0.80", \
