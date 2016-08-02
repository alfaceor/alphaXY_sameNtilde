#!/usr/bin/gnuplot
set term epslatex size 10cm,7cm standalone color dl 3 header '\newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
OUTFILENAME="TempProf__A_var.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME


set xlabel "\\Large $i/N$"
set ylabel "\\Large $T_i$"
set ytics 0.10
load 'set1.pal'
set multiplot
plot \
'TempFluxProfile__N_50__A_0.00.DAT' u 1:2 w l ls  1 lw 3 t "\\scriptsize $\\alpha = 0.00$" , \
'TempFluxProfile__N_50__A_0.50.DAT' u 1:2 w l ls  2 lw 3 t "\\scriptsize $\\alpha = 0.50$" , \
'TempFluxProfile__N_50__A_1.00.DAT' u 1:2 w l ls  3 lw 3 t "\\scriptsize $\\alpha = 1.00$" , \
'TempFluxProfile__N_50__A_1.50.DAT' u 1:2 w l ls  4 lw 3 t "\\scriptsize $\\alpha = 1.50$" #, \

set key at 0.4,0.79 #left bottom
plot \
'TempFluxProfile__N_50__A_2.00.DAT' u 1:2 w l ls  5 lw 3 t "\\scriptsize $\\alpha = 2.00$" , \
'TempFluxProfile__N_50__A_3.00.DAT' u 1:2 w l ls  6 lw 3 t "\\scriptsize $\\alpha = 3.00$" , \
'TempFluxProfile__N_50__A_4.00.DAT' u 1:2 w l ls  7 lw 3 t "\\scriptsize $\\alpha = 4.00$" , \
'TempFluxProfile__N_50__A_INFT.DAT' u 1:2 w l ls  8 lw 3 t "\\scriptsize $\\alpha \\to \\infty$" #, \

#plot \
#'TempFluxProfile__N_50__A_0.00.DAT' u 1:2 w l ls  1 lw 2 t "\\scriptsize $\\alpha = 0.00$" , \
#'TempFluxProfile__N_50__A_0.25.DAT' u 1:2 w l ls  2 lw 2 t "\\scriptsize $\\alpha = 0.25$" , \
#'TempFluxProfile__N_50__A_0.50.DAT' u 1:2 w l ls  3 lw 2 t "\\scriptsize $\\alpha = 0.50$" , \
#'TempFluxProfile__N_50__A_0.75.DAT' u 1:2 w l ls  4 lw 2 t "\\scriptsize $\\alpha = 0.75$" , \
#'TempFluxProfile__N_50__A_1.00.DAT' u 1:2 w l ls  5 lw 2 t "\\scriptsize $\\alpha = 1.00$" , \
#'TempFluxProfile__N_50__A_1.25.DAT' u 1:2 w l ls  6 lw 2 t "\\scriptsize $\\alpha = 1.25$" , \
#'TempFluxProfile__N_50__A_1.50.DAT' u 1:2 w l ls  7 lw 2 t "\\scriptsize $\\alpha = 1.50$" , \
#'TempFluxProfile__N_50__A_1.75.DAT' u 1:2 w l ls  8 lw 2 t "\\scriptsize $\\alpha = 1.75$" , \
#'TempFluxProfile__N_50__A_2.00.DAT' u 1:2 w l ls  9 lw 2 t "\\scriptsize $\\alpha = 2.00$" #, \
#
#set key at 0.4,0.79 #left bottom
#plot \
#'TempFluxProfile__N_50__A_2.25.DAT' u 1:2 w l ls 10 lw 2 t "\\scriptsize $\\alpha = 2.25$" , \
#'TempFluxProfile__N_50__A_2.50.DAT' u 1:2 w l ls 11 lw 2 t "\\scriptsize $\\alpha = 2.50$" , \
#'TempFluxProfile__N_50__A_2.75.DAT' u 1:2 w l ls 12 lw 2 t "\\scriptsize $\\alpha = 2.75$" , \
#'TempFluxProfile__N_50__A_3.00.DAT' u 1:2 w l ls 13 lw 2 t "\\scriptsize $\\alpha = 3.00$" , \
#'TempFluxProfile__N_50__A_3.25.DAT' u 1:2 w l ls 14 lw 2 t "\\scriptsize $\\alpha = 3.25$" , \
#'TempFluxProfile__N_50__A_3.50.DAT' u 1:2 w l ls 15 lw 2 t "\\scriptsize $\\alpha = 3.50$" , \
#'TempFluxProfile__N_50__A_3.75.DAT' u 1:2 w l ls 16 lw 2 t "\\scriptsize $\\alpha = 3.75$" , \
#'TempFluxProfile__N_50__A_4.00.DAT' u 1:2 w l ls 17 lw 2 t "\\scriptsize $\\alpha = 4.00$" , \
#'TempFluxProfile__N_50__A_INFT.DAT' u 1:2 w l ls 18 lw 2 t "\\scriptsize $\\alpha \\to \\infty$" #, \


unset multiplot
