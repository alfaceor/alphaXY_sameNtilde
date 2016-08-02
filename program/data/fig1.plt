#!/usr/bin/gnuplot
OUTFILENAME="fig1"

#########################################################################
mpl_top    = 0.44 #inch  outer top margin, title goes here
mpl_bot    = 0.54 #inch  outer bottom margin, x label goes here
mpl_left   = 0.95 #inch  outer left margin, y label goes here
mpl_right  = 0.28 #inch  outer right margin, y2 label goes here
mpl_height = 2.0 #inch  height of individual plots
mpl_width  = 2.0*(7.0/5) #inch  width of individual plots
mpl_dx     = 0.65 #inch  inter-plot horizontal spacing
mpl_dy     = 0.1 #inch  inter-plot vertical spacing
mpl_ny     = 1   #number of rows
mpl_nx     = 1   #number of columns

# calculate full dimensions
xsize = mpl_left+mpl_right+(mpl_width*mpl_nx)+(mpl_nx-1)*mpl_dx
ysize = mpl_top+mpl_bot+(mpl_ny*mpl_height)+(mpl_ny-1)*mpl_dy

# placement functions
#   rows are numbered from bottom to top
bot(n) = (mpl_bot+(n-1)*mpl_height+(n-1)*mpl_dy)/ysize
top(n)  = 1-((mpl_top+(mpl_ny-n)*(mpl_height+mpl_dy))/ysize)
#   columns are numbered from left to right
left(n) = (mpl_left+(n-1)*mpl_width+(n-1)*mpl_dx)/xsize
right(n)  = 1-((mpl_right+(mpl_nx-n)*(mpl_width+mpl_dx))/xsize)



#set ter epslatex standalone color colortext 12 dl 1.5 size xsize,ysize #header "\\usepackage{cmbright}"
set term epslatex size xsize,ysize standalone color colortext 12 dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'

set out sprintf("%s.tex",OUTFILENAME)
set tics scale 1.2

#########################################################################

################   Plot 1 top  ################   

r=1
c=1

set lmargin at screen left(c)
set rmargin at screen right(c)

set tmargin at screen top(r)
set bmargin at screen bot(r)

### X
xmin=0
xmax=1
#set xrange [xmin:xmax]
set xlabel "$i/N$" offset 0.7,1
set format x "$%g$"
set xtics format "\\footnotesize $%0.1f$" offset 0.7,0

set xrange [-0.02:1.02]


### X
ymin=0.70
ymax=0.90
#set yrange [ymin:ymax]
set yrange [ymin-0.01:ymax+0.01]
set ylabel "$T_i$" offset 6.0,3 rotate by 0
set ytics format "\\footnotesize $%0.1f$" offset 0.7,0
set ytics 0.10



set key invert
set key at 0.95,0.9 spacing 0.7
load 'set1differlt.pal'

plot \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.00.DAT' u 1:2 w l ls 1 lw 4 t "\\scriptsize $0.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.50.DAT' u 1:2 w l ls 2 lw 4 t "\\scriptsize $0.50$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.00.DAT' u 1:2 w l ls 3 lw 4 t "\\scriptsize $1.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_1.50.DAT' u 1:2 w l ls 4 lw 4 t "\\scriptsize $1.50$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_2.00.DAT' u 1:2 w l ls 5 lw 4 t "\\scriptsize $2.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_3.00.DAT' u 1:2 w l ls 6 lw 4 t "\\scriptsize $3.00$" , \
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_INFT.DAT' u 1:2 w l ls 7 lw 4 t "\\scriptsize $\\infty$" #, \




#unset label
#unset xlabel
#unset ylabel

set output
system(sprintf("latex %s.tex", OUTFILENAME))
system(sprintf("dvipdf %s.dvi", OUTFILENAME))
system('rm -f *.aux *dvi *tex *log *eps')
set print "-"
print sprintf("okular	%s.pdf &",OUTFILENAME)
