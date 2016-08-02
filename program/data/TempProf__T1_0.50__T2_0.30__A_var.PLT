#!/usr/bin/gnuplot
OUTFILENAME="TempProf__T1_0.50__T2_0.30__A_var.tex"
set term epslatex size 8.6cm,7cm standalone color dl 3 header '\usepackage{grffile}  \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
#load 'set1.pal'
load 'TempProf.pal'

set out OUTFILENAME

set xlabel "\\Large $i/N$" offset 0
set ylabel "\\Large $T_i$" offset 2
set ytics 0.10
ymin=0.30
ymax=0.50

T1=0.50
T2=0.30
T=0.5*(T1+T2)
DelT=T1-T2
set yrange [T2-0.05*DelT:T1+0.05*DelT]
#set yrange [ymin-0.01:ymax+0.01]
set xrange [-0.02:1.02]

set ytics (T2,T,T1)

set key invert
set key spacing 0.8

set out OUTFILENAME
#set multiplot
plot \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_0.00.DAT' u 1:2 w l ls 1 lw 3 t "\\scriptsize $0.00$" , \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_0.50.DAT' u 1:2 w l ls 2 lw 3 t "\\scriptsize $0.50$" , \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_1.00.DAT' u 1:2 w l ls 3 lw 3 t "\\scriptsize $1.00$" , \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_1.50.DAT' u 1:2 w l ls 4 lw 3 t "\\scriptsize $1.50$" , \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_2.00.DAT' u 1:2 w l ls 5 lw 3 t "\\scriptsize $2.00$" , \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_3.00.DAT' u 1:2 w l ls 6 lw 3 t "\\scriptsize $3.00$" , \
'TempFluxProfile__N_100__T1_0.50__T2_0.30__A_INFT.DAT' u 1:2 w l ls 7 lw 3 t "\\scriptsize $\\infty$" #, \


#set key at 0.4,0.5*(ymin+ymax)-0.05 #left bottom
#plot \
#unset multiplot


set print "-"
print OUTFILENAME
