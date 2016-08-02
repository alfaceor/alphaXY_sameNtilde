#!/usr/bin/gnuplot


set xlabel "alpha"

set yrange [-0.25:0.25]
#set yrange [-2:2]
titulo01(A)=sprintf("slope T=%s",A)
titulo02(A)=sprintf("Flux  T=%s",A)
plot \
'SLOPE_FLUX__N_100__T1_0.50__T2_0.30__ALPHA.DAT' u ($2=='INFT'? 5:$2):5       w lp ls 1 ps 2 pt 1 t titulo01("0.40") ,\
'SLOPE_FLUX__N_100__T1_0.70__T2_0.50__ALPHA.DAT' u ($2=='INFT'? 5:$2):5       w lp ls 1 ps 2 pt 2 t titulo01("0.60") ,\
'SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT' u ($2=='INFT'? 5:$2):5       w lp ls 1 ps 2 pt 7 t titulo01("0.80") ,\
'SLOPE_FLUX__N_100__T1_1.30__T2_1.10__ALPHA.DAT' u ($2=='INFT'? 5:$2):5       w lp ls 1 ps 2 pt 4 t titulo01("1.20") ,\
'SLOPE_FLUX__N_100__T1_1.90__T2_1.70__ALPHA.DAT' u ($2=='INFT'? 5:$2):5       w lp ls 1 ps 2 pt 5 t titulo01("1.80") ,\
'SLOPE_FLUX__N_100__T1_0.50__T2_0.30__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7) w lp ls 2 ps 2 pt 1 t titulo02("0.40") ,\
'SLOPE_FLUX__N_100__T1_0.70__T2_0.50__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7) w lp ls 2 ps 2 pt 2 t titulo02("0.60") ,\
'SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7) w lp ls 2 ps 2 pt 7 t titulo02("0.80") ,\
'SLOPE_FLUX__N_100__T1_1.30__T2_1.10__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7) w lp ls 2 ps 2 pt 4 t titulo02("1.20") ,\
'SLOPE_FLUX__N_100__T1_1.90__T2_1.70__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7) w lp ls 2 ps 2 pt 5 t titulo02("1.80") #,\
