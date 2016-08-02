#!/usr/bin/gnuplot
OUTFILENAME="FluxProf__A_var.tex"
set term epslatex size 20cm,18cm standalone color dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
set out OUTFILENAME

ymin=0.0
ymax=0.003
set xrange [-0.01:1.01]
set yrange [ymin:ymax]
set key out

set title "\\scriptsize $N=100, T=0.8, \\Delta T=0.2$" #at 2.5, 0.5*(ymin+ymax)
titulo(alpha)=sprintf("\\scriptsize $%s$", alpha)
plot \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.00.DAT' u 1:(1*$5) w lp t titulo("0.00"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.25.DAT' u 1:(1*$5) w lp t titulo("0.25"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.50.DAT' u 1:(1*$5) w lp t titulo("0.50"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.75.DAT' u 1:(1*$5) w lp t titulo("0.75"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.00.DAT' u 1:(1*$5) w lp t titulo("1.00"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.25.DAT' u 1:(1*$5) w lp t titulo("1.25"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.50.DAT' u 1:(1*$5) w lp t titulo("1.50"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.75.DAT' u 1:(1*$5) w lp t titulo("1.75"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.00.DAT' u 1:(1*$5) w lp t titulo("2.00"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.25.DAT' u 1:(1*$5) w lp t titulo("2.25"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.50.DAT' u 1:(1*$5) w lp t titulo("2.50"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.75.DAT' u 1:(1*$5) w lp t titulo("2.75"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.00.DAT' u 1:(1*$5) w lp t titulo("3.00"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.25.DAT' u 1:(1*$5) w lp t titulo("3.25"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.50.DAT' u 1:(1*$5) w lp t titulo("3.50"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.75.DAT' u 1:(1*$5) w lp t titulo("3.75"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_4.00.DAT' u 1:(1*$5) w lp t titulo("4.00"), \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_INFT.DAT' u 1:(1*$5) w lp t titulo("INFT")#, \

set print "-"
print OUTFILENAME
