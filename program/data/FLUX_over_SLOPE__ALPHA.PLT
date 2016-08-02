#!/usr/bin/gnuplot

#set term tikz size 9,6 standalone
set term epslatex size 8.6cm,7cm standalone color dl 3 header '\newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
##set format "\\Large %s"
OUTFILENAME="FLUX_over_SLOPE__ALPHA.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME
load "setNum.pal"

set xlabel "\\Large $\\alpha$"
#set ylabel "\\Large $\\kappa$"
set ylabel "\\Large $J/ \\nabla T_{center}$"
#set key center right
#set xrange [1:5]
#set yrange [0.001:0.1]
ymin=0.1
ymax=2.0
set yrange [ymin:ymax]

infinito=5
#unset ylabel # offset 2,0
#set y2range [0.0002:0.005]
#set autoscale y2
set xtics add ("$\\infty$" 5)
#set y2tics
#set ytics nomirror
set label "$\\hl{//}$" at 4.5, ymin front
set label "$\\hl{//}$" at 4.5, ymax front
set key bottom
#set logscale x
#set logscale y
plot \
'./SLOPE_FLUX__N_20__ALPHA.DAT'    u ($2=='INFT'? infinito:$2):(-$9*$1) w lp  ls 1 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $ 20$", \
'./SLOPE_FLUX__N_50__ALPHA.DAT'    u ($2=='INFT'? infinito:$2):(-$9*$1) w lp  ls 2 lw 3 ps 2 pt 66 axes x1y1 title "\\scriptsize $ 50$", \
'./SLOPE_FLUX__N_100__ALPHA.DAT'   u ($2=='INFT'? infinito:$2):(-$9*$1) w lp  ls 3 lw 3 ps 2 pt 68 axes x1y1 title "\\scriptsize $100$", \
'./SLOPE_FLUX__N_200__ALPHA.DAT'   u ($2=='INFT'? infinito:$2):(-$9*$1) w lp  ls 4 lw 3 ps 2 pt 69 axes x1y1 title "\\scriptsize $200$"#, \




#'./SLOPE_FLUX__N_20__ALPHA.DAT'    u ($2=='INFT'? infinito:$2):(-$9/0.0579170272031) w lp  ls 1 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $N= 20$", \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'    u ($2=='INFT'? infinito:$2):(-$9/0.0246557237199) w lp  ls 2 lw 3 ps 2 pt 66 axes x1y1 title "\\scriptsize $N= 50$", \
#'./SLOPE_FLUX__N_100__ALPHA.DAT'   u ($2=='INFT'? infinito:$2):(-$9/0.0120834299945) w lp  ls 3 lw 3 ps 2 pt 68 axes x1y1 title "\\scriptsize $N=100$", \
#'./SLOPE_FLUX__N_200__ALPHA.DAT'   u ($2=='INFT'? infinito:$2):(-$9/0.00577296614287) w lp  ls 4 lw 3 ps 2 pt 69 axes x1y1 title "\\scriptsize $N=200$"#, \
#

#'./SLOPE_FLUX__N_20__ALPHA.DAT'   u ($2=='INFT'? 5:$2):(-$7*0.14483234301/($5*0.00838825875))     w lp  ls 1 lw 3 ps 2 pt 62 axes x1y1 title "\\scriptsize $N= 20$", \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'   u ($2=='INFT'? 5:$2):(-$7*0.166387346768/($5*0.00410240045238))  w lp  ls 2 lw 3 ps 2 pt 63 axes x1y1 title "\\scriptsize $N= 50$", \
#'./SLOPE_FLUX__N_100__ALPHA.DAT'  u ($2=='INFT'? 5:$2):(-$7*0.181368623136/($5*0.00219155506087))  w lp  ls 3 lw 3 ps 2 pt 64 axes x1y1 title "\\scriptsize $N=100$", \
#'./SLOPE_FLUX__N_200__ALPHA.DAT'  u ($2=='INFT'? 5:$2):(-$7*0.18596641566/($5*0.00107357782131))  w lp  ls 4 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $N=200$"#, \
#

#==> SLOPE_FLUX__N_100__ALPHA.DAT <==
#100 INFT 0.90 0.70 -0.181368623136 0.00164905936163 0.00219155506087
#
#==> SLOPE_FLUX__N_200__ALPHA.DAT <==
#200 4.00 0.90 0.70 -0.18596641566 0.00123759973284 0.00107357782131
#
#==> SLOPE_FLUX__N_20__ALPHA.DAT <==
#20 INFT 0.90 0.70 -0.14483234301 0.00263885721737 0.00838825875
#
#==> SLOPE_FLUX__N_50__ALPHA.DAT <==
#50 INFT 0.90 0.70 -0.166387346768 0.00204255019123 0.00410240045238
#

#'./SLOPE_FLUX__N_50__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($7/($5*$1))             w p  ls 1 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $N= 50$", \

#plot \
#'./SLOPE_FLUX__N_20__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $N= 20, \\nabla T/N$", \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 66 axes x1y1 title "\\scriptsize $N= 50, \\nabla T/N$", \
#'./SLOPE_FLUX__N_100__ALPHA.DAT' u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 68 axes x1y1 title "\\scriptsize $N=100, \\nabla T/N$", \
#'./SLOPE_FLUX__N_200__ALPHA.DAT' u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 69 axes x1y1 title "\\scriptsize $N=200, \\nabla T/N$", \
#'./SLOPE_FLUX__N_20__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5:(100)       w l  ls 1 lw 1            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5:(100)       w l  ls 1 lw 1            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_100__ALPHA.DAT' u ($2=='INFT'? 5:$2):5:(100)       w l  ls 1 lw 1            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_200__ALPHA.DAT' u ($2=='INFT'? 5:$2):5:(100)       w l  ls 1 lw 1            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_20__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $N= 20, J \\times N $", \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 66 axes x1y1 title "\\scriptsize $N= 50, J \\times N $", \
#'./SLOPE_FLUX__N_100__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 68 axes x1y1 title "\\scriptsize $N=100, J \\times N $", \
#'./SLOPE_FLUX__N_200__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 69 axes x1y1 title "\\scriptsize $N=200, J \\times N $", \
#'./SLOPE_FLUX__N_20__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7):(100) w l  ls 2 lw 2            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7):(100) w l  ls 2 lw 2            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_100__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7):(100) w l  ls 2 lw 2            axes x1y1 smooth acspline notitle, \
#'./SLOPE_FLUX__N_200__ALPHA.DAT' u ($2=='INFT'? 5:$2):($1*$7):(100) w l  ls 2 lw 2            axes x1y1 smooth acspline notitle#, \
#


