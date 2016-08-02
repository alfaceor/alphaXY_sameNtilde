
T=0.80
DelT01=0.02
DelT02=0.20
DelT03=0.30


#DelT01=1
#DelT02=1
#DelT03=1
plot \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_0.00.DAT" u 1:(($2-T)/DelT01) w lp ls 1 pt 2 t "0.00" , \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_0.50.DAT" u 1:(($2-T)/DelT01) w lp ls 2 pt 2 t "0.50" , \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_1.00.DAT" u 1:(($2-T)/DelT01) w lp ls 3 pt 2 t "1.00" , \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_1.50.DAT" u 1:(($2-T)/DelT01) w lp ls 4 pt 2 t "1.50" , \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_2.00.DAT" u 1:(($2-T)/DelT01) w lp ls 5 pt 2 t "2.00" , \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_3.00.DAT" u 1:(($2-T)/DelT01) w lp ls 6 pt 2 t "3.00" , \
"TempFluxProfile__N_100__T1_0.81__T2_0.79__A_INFT.DAT" u 1:(($2-T)/DelT01) w lp ls 7 pt 2 t "INFT" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.00.DAT" u 1:(($2-T)/DelT02) w lp ls 1 pt 4 t "0.00" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.50.DAT" u 1:(($2-T)/DelT02) w lp ls 2 pt 4 t "0.50" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.00.DAT" u 1:(($2-T)/DelT02) w lp ls 3 pt 4 t "1.00" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.50.DAT" u 1:(($2-T)/DelT02) w lp ls 4 pt 4 t "1.50" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.00.DAT" u 1:(($2-T)/DelT02) w lp ls 5 pt 4 t "2.00" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.00.DAT" u 1:(($2-T)/DelT02) w lp ls 6 pt 4 t "3.00" , \
"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_INFT.DAT" u 1:(($2-T)/DelT02) w lp ls 7 pt 4 t "INFT" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_0.00.DAT" u 1:(($2-T)/DelT03) w lp ls 1 pt 6 t "0.00" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_0.50.DAT" u 1:(($2-T)/DelT03) w lp ls 2 pt 6 t "0.50" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_1.00.DAT" u 1:(($2-T)/DelT03) w lp ls 3 pt 6 t "1.00" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_1.50.DAT" u 1:(($2-T)/DelT03) w lp ls 4 pt 6 t "1.50" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_2.00.DAT" u 1:(($2-T)/DelT03) w lp ls 5 pt 6 t "2.00" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_3.00.DAT" u 1:(($2-T)/DelT03) w lp ls 6 pt 6 t "3.00" , \
"TempFluxProfile__N_100__T1_0.95__T2_0.65__A_INFT.DAT" u 1:(($2-T)/DelT03) w lp ls 7 pt 6 t "INFT" #, \









