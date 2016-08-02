#!/usr/bin/gnuplot
OUTFILENAME="Alpha_T__Kappa"

#########################################################################
mpl_top    = 0.44 #inch  outer top margin, title goes here
mpl_bot    = 0.54 #inch  outer bottom margin, x label goes here
mpl_left   = 0.95 #inch  outer left margin, y label goes here
mpl_right  = 0.68 #inch  outer right margin, y2 label goes here
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
xmin=0.01
xmax=2.05
set xrange [xmin:xmax]
set xlabel "$T$"
set format x "$%g$"
#set logscale x


### X
ymin=-0.05
ymax=4.1
set yrange [ymin:ymax]
set ylabel "$\\alpha$"
set format y "$%g$"

### colorbar
#set cbrange [-1:1]

set title "$\\delta = 0.2$"

#load "moreland.pal"
load "MyMoreland.pal"
#set palette gray
plot \
"Alpha_T__Kappa.dat" u 1:2:3 with circles lc palette fs transparent solid t ""#, \
#"Alpha_T__Kappa.dat" u 1:2:(sprintf("%g",$3) ) with labels

#unset label
#unset xlabel
#unset ylabel

set output
system(sprintf("latex %s.tex", OUTFILENAME))
system(sprintf("dvipdf %s.dvi", OUTFILENAME))
system('rm -f *.aux *dvi *tex *log *eps')
set print "-"
print sprintf("okular	%s.pdf &",OUTFILENAME)
