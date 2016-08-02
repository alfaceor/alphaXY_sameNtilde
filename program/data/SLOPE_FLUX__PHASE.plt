#!/usr/bin/gnuplot

#set term tikz size 9,6 standalone
#set term epslatex size 10cm,10cm standalone color dl 3 header '\newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
#set format "\\Large %s"
OUTFILENAME="SLOPE_FLUX__PHASE.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME
load "setNum.pal"

set xlabel "\\Large $\\alpha$"
#set ylabel "\\Large $s$"
set key center right
#set xrange [0:5]
#set yrange [-0.25:0.25]
#
unset ylabel # offset 2,0
#set y2range [0.0002:0.005]
#set autoscale y2
#set xtics add ("$\\infty$" 5)
#set y2tics
#set ytics nomirror
#set label "$\\hl{//}$" at 4.5,-0.25 front
#set label "$\\hl{//}$" at 4.5, 0.25 front

plot \
'./SLOPE_FLUX__N_20__ALPHA.DAT'  u 7:5 w lp ls 1 lw 3 ps 2 pt 65, \
'./SLOPE_FLUX__N_50__ALPHA.DAT'  u 7:5 w lp ls 2 lw 3 ps 2 pt 66, \
'./SLOPE_FLUX__N_100__ALPHA.DAT' u 7:5 w lp ls 3 lw 3 ps 2 pt 67, \
'./SLOPE_FLUX__N_200__ALPHA.DAT' u 7:5 w lp ls 4 lw 3 ps 2 pt 68#, \

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



