#!/usr/bin/gnuplot
#set term epslatex size 15cm,10.2cm standalone color dl 3 header '\usepackage{grffile}  \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
set term epslatex size 4.03,2.60 standalone color dl 3 header '\usepackage{grffile}  \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
OUTFILENAME="TempProf__T1_0.90__T2_0.70__A_var.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME

#load 'set1.pal'
load 'set1differlt.pal'

set ytics format "\\Large $%0.1f$" offset 0.7,0
set xtics format "\\Large $%0.1f$" offset 0.7,0
set xlabel "\\Large $i/N$"
set ylabel "\\Large $T_i$" offset 6,3 rotate by 0
set ytics 0.10
ymin=0.70
ymax=0.90

set key invert
set key at 0.95,0.9 spacing 0.8
set yrange [ymin-0.01:ymax+0.01]
set xrange [-0.02:1.02]
set lmargin 10
set rmargin 10
plot \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.00.DAT' u 1:2 w l ls 1 lw 4 t "\\scriptsize $0.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.50.DAT' u 1:2 w l ls 2 lw 4 t "\\scriptsize $0.50$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.00.DAT' u 1:2 w l ls 3 lw 4 t "\\scriptsize $1.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.50.DAT' u 1:2 w l ls 4 lw 4 t "\\scriptsize $1.50$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.00.DAT' u 1:2 w l ls 5 lw 4 t "\\scriptsize $2.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.00.DAT' u 1:2 w l ls 6 lw 4 t "\\scriptsize $3.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_INFT.DAT' u 1:2 w l ls 7 lw 4 t "\\scriptsize $\\infty$" #, \






