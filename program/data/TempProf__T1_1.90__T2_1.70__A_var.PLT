#!/usr/bin/gnuplot
set term epslatex size 8.6cm,7cm standalone color dl 3 header '\usepackage{grffile}  \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
OUTFILENAME="TempProf__T1_1.90__T2_1.70__A_var.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME

load 'set1.pal'

set xlabel "\\Large $i/N$"
set ylabel "\\Large $T_i$"
set ytics 0.10
ymin=1.70
ymax=1.90
set yrange [ymin:ymax]

set multiplot
plot \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_0.00.DAT' u 1:2 w l ls 1 lw 3 t "\\scriptsize $0.00$" , \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_0.50.DAT' u 1:2 w l ls 2 lw 3 t "\\scriptsize $0.50$" , \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_1.00.DAT' u 1:2 w l ls 3 lw 3 t "\\scriptsize $1.00$" , \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_1.50.DAT' u 1:2 w l ls 4 lw 3 t "\\scriptsize $1.50$" #, \

set key at 0.4,0.5*(ymin+ymax)-0.05 #left bottom
plot \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_2.00.DAT' u 1:2 w l ls 5 lw 3 t "\\scriptsize $2.00$" , \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_3.00.DAT' u 1:2 w l ls 6 lw 3 t "\\scriptsize $3.00$" , \
'TempFluxProfile__N_100__T1_1.90__T2_1.70__A_INFT.DAT' u 1:2 w l ls 7 lw 3 t "\\scriptsize $\\infty$" #, \


unset multiplot





