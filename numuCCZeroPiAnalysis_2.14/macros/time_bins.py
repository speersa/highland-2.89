#!/usr/bin/python

# A small script to check the (true)track time distribution in time-bins and so set corresponding cuts for highland analysis 

import os,sys
from optparse import OptionParser
import math

# Prevent ROOT from interpreting the command line arguments !
tmpargv = sys.argv
sys.argv = [ '-n' ]
from ROOT import *
sys.argv = tmpargv
from array import array

class timeBins:
    def __init__(self, options):
        """
        Instantiate the requested custom generator class.
        """
        self.OutputName = options.outfile
        self.InputFile  = options.inputfile

        #create drawing tools instance    
        self.Draw   = DrawingToolsBase(self.InputFile)
        self.Sample = DataSample(self.InputFile)

        #canvas for plots 
        self.Canv = TCanvas()
        SetOwnership(self.Canv, False)
        
        self.Tree = self.Sample.GetTree(options.tree)
        if not self.Tree:
            print ("Failed to load tree -- %s" % options.tree)
        
        self.VarName = options.var
            
        self.PreCut = options.cut  
        
        self.Sigma  = options.sigma 


    # ============ PDF stuff ==============
    def OpenPDF(self):
        self.Canv.Print(self.OutputName+'.pdf[')

    def Update(self):
        self.Canv.Modified()
        self.Canv.Update() 

    def PrintPDF(self):
        self.Canv.Print(self.OutputName + ".pdf")
        self.Canv.Clear()

    def ClosePDF(self):
        self.Canv.Print(self.OutputName +'.pdf]')
        self.Canv.Clear()

    # =====================================
    def FitBins(self):

        self.Canv.Clear()
        self.OpenPDF()

        #draw the distribution
        histo = self.Draw.Draw(self.Tree, self.VarName, 4000, 0, 8000., "all", self.PreCut)

        #create TSpectrum object to search for peaks
        peakFinder = TSpectrum(10, 1)  
        npeaks     = peakFinder.Search(histo, 15.)

        if npeaks < 8:
            print "failed to find 8  peaks!!"
            sys.exit(2)

        peakPos = []

        ##fit peaks with eight gaussians 
        xpeaks = peakFinder.GetPositionX()

        for i in range(0, 8):
            peakPos.append(xpeaks[i])

        peakPos.sort()    

        par = array( 'd', 24*[0.])


        total_name = ""
        first = True
        index = 0
        for i, pos  in enumerate(peakPos):
            func = TF1("g"+str(i), "gaus", pos-self.Sigma, pos+self.Sigma)
            total_name += "gaus(" + str(index) + ")+"

            if first:
                histo.Fit(func, "R")
            else:
                histo.Fit(func, "R+")

            first = False

            par_fit = func.GetParameters()
            par[index], par[index+1], par[index+2] = par_fit[0], par_fit[1], par_fit[2]
            index += 3

        total_name = total_name[:-1]

        total = TF1("total", total_name, peakPos[0]-self.Sigma, peakPos[-1]+self.Sigma)
        
        total.SetParameters(par)
        total.SetLineColor(4)
        
        # fill the total
        histo.Fit (total, "R+") 
        
        self.PrintPDF()
        self.ClosePDF()




def main(argv):
    usage   = "usage: %prog [options] -o OUT"
    optparser  = OptionParser(usage=usage)
    optparser.add_option ('-o', '--out',    dest='outfile',     type="string",  help="Output file, no .pdf at the end",         default="time_bins")
    optparser.add_option ('-i', '--input',  dest='inputfile',   type="string",  help="Input .root highland2 micro-tree file")
    optparser.add_option ('-t', '--tree',   dest='tree',        type="string",  help="Tree name")
    optparser.add_option ('-v', '--var',    dest='var',         type="string",  help="Variable name")
    optparser.add_option ('-c', '--cut',    dest='cut',         type="string",  help="Cut name",                                default="")
    optparser.add_option ('-s', '--sigma',  dest='sigma',       type="float",   help="Sigma start",                             default=15.)



    (options, args) = optparser.parse_args()

    if not options.inputfile:
        print "No input file"
        sys.exit(2)

    if not options.tree:
        print "No tree name given"
        sys.exit(2)
     
    if not options.var:
        print "No var name given"
        sys.exit(2)
    
     
        
     
    TimeBinner = timeBins(options)
    TimeBinner.FitBins()


if __name__ == "__main__":
    main(sys.argv[1:])
